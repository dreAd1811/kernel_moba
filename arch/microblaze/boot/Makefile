# SPDX-License-Identifier: GPL-2.0
#
# arch/microblaze/boot/Makefile
#

targets := linux.bin linux.bin.gz linux.bin.ub simpleImage.%

OBJCOPYFLAGS := -R .note -R .comment -R .note.gnu.build-id -O binary

$(obj)/linux.bin: vmlinux FORCE
	$(call if_changed,objcopy)
<<<<<<< HEAD
	@echo 'Kernel: $@ is ready' ' (#'`cat .version`')'

$(obj)/linux.bin.ub: $(obj)/linux.bin FORCE
	$(call if_changed,uimage)
	@echo 'Kernel: $@ is ready' ' (#'`cat .version`')'

$(obj)/linux.bin.gz: $(obj)/linux.bin FORCE
	$(call if_changed,gzip)
	@echo 'Kernel: $@ is ready' ' (#'`cat .version`')'
=======

$(obj)/linux.bin.ub: $(obj)/linux.bin FORCE
	$(call if_changed,uimage)

$(obj)/linux.bin.gz: $(obj)/linux.bin FORCE
	$(call if_changed,gzip)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

quiet_cmd_cp = CP      $< $@$2
	cmd_cp = cat $< >$@$2 || (rm -f $@ && echo false)

quiet_cmd_strip = STRIP   $< $@$2
	cmd_strip = $(STRIP) -K microblaze_start -K _end -K __log_buf \
				-K _fdt_start $< -o $@$2

UIMAGE_LOADADDR = $(CONFIG_KERNEL_BASE_ADDR)
UIMAGE_IN = $@
UIMAGE_OUT = $@.ub

$(obj)/simpleImage.%: vmlinux FORCE
	$(call if_changed,cp,.unstrip)
	$(call if_changed,objcopy)
	$(call if_changed,uimage)
	$(call if_changed,strip,.strip)
<<<<<<< HEAD
	@echo 'Kernel: $(UIMAGE_OUT) is ready' ' (#'`cat .version`')'

clean-files += simpleImage.*.unstrip linux.bin.ub
=======

clean-files += simpleImage.*.unstrip linux.bin.ub dts/*.dtb
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
