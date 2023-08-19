# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
subdir-y	+= brcm
subdir-y	+= cavium-octeon
subdir-y	+= img
subdir-y	+= ingenic
subdir-y	+= lantiq
subdir-y	+= mscc
subdir-y	+= mti
subdir-y	+= netlogic
subdir-y	+= ni
subdir-y	+= pic32
subdir-y	+= qca
subdir-y	+= ralink
subdir-y	+= xilfpga

obj-$(CONFIG_BUILTIN_DTB)	:= $(addsuffix /, $(subdir-y))
=======
dts-dirs	+= brcm
dts-dirs	+= cavium-octeon
dts-dirs	+= img
dts-dirs	+= ingenic
dts-dirs	+= lantiq
dts-dirs	+= mti
dts-dirs	+= netlogic
dts-dirs	+= ni
dts-dirs	+= pic32
dts-dirs	+= qca
dts-dirs	+= ralink
dts-dirs	+= xilfpga

obj-y		:= $(addsuffix /, $(dts-dirs))

dtstree		:= $(srctree)/$(src)
dtb-$(CONFIG_OF_ALL_DTBS) := $(patsubst $(dtstree)/%.dts,%.dtb, $(foreach d,$(dts-dirs), $(wildcard $(dtstree)/$(d)/*.dts)))

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb *.dtb.S
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
