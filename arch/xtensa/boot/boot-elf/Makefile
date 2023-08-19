#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

ifeq ($(BIG_ENDIAN),1)
OBJCOPY_ARGS    := -O elf32-xtensa-be
else
OBJCOPY_ARGS    := -O elf32-xtensa-le
endif

export OBJCOPY_ARGS
export CPPFLAGS_boot.lds += -P -C
export KBUILD_AFLAGS += -mtext-section-literals

boot-y		:= bootstrap.o

OBJS		:= $(addprefix $(obj)/,$(boot-y))

$(obj)/Image.o: vmlinux.bin $(OBJS)
	$(Q)$(OBJCOPY) $(OBJCOPY_ARGS) -R .comment \
		--add-section image=vmlinux.bin \
		--set-section-flags image=contents,alloc,load,load,data \
		$(OBJS) $@

$(obj)/../Image.elf: $(obj)/Image.o $(obj)/boot.lds
<<<<<<< HEAD
	$(Q)$(LD) $(KBUILD_LDFLAGS) $(LDFLAGS_vmlinux) \
=======
	$(Q)$(LD) $(LDFLAGS) $(LDFLAGS_vmlinux) \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		-T $(obj)/boot.lds \
		--build-id=none \
		-o $@ $(obj)/Image.o
	$(Q)$(kecho) '  Kernel: $@ is ready'

all Image: $(obj)/../Image.elf
