/*
pcboot - bootable PC demo/game kernel
Copyright (C) 2018  John Tsiombikas <nuclear@member.fsf.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY, without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef INT86_H_
#define INT86_H_

#include <inttypes.h>

struct int86regs {
	uint32_t edi, esi, ebp, esp;
	uint32_t ebx, edx, ecx, eax;
	uint16_t flags;
	uint16_t es, ds, fs, gs;
} __attribute__ ((packed));

#define FLAGS_CARRY		0x0001
#define FLAGS_PARITY	0x0004
#define FLAGS_AUXC		0x0010
#define FLAGS_ZERO		0x0040
#define FLAGS_SIGN		0x0080
#define FLAGS_TRAP		0x0100
#define FLAGS_INTR		0x0200
#define FLAGS_DIR		0x0400
#define FLAGS_OVF		0x0800
#define FLAGS_SIOPL(x)	(((uint16_t)(x) & 3) << 12)
#define FLAGS_GIOPL(x)	(((x) >> 12) & 3)
#define FLAGS_NTASK		0x4000

void int86(int inum, struct int86regs *regs);

#endif	/* INT86_H_ */
