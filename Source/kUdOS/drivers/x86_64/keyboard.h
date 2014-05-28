/*
 * x86 Keyboard Driver
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
 * $Id: keyboard.h,v 1.0 2014/04/28 20:56:06 Philip Exp $
 *
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <arch.h>

/* x86 Keyboard ports (PS2) */
#define PS2_KEYBOARD_DATA	0x60
#define PS2_KEYBOARD_STATUS	0x64

/* Status Port Bits */
#define PS2_KB_STATUS_OUTPUT_BUSY	0x1
#define PS2_KB_STATUS_INPUT_BUSY	0x2

/* Controller Commands */
#define PS2_KB_SELFTEST		0xAA
#define PS2_KB_INTERFACETEST	0xAB
#define PS2_DISABLE_PORT1	0xAD
#define PS2_DISABLE_PORT2	0xA7

/* Encoder Commands */
#define PS2_KB_SETLEDS		0xED
#define PS2_KB_IDENTIFY		0xF2
#define PS2_KB_ENABLESCAN	0xF4
#define PS2_KB_RESETWAIT	0xF5
#define PS2_KB_RESETSCAN	0xF6
#define PS2_KB_ACK		0xFA
#define PS2_KB_RESET		0xFF

/* Error Codes */
#define PS2_ERR_BAT_FAILED	0xFC
#define PS2_ERR_DIAG_FAILED	0xFD
#define PS2_ERR_RESEND_CMD	0xFE

#define INVALID_SCANCODE	0xFFFF

/* Prototypes */
void keyboard_init();

char keyboard_getkey();

#endif /* TTY_H */
