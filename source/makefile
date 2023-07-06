
CC ?= gcc
RM ?= rm -f

CFLAGS += -g3 -m32 -Dstricmp=strcasecmp -std=gnu99 -lm

SDL2 = quakegeneric_sdl2.c $(shell sdl2-config --libs --cflags)

SOURCES = \
	cd_null.c \
	chase.c \
	cl_demo.c \
	cl_input.c \
	cl_main.c \
	cl_parse.c \
	cl_tent.c \
	cmd.c \
	common.c \
	console.c \
	crc.c \
	cvar.c \
	d_edge.c \
	d_fill.c \
	d_init.c \
	d_modech.c \
	d_part.c \
	d_polyse.c \
	d_scan.c \
	d_sky.c \
	d_sprite.c \
	d_surf.c \
	d_vars.c \
	d_zpoint.c \
	draw.c \
	host_cmd.c \
	host.c \
	in_null.c \
	keys.c \
	mathlib.c \
	menu.c \
	model.c \
	net_loop.c \
	net_main.c \
	net_none.c \
	net_vcr.c \
	nonintel.c \
	pr_cmds.c \
	pr_edict.c \
	pr_exec.c \
	r_aclip.c \
	r_alias.c \
	r_bsp.c \
	r_draw.c \
	r_edge.c \
	r_efrag.c \
	r_light.c \
	r_main.c \
	r_misc.c \
	r_part.c \
	r_sky.c \
	r_sprite.c \
	r_surf.c \
	r_vars.c \
	sbar.c \
	screen.c \
	snd_null.c \
	sv_main.c \
	sv_move.c \
	sv_phys.c \
	sv_user.c \
	sys_null.c \
	vid_null.c \
	view.c \
	wad.c \
	world.c \
	zone.c \
	quakegeneric.c \

all: clean quakegeneric

clean:
	$(RM) *.o quakegeneric

quakegeneric: $(SOURCES)
	$(CC) -o quakegeneric $(SOURCES) $(SDL2) $(CFLAGS)
