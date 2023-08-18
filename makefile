csrc = $(wildcard pcboot/src/*.c) $(wildcard pcboot/src/libc/*.c) $(wildcard pcboot/src/test/*.c)
ssrc = $(wildcard pcboot/src/*.s) $(wildcard pcboot/src/libc/*.s) $(wildcard pcboot/src/boot/*.s) $(wildcard pcboot/src/test/*.s)
Ssrc = $(wildcard pcboot/src/*.S)
qsrc = $(wildcard source/*.c)
obj = $(csrc:.c=.o) $(ssrc:.s=.o) $(Ssrc:.S=.o) $(qsrc:.c=.o)
dep = $(obj:.o=.d)
elf = test
bin = test.bin

warn = -pedantic -Wall
#opt = -O2
dbg = -g
inc = -Ipcboot/src -Ipcboot/src/libc -Ipcboot/src/test
gccopt = -fno-pic -ffreestanding -nostdinc -fno-builtin -ffast-math -fcommon

CFLAGS = $(ccarch) -march=i386 $(warn) $(opt) $(dbg) $(gccopt) $(inc) $(def)
ASFLAGS = $(asarch) -march=i386 $(dbg) -nostdinc -fno-builtin $(inc)
LDFLAGS = $(ldarch) -nostdlib -T pcboot.ld -print-gc-sections

QEMU_FLAGS = -drive file=floppy.img,format=raw,if=floppy -serial file:serial.log -device sb16

ifneq ($(shell uname -m), i386)
	ccarch = -m32
	asarch = --32
	ldarch = -m elf_i386
endif

# uncomment to use a specific toolchain
#TOOLPREFIX = x86_64-elf-

CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)as
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump

floppy.img: boot.img
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$< of=$@ conv=notrunc

pcboot.iso: floppy.img
	rm -rf cdrom
	git archive --format=tar --prefix=cdrom/ HEAD | tar xf -
	cp $< cdrom
	mkisofs -o $@ -R -J -V pcboot -b $< cdrom


boot.img: bootldr.bin $(bin)
	cat bootldr.bin $(bin) >$@

# bootldr.bin will contain .boot, .boot2, .bootend, and .lowtext
bootldr.bin: $(elf)
	$(OBJCOPY) -O binary -j '.boot*' -j .lowtext $< $@

# the main binary will contain every section *except* those
$(bin): $(elf)
	$(OBJCOPY) -O binary -R '.boot*' -R .lowtext $< $@

$(elf): $(obj)
	$(LD) -o $@ $(obj) -Map link.map $(LDFLAGS)

%.o: %.S
	$(CC) -o $@ $(CFLAGS) -c $<

-include $(dep)

%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) $(bin) boot.img floppy.img link.map

.PHONY: cleandep
cleandep:
	rm -f $(dep)

.PHONY: disasm
disasm: bootldr.disasm $(elf).disasm

bootldr.disasm: $(elf)
	$(OBJDUMP) -d $< -j .boot -j .boot2 -m i8086 >$@

$(elf).disasm: $(elf)
	$(OBJDUMP) -d $< -j .startup -j .text -j .lowtext -m i386 >$@

$(elf).sym: $(elf)
	$(OBJCOPY) --only-keep-debug $< $@

.PHONY: run
run: $(bin)
	qemu-system-i386 $(QEMU_FLAGS)

.PHONY: debug
debug: $(bin) $(elf).sym
	qemu-system-i386 $(QEMU_FLAGS) -s -S

.PHONY: sym
sym: $(elf).sym
