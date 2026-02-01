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
#include <sys/mman.h>
#include <errno.h>

void QG_Tick(double duration)
{
	Host_Frame(duration);
}

void *QG_Alloc(size_t sz)
{
#ifdef __64
	size_t mmapsize = ((size_t)sz + (65536U - 1)) & ~(65536U - 1);
	void *ret = mmap(NULL, mmapsize, PROT_READ | PROT_WRITE, MAP_32BIT | MAP_ANON | MAP_PRIVATE, 0, 0);
	uintptr_t base = 0U;
	while(ret == MAP_FAILED)
	{
		base += 16U * 1024 * 1024;		// start at 16 MiB and try increasing addresses
		if(base >= 0x100000000U)
		{
			// abort
			return NULL;
		}
		ret = mmap((void *)base, mmapsize, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_ANON | MAP_PRIVATE, 0, 0);
	}
	if(ret == MAP_FAILED)
	{
		return NULL;
	}
	return ret;
#else
	return malloc(sz);
#endif
}

#define	MAX_MOD_KNOWN	256
extern model_t	*mod_known;

void QG_Create(int argc, char *argv[])
{
	static quakeparms_t    parms;

	parms.memsize = 8*1024*1024;

	parms.membase = QG_Alloc(parms.memsize);
	sv = QG_Alloc(sizeof(server_t));
	mod_known = QG_Alloc(MAX_MOD_KNOWN * sizeof(model_t));

	parms.basedir = ".";

	COM_InitArgv (argc, argv);

	parms.argc = com_argc;
	parms.argv = com_argv;

	printf ("Host_Init\n");
	Host_Init (&parms);
}
