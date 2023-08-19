# SPDX-License-Identifier: GPL-2.0
#
# Makefile for device trees
#

DTC_FLAGS ?= -p 1024

ifneq ($(DTB),)
obj-y += linked_dtb.o
endif

quiet_cmd_cp = CP      $< $@$2
	cmd_cp = cat $< >$@$2 || (rm -f $@ && echo false)

# Generate builtin.dtb from $(DTB).dtb
$(obj)/builtin.dtb: $(obj)/$(DTB).dtb
	$(call if_changed,cp)

$(obj)/linked_dtb.o: $(obj)/builtin.dtb
<<<<<<< HEAD
=======

clean-files := *.dtb
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
