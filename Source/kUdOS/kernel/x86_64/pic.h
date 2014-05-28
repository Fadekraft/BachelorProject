/*
 * The programmable interrupt controller.
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
 * $Id: pic.h,v 1.0 2003/07/22 19:51:28 philip Exp $
 *
 */

#ifndef __PIC_H__
#define __PIC_H__

/* Includes */
#include "lib/types.h"

/* Defines */

/* We have two PICs, a master and a slave, 
 * and they are capable of 8 interrupt lines each */

/* PIC 1 Interrupts */
#define PIC_IRQ_TIMER			0
#define PIC_IRQ_KEYBOARD		1
#define PIC_IRQ_SERIAL2			3
#define PIC_IRQ_SERIAL1			4
#define PIC_IRQ_PARALLEL2		5
#define PIC_IRQ_FLOPPYDISK		6
#define PIC_IRQ_PARALLEL1		7

/* PIC 2 Interrupts */
#define PIC_IRQ_CMOSTIMER		0
#define PIC_IRQ_CGARETRACE		1
#define PIC_IRQ_AUXILIARY		4
#define PIC_IRQ_FPU			5
#define PIC_IRQ_HDC			6

/* Command words, we use to communicate with PIC */
#define PIC_OCW2_MASK_L1		1
#define PIC_OCW2_MASK_L2		2
#define PIC_OCW2_MASK_L3		4
#define PIC_OCW2_MASK_EOI		0x20
#define PIC_OCW2_MASK_SL		0x40
#define PIC_OCW2_MASK_ROTATE		0x80

#define PIC_OCW3_MASK_RIS		1
#define PIC_OCW3_MASK_RIR		2
#define PIC_OCW3_MASK_MODE		4
#define PIC_OCW3_MASK_SMM		0x20
#define PIC_OCW3_MASK_ESMM		0x40
#define PIC_OCW3_MASK_D7		0x80


/* PIC Port Map
 * Port Address      Description
 *    0x20		Primary PIC Command & Status Register
 *    0x21		Primary PIC Interrupt Mask Register & Data Register
 *    0xA0		Secondary (SLAVE) PIC Command & Status Register
 *    0xA1		Secondary (SLAVE) PIC Interrupt Mask Register & Data Register */

#define PIC0_COMMAND_REGISTER		0x20
#define PIC0_INT_MASK_REGISTER		0x21

#define PIC1_COMMAND_REGISTER		0xA0
#define PIC1_INT_MASK_REGISTER		0xA1

/* Control Word 1 */
#define PIC_ICW1_MASK_IC4		1	/* If set, pic expects IC4 during init */
#define PIC_ICW1_MASK_SNGL		2	/* If set, no slave pic is present */
#define PIC_ICW1_MASK_ADI		4	/* If set, call address interval is 4, default is 
						 * cleared */
#define PIC_ICW1_MASK_LTIM		8	/* If set, level triggered mode is enabled, else
						 * we operate in edge triggered mode */
#define PIC_ICW1_MASK_INIT		0x10	/* Set 1 to initialise PIC */


/* Control Word 4 */
#define PIC_ICW4_MASK_UPM		1	/* If set, it is in x86 mode */
#define PIC_ICW4_MASK_AEOI		2	/* If set, the controller automatically sets 
						 * end of interrupt on the last interrupt pulse */
#define PIC_ICW4_MASK_MS		4	/* If set, selects buffer master, else slave */
#define PIC_ICW4_MASK_BUF		8	/* If set, controller operates in buffer mode */
#define PIC_ICW4_MASK_SFNM		0x10	/* If set, operates in nested mode */




#define PRIMARY_PIC			0
#define SECONDARY_PIC			1



/* Prototypes */
void pic_init();

/* Enable/disable interrupts */
void pic_maskinterrupt(uint8_t irq);
void pic_unmaskinterrupt(uint8_t irq);

/* Acknowledge int */
void pic_eoi(uint8_t irq);


#endif
