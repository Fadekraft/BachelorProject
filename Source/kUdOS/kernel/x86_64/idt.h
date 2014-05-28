/*
 * The interrupt descriptor table.
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
 * $Id: idt.h,v 1.0 2003/07/22 19:51:28 philip Exp $
 *
 */

#ifndef __IDT_H__
#define __IDT_H__

/* Includes */
#include "lib/types.h"

/* Defines */
#define IDT_DESC_BIT16			0x07	//16 Bit
#define IDT_DESC_BIT32			0x0F	//32 Bit Trap Gate
#define IDT_DESC_RING1			0x40	//Priveligie Level 1
#define IDT_DESC_RING2			0x20	//Priveligie Level 2
#define IDT_DESC_RING3			0x60	//Priveligie Level 3
#define IDT_DESC_PRESENT		0x80	//Is it present? 

/* Callback Type (Interrupt) */
typedef void (*IrqHandler)();

/* Structures */
#define MAX_INTERRUPTS			0xFF

/* IDT Descriptor */
typedef struct IdtDescriptor
{
	/* Base Bits 0..15 */
	uint16_t BaseLow;

	/* Selector (Code Segment) */
	uint16_t Selector;

	/* Reserved */
	uint8_t Reserved0;

	/* Attributes */
	uint8_t Flags;

	/* Base Bits 16..31 */
	uint16_t BaseMid;

	/* Base Bits 32..63 */
	uint32_t BaseHigh;

	/* Reserved */
	uint32_t Reserved1;

} __attribute__((packed)) idt_desc_t;

/* Interrupt Descriptor Table */
typedef struct IdTable
{
	/* Size of IDT */
	uint16_t Limit;

	/* Base Address of IDT */
	uint64_t Base;

} __attribute__((packed)) idt_t;

/* Prototypes */
void idt_init();

void idt_install_gate(uint32_t index, uint16_t flags, uint16_t selector, IrqHandler Irq);


#endif




