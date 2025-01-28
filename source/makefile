
RM?=rm -f
PKGCONFIG?=pkg-config

LIBEXT?=.a
BINEXT?=
OBJEXT?=.o

ifeq ($(CC),tcc)
override CFLAGS+=-DSDL_DISABLE_IMMINTRIN_H=1
endif

ifeq ($(DEBUG),1)
override CFLAGS+=-g -O0
endif

ifeq ($(PARANOID),1)
override CFLAGS+=-fsanitize=address,undefined -Wall -Wextra -pedantic
override LDFLAGS+=-fsanitize=address,undefined
endif

ifeq ($(RELEASE),1)
override CFLAGS+=-O3
override LDFLAGS+=-O3
endif

override CFLAGS+=-m32 -std=gnu99 $(shell $(PKGCONFIG) sdl2 --cflags)
override LDFLAGS+=-m32 -lm $(shell $(PKGCONFIG) sdl2 --libs)

EXECNAME?=quakegeneric$(BINEXT)
LIBNAME?=libquakegeneric$(LIBEXT)

OBJS = \
	cd_null$(OBJEXT) chase$(OBJEXT) cl_demo$(OBJEXT) cl_input$(OBJEXT) \
	cl_main$(OBJEXT) cl_parse$(OBJEXT) cl_tent$(OBJEXT) cmd$(OBJEXT) \
	common$(OBJEXT) console$(OBJEXT) crc$(OBJEXT) cvar$(OBJEXT) \
	d_edge$(OBJEXT) d_fill$(OBJEXT) d_init$(OBJEXT) d_modech$(OBJEXT) \
	d_part$(OBJEXT) d_polyse$(OBJEXT) d_scan$(OBJEXT) d_sky$(OBJEXT) \
	d_sprite$(OBJEXT) d_surf$(OBJEXT) d_vars$(OBJEXT) d_zpoint$(OBJEXT) \
	draw$(OBJEXT) host_cmd$(OBJEXT) host$(OBJEXT) in_null$(OBJEXT) \
	keys$(OBJEXT) mathlib$(OBJEXT) menu$(OBJEXT) model$(OBJEXT) \
	net_loop$(OBJEXT) net_main$(OBJEXT) net_none$(OBJEXT) net_vcr$(OBJEXT) \
	nonintel$(OBJEXT) pr_cmds$(OBJEXT) pr_edict$(OBJEXT) pr_exec$(OBJEXT) \
	r_aclip$(OBJEXT) r_alias$(OBJEXT) r_bsp$(OBJEXT) r_draw$(OBJEXT) \
	r_edge$(OBJEXT) r_efrag$(OBJEXT) r_light$(OBJEXT) r_main$(OBJEXT) \
	r_misc$(OBJEXT) r_part$(OBJEXT) r_sky$(OBJEXT) r_sprite$(OBJEXT) \
	r_surf$(OBJEXT) r_vars$(OBJEXT) sbar$(OBJEXT) screen$(OBJEXT) \
	snd_null$(OBJEXT) sv_main$(OBJEXT) sv_move$(OBJEXT) sv_phys$(OBJEXT) \
	sv_user$(OBJEXT) sys_null$(OBJEXT) vid_null$(OBJEXT) view$(OBJEXT) \
	wad$(OBJEXT) world$(OBJEXT) zone$(OBJEXT) quakegeneric$(OBJEXT)

OBJS_SDL2=quakegeneric_sdl2$(OBJEXT)

all: $(EXECNAME) $(LIBNAME)

clean:
	$(RM) $(OBJS)

$(EXECNAME): $(OBJS) $(OBJS_SDL2)
	$(CC) -o $@ $(OBJS) $(OBJS_SDL2) $(LDFLAGS)

$(LIBNAME): $(OBJS)
	$(AR) rcs $@ $(OBJS)
