# SPDX-License-Identifier: GPL-2.0
ifneq '$(CONFIG_H8300_BUILTIN_DTB)' '""'
BUILTIN_DTB := $(patsubst "%",%,$(CONFIG_H8300_BUILTIN_DTB)).dtb.o
endif

obj-y += $(BUILTIN_DTB)

dtb-$(CONFIG_H8300H_SIM) := h8300h_sim.dtb
dtb-$(CONFIG_H8S_SIM) := h8s_sim.dtb
dtb-$(CONFIG_H8S_EDOSK2674) := edosk2674.dtb
<<<<<<< HEAD
=======

dtstree		:= $(srctree)/$(src)
dtb-$(CONFIG_OF_ALL_DTBS) := $(patsubst $(dtstree)/%.dts,%.dtb, $(wildcard $(dtstree)/*.dts))

always	    := $(dtb-y)
clean-files := *.dtb.S *.dtb
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
