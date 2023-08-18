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
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "segm.h"
#include "intr.h"
#include "mem.h"
#include "keyb.h"
#include "psaux.h"
#include "timer.h"
#include "contty.h"
#include "video.h"
#include "audio.h"
#include "pci.h"

#include "quakegeneric.h"
#include "quakekeys.h"

static int argc = 1;
static char *argv[] = {"QuakeOS.bin"};

void QG_Init(void)
{
	/* set video mode */
	set_vga_mode(0x13);
}

int QG_GetKey(int *down, int *key)
{
	return 0;
}

void QG_Quit(void)
{
	set_vga_mode(3);
}

void QG_DrawFrame(void *pixels)
{

}

void QG_SetPalette(unsigned char palette[768])
{

}

void QG_GetMouseMove(int *x, int *y)
{

}

void QG_GetJoyAxes(float *axes)
{

}

void pcboot_main(void)
{
	/* init kernel */
	init_segm();
	init_intr();
	con_init();
	kb_init();
	init_psaux();
	init_mem();
	init_pci();
	init_timer();
	audio_init();
	enable_intr();

	/* init quake */
	QG_Create(argc, argv);

	/* main loop*/
	while (1)
	{
		halt_cpu();
		QG_Tick(0.1);
	}
}
