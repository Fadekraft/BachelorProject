/*
 * Pagetable.
 *
 * Copyright (C) 2014 Juha Aatrokoski, Timo Lilja,
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
 * $Id: pagetable.h,v 1.0 2003/05/08 13:47:19 philip Exp $
 *
 */

#ifndef KUDOS_VM_PAGETABLE_H
#define KUDOS_VM_PAGETABLE_H

#include "lib/types.h"

/* Number of mapping entries in one pagetable. This is the number
   of entries that fits on a single hardware memory page (4k). */
#define PAGE_TABLE_ENTRIES 512

/* Page/Table/Ptr Attributes */
#define PAGE_MASK	0xFFFFFFFFFFFFF000
#define PAGE_ATTRIBS	0x0000000000000FFF
#define PAGE_PRESENT	0x1
#define PAGE_WRITE	0x2
#define PAGE_USER	0x4
#define PAGE_WRITETHR	0x8
#define PAGE_NOT_CACHE	0x10
#define PAGE_ACCESSED	0x20
#define PAGE_DIRTY	0x40
#define PAGE_2MB	0x80
#define PAGE_CPU_GLOBAL	0x100
#define PAGE_LV4_GLOBAL	0x200

/* In x86_64, with 4 KB Pages we have 4 Level Page Directory */

/* The lowest level, is a page, which contains a physical address */
typedef uint64_t page_t;

/* The next level, is a page table, it has 512 page entries */
typedef struct PageTable
{
	/* 512 Pages */
	page_t Pages[PAGE_TABLE_ENTRIES];

} pagetable_t;

/* The next level is Page Directories, they have 512 page tables each */
typedef struct PageDirectory
{
	/* 512 Page tables 
	 * Physical address of each page table is contained here */
	uint64_t pTables[PAGE_TABLE_ENTRIES];

	/* Their virtual mapping 
	 * this is not seen by the MMU, it is for our sake so we can 
	 * access them */
	uint64_t vTables[PAGE_TABLE_ENTRIES];

} pagedirectory_t;

/* At the next leve we have Page Directory Table, it has 512 PageDirectory entries */
typedef struct PageDirectoryTable
{
	/* 512 Page tables 
	 * Physical address of each page table is contained here */
	uint64_t pPageDirs[PAGE_TABLE_ENTRIES];

	/* Their virtual mapping 
	 * this is not seen by the MMU, it is for our sake so we can 
	 * access them */
	uint64_t vPageDirs[PAGE_TABLE_ENTRIES];

} pdp_t;

/* The top level, the PML4, it has 512 entries of PageDirectoryTables 
 * Total, this gives us access of 256 Terabytes of memory, since the 
 * physical address space is limited at 48 bits and not actually 64 bit */
typedef struct PML4
{
	/* 512 Page tables 
	 * Physical address of each page table is contained here */
	uint64_t pPageDirPts[PAGE_TABLE_ENTRIES];

	/* Their virtual mapping 
	 * this is not seen by the MMU, it is for our sake so we can 
	 * access them */
	uint64_t vPageDirPts[PAGE_TABLE_ENTRIES];

} pml4_t;

#endif /* KUdos_VM_PAGETABLE_H */
