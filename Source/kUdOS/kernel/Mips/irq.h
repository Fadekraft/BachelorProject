/*
 * Internal interrupt rutines (arch-specific)
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
 * $Id: irq.h,v 1.9 2003/07/22 19:51:28 ttakanen Exp $
 *
 */

#ifndef KUDOS_KERNEL_INTERRUPT_H
#define KUDOS_KERNEL_INTERRUPT_H

#include "lib/types.h"
#include "drivers/device.h"

/* CAUSE register bits */

#define INTERRUPT_CAUSE_SOFTWARE_0 (1<<8)
#define INTERRUPT_CAUSE_SOFTWARE_1 (1<<9)
#define INTERRUPT_CAUSE_HARDWARE_0 (1<<10)
#define INTERRUPT_CAUSE_HARDWARE_1 (1<<11)
#define INTERRUPT_CAUSE_HARDWARE_2 (1<<12)
#define INTERRUPT_CAUSE_HARDWARE_3 (1<<13)
#define INTERRUPT_CAUSE_HARDWARE_4 (1<<14)
#define INTERRUPT_CAUSE_HARDWARE_5 (1<<15)


#define INTERRUPT_MASK_MASTER 0x1
#define INTERRUPT_MASK_SOFTWARE_0 INTERRUPT_CAUSE_SOFTWARE_0
#define INTERRUPT_MASK_SOFTWARE_1 INTERRUPT_CAUSE_SOFTWARE_1
#define INTERRUPT_MASK_HARDWARE_0 INTERRUPT_CAUSE_HARDWARE_0
#define INTERRUPT_MASK_HARDWARE_1 INTERRUPT_CAUSE_HARDWARE_1
#define INTERRUPT_MASK_HARDWARE_2 INTERRUPT_CAUSE_HARDWARE_2
#define INTERRUPT_MASK_HARDWARE_3 INTERRUPT_CAUSE_HARDWARE_3
#define INTERRUPT_MASK_HARDWARE_4 INTERRUPT_CAUSE_HARDWARE_4
#define INTERRUPT_MASK_HARDWARE_5 INTERRUPT_CAUSE_HARDWARE_5
#define INTERRUPT_MASK_ALL 0xff00
#define INTERRUPT_MASK_SOFTWARE 0x0300
#define INTERRUPT_MASK_HARDWARE 0xfc00

/* data types */
typedef uint32_t interrupt_status_t;

/* Interrupt type */
typedef void (*int_handler_t)(device_t*);

/* Arch Specific */
void _interrupt_clear_bootstrap(void);
void _interrupt_clear_sw(void);
void _interrupt_clear_sw0(void);
void _interrupt_clear_sw1(void);

void _interrupt_set_EXL(void);
void _interrupt_clear_EXL(void);

#endif /* KUdos_KERNEL_INTERRUPT_H */
