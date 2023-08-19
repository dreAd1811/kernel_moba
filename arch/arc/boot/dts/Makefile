# SPDX-License-Identifier: GPL-2.0
# Built-in dtb
builtindtb-y		:= nsim_700

ifneq ($(CONFIG_ARC_BUILTIN_DTB_NAME),"")
	builtindtb-y	:= $(patsubst "%",%,$(CONFIG_ARC_BUILTIN_DTB_NAME))
endif

obj-y   += $(builtindtb-y).dtb.o
dtb-y := $(builtindtb-y).dtb

<<<<<<< HEAD
# for CONFIG_OF_ALL_DTBS test
dtstree	:= $(srctree)/$(src)
dtb-	:= $(patsubst $(dtstree)/%.dts,%.dtb, $(wildcard $(dtstree)/*.dts))
=======
.SECONDARY: $(obj)/$(builtindtb-y).dtb.S

dtstree		:= $(srctree)/$(src)
dtb-$(CONFIG_OF_ALL_DTBS) := $(patsubst $(dtstree)/%.dts,%.dtb, $(wildcard $(dtstree)/*.dts))

always := $(dtb-y)
clean-files := *.dtb  *.dtb.S
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
