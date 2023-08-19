# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
subdir-y += actions
subdir-y += al
subdir-y += allwinner
subdir-y += altera
subdir-y += amd
subdir-y += amlogic
subdir-y += apm
subdir-y += arm
subdir-y += broadcom
subdir-y += cavium
subdir-y += exynos
subdir-y += freescale
subdir-y += hisilicon
subdir-y += lg
subdir-y += marvell
subdir-y += mediatek
subdir-y += nvidia
subdir-y += qcom
subdir-y += realtek
subdir-y += renesas
subdir-y += rockchip
subdir-y += socionext
subdir-y += sprd
subdir-y += synaptics
subdir-y += ti
subdir-y += xilinx
subdir-y += zte


dtstree		:= $(srctree)/$(src)

vendor := $(dtstree)/vendor
ifneq "$(wildcard $(vendor)/Makefile)" ""
        subdir-y += vendor
endif

dtb-$(CONFIG_OF_ALL_DTBS) := $(patsubst $(dtstree)/%.dts,%.dtb, $(foreach d,$(subdir), $(wildcard $(dtstree)/$(d)/*.dts)))
=======
dts-dirs += actions
dts-dirs += al
dts-dirs += allwinner
dts-dirs += altera
dts-dirs += amd
dts-dirs += amlogic
dts-dirs += apm
dts-dirs += arm
dts-dirs += broadcom
dts-dirs += cavium
dts-dirs += exynos
dts-dirs += freescale
dts-dirs += hisilicon
dts-dirs += marvell
dts-dirs += mediatek
dts-dirs += nvidia
dts-dirs += qcom
dts-dirs += realtek
dts-dirs += renesas
dts-dirs += rockchip
dts-dirs += socionext
dts-dirs += sprd
dts-dirs += xilinx
dts-dirs += lg
dts-dirs += zte

subdir-y	:= $(dts-dirs)

dtstree		:= $(srctree)/$(src)

dtb-$(CONFIG_OF_ALL_DTBS) := $(patsubst $(dtstree)/%.dts,%.dtb, $(foreach d,$(dts-dirs), $(wildcard $(dtstree)/$(d)/*.dts)))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

always		:= $(dtb-y)

targets += dtbs

DTB_NAMES := $(subst $\",,$(CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE_NAMES))
ifneq ($(DTB_NAMES),)
DTB_LIST := $(addsuffix .dtb,$(DTB_NAMES))
else
DTB_LIST := $(dtb-y)
endif
targets += $(DTB_LIST)

dtbs: $(addprefix $(obj)/, $(DTB_LIST))

clean-files := dts/*.dtb *.dtb
