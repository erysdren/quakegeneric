/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "quakedef.h"

void QG_Tick(double duration)
{
	Host_Frame(duration);
}

/* Quake uses eval_t members to point to the string table.  For compatibility with loading
	from disk these pointers are 4 bytes.

	The string table is allocated on the heap.  The pointers can come from the
	heap itself as well as the sv.world_view member, the mod_known array and
	the pr_string_temp buffer.

	For 32-bits the offset pointers will always be 32-bit, and can be positive or
	negative as the address space will wraparound.

	For 64-bits, however, we need the offsets to be within 2 GiB and positive else
	they will point to an invalid address.

	We therefore dynamically allocate sv, mod_known and pr_string_temp to ensure
	that they are close together, and in the correct order */

#define	MAX_MOD_KNOWN	256
extern model_t	*mod_known;
extern char *pr_string_temp;

#define	MAX_MOD_KNOWN	256
extern model_t	*mod_known;
extern char *pr_string_temp;

void QG_Create(int argc, char *argv[])
{
	static quakeparms_t    parms;

	parms.memsize = 8*1024*1024;

	parms.membase = malloc(parms.memsize + sizeof(server_t) +
		MAX_MOD_KNOWN * sizeof(model_t) + 128);

	sv = (server_t *)((byte *)parms.membase + parms.memsize);
	mod_known = (model_t *)((byte *)sv + sizeof(server_t));
	pr_string_temp = (char *)((byte *)mod_known + MAX_MOD_KNOWN * sizeof(model_t));

	parms.basedir = ".";

	COM_InitArgv (argc, argv);

	parms.argc = com_argc;
	parms.argv = com_argv;

	printf ("Host_Init\n");
	Host_Init (&parms);
}
