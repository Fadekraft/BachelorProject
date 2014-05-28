/*
 * Physical Memory Management
 *
 * Copyright (C) 2003-2014 Juha Aatrokoski, Timo Lilja,
 *   Leena Salmela, Teemu Takanen, Aleksi Virtanen,
 *   Philip Meulengracht.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: mm_phys.c,v 1.6 2004/01/14 09:05:58 ttakanen Exp $
 *
 */

#include "vm/memory.h"
#include "lib/bitmap.h"
#include "kernel/stalloc.h"
#include "kernel/spinlock.h"
#include "kernel/interrupt.h"
#include "kernel/assert.h"

/** @name Page pool
 *
 * Functions and data structures for handling physical page reservation.
 *
 * @{
 */

/* Bitmap field of physical pages. Length is number of physical pages
   rounded up to a word boundary */
static bitmap_t *pagepool_free_pages;

/* Number of physical pages */
static int pagepool_num_pages;

/* Number of free physical pages */
static int pagepool_num_free_pages;

/* Number of last staticly reserved page. This is needed to ensure
   that staticly reserved pages are not freed in accident (or in
   purpose).  */
static int pagepool_static_end;

/* Spinlock to handle synchronous access to pagepool_free_pages */
static spinlock_t pagepool_slock;

/**
 * Returns the number of memory pages present in the system. Causes
 * kernel panic if the MemInfo device is not found.
 *
 * @return The number of memory pages
 */
int physmem_get_size()
{
    uint32_t num_pages = 0;

    int i;

    io_descriptor_t *io_desc;

    io_desc = (io_descriptor_t *)IO_DESCRIPTOR_AREA;
    
    /* Find MemInfo meta device */
    for(i = 0; i < YAMS_MAX_DEVICES; i++) {
        if (io_desc->type == 0x101) {
        num_pages = (*(uint32_t *)io_desc->io_area_base);
            break;
        }
        io_desc++;
    }

    if (num_pages == 0)
        KERNEL_PANIC("No MemInfo device found.");

    return num_pages;
}

/**
 * Returns the number of pages statically reserved for the kernel.
 *
 * @return The number of pages
 */
int physmem_get_reserved_size()
{
    int num_res_pages;
    uint32_t system_memory_size = 0;
    physaddr_t free_start = (physaddr_t)stalloc(1);
    system_memory_size = physmem_get_size() * PAGE_SIZE;

    num_res_pages = (free_start - 0x80000000) / PAGE_SIZE;

    if (((free_start - 0x80000000) % PAGE_SIZE) != 0)
        num_res_pages++;

    kprintf("Kernel size is 0x%.8x (%d) bytes\n", 
        (free_start - KERNEL_BOOT_ADDRESS),
        (free_start - KERNEL_BOOT_ADDRESS));
    kprintf("System Memory Size: 0x%x bytes\n", system_memory_size);

    return num_res_pages;
}


/**
 * Physical memory initialization. Finds out number of physical pages and
 * number of staticly reserved physical pages. Marks reserved pages
 * reserved in pagepool_free_pages.
 */
void physmem_init(void *BootInfo)
{
    int num_res_pages;
    int i;

    /* We dont use this */
    BootInfo = BootInfo;

    pagepool_num_pages = physmem_get_size();

    pagepool_free_pages = 
        (uint32_t *)stalloc(bitmap_sizeof(pagepool_num_pages));
    bitmap_init(pagepool_free_pages, pagepool_num_pages);

    /* Note that number of reserved pages must be get after we have 
       (staticly) reserved memory for bitmap. */
    num_res_pages = physmem_get_reserved_size();
    pagepool_num_free_pages = pagepool_num_pages - num_res_pages;
    pagepool_static_end = num_res_pages;

    for (i = 0; i < num_res_pages; i++)
        bitmap_set(pagepool_free_pages, i, 1);

    spinlock_reset(&pagepool_slock);

    kprintf("Pagepool: Found %d pages of size %d\n", pagepool_num_pages,
            PAGE_SIZE);
    kprintf("Pagepool: Static allocation for kernel: %d pages\n", 
            num_res_pages);
}

/**
 * Finds first free physical page and marks it reserved.  
 *
 * @return Address of first free physical page, zero if no free pages
 * are available.
 */
physaddr_t physmem_allocblock(void)
{
    interrupt_status_t intr_status;
    int i;

    intr_status = _interrupt_disable();
    spinlock_acquire(&pagepool_slock);
    
    if (pagepool_num_free_pages > 0) {
	i = bitmap_findnset(pagepool_free_pages,pagepool_num_pages);
	pagepool_num_free_pages--;

        /* There should have been a free page. Check that the pagepool
           internal variables are in synch. */
	KERNEL_ASSERT(i >= 0 && pagepool_num_free_pages >= 0);
    } else {
        i = 0;
    }

    spinlock_release(&pagepool_slock);
    _interrupt_set_state(intr_status);
    return i*PAGE_SIZE;
}

/**
 * Frees given page. Given page should be reserved, but not staticly
 * reserved.
 *
 * @param phys_addr Page to be freed.
 */
void physmem_freeblock(void *Ptr)
{
    interrupt_status_t intr_status;
    int i;

    physaddr_t phys_addr = (physaddr_t)Ptr;
    i = phys_addr / PAGE_SIZE;

    /* A page allocated by stalloc should not be freed. */
    KERNEL_ASSERT(i >= pagepool_static_end);

    intr_status = _interrupt_disable();
    spinlock_acquire(&pagepool_slock);
    
    /* Check that the page was reserved. */
    KERNEL_ASSERT(bitmap_get(pagepool_free_pages, i) == 1);

    bitmap_set(pagepool_free_pages, i, 0);
    pagepool_num_free_pages++;

    spinlock_release(&pagepool_slock);
    _interrupt_set_state(intr_status);
}



/** @} */

