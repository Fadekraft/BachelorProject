/*
 * The pci interface
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
 * $Id: pci.h,v 1.0 2014/04/28 20:56:06 Philip Exp $
 *
 */

#ifndef __PCI_H__
#define __PCI_H__

/* Includes */
#include "lib/types.h"

/* Defines */

/* Structures */
typedef struct pci_conf_space
{
	/* Offset 0x0 */
	uint16_t vendor_id;
	uint16_t device_id;

	/* Offset 0x4 */
	uint16_t command;
	uint16_t status;

	/* Offset 0x8 */
	uint8_t revision;
	uint8_t prog_if;
	uint8_t subclass;
	uint8_t classcode;

	/* Offset 0xC */
	uint8_t cache_size;
	uint8_t latency_timer;
	uint8_t header_type;
	uint8_t bist;

	/* Offset 0x10 */
	uint32_t bar0;

	/* Offset 0x14 */
	uint32_t bar1;

	/* Offset 0x18 */
	uint32_t bar2;

	/* Offset 0x1C */
	uint32_t bar3;

	/* Offset 0x20 */
	uint32_t bar4;

	/* Offset 0x24 */
	uint32_t bar5;

	/* Offset 0x28 */
	uint32_t cis_pointer;

	/* Offset 0x2C */
	uint16_t sub_vendor_id;
	uint16_t sub_id;

	/* Offset 0x30 */
	uint32_t rom_base_addr;

	/* Offset 0x34 */
	uint64_t Reserved;

	/* Offset 0x3C */
	uint8_t irq_line;
	uint8_t irq_pin;
	uint8_t min_grant;
	uint8_t max_latency;

} __attribute__((packed)) pci_conf_t;

#endif
