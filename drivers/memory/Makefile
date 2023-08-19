# SPDX-License-Identifier: GPL-2.0
#
# Makefile for memory devices
#

ifeq ($(CONFIG_DDR),y)
obj-$(CONFIG_OF)		+= of_memory.o
endif
obj-$(CONFIG_ARM_PL172_MPMC)	+= pl172.o
obj-$(CONFIG_ATMEL_SDRAMC)	+= atmel-sdramc.o
obj-$(CONFIG_ATMEL_EBI)		+= atmel-ebi.o
<<<<<<< HEAD
obj-$(CONFIG_ARCH_BRCMSTB)	+= brcmstb_dpfe.o
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
obj-$(CONFIG_TI_AEMIF)		+= ti-aemif.o
obj-$(CONFIG_TI_EMIF)		+= emif.o
obj-$(CONFIG_OMAP_GPMC)		+= omap-gpmc.o
obj-$(CONFIG_FSL_CORENET_CF)	+= fsl-corenet-cf.o
obj-$(CONFIG_FSL_IFC)		+= fsl_ifc.o
obj-$(CONFIG_MVEBU_DEVBUS)	+= mvebu-devbus.o
<<<<<<< HEAD
=======
obj-$(CONFIG_TEGRA20_MC)	+= tegra20-mc.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
obj-$(CONFIG_JZ4780_NEMC)	+= jz4780-nemc.o
obj-$(CONFIG_MTK_SMI)		+= mtk-smi.o
obj-$(CONFIG_DA8XX_DDRCTL)	+= da8xx-ddrctl.o

obj-$(CONFIG_SAMSUNG_MC)	+= samsung/
obj-$(CONFIG_TEGRA_MC)		+= tegra/
<<<<<<< HEAD
obj-$(CONFIG_TI_EMIF_SRAM)	+= ti-emif-sram.o
ti-emif-sram-objs		:= ti-emif-pm.o ti-emif-sram-pm.o

AFLAGS_ti-emif-sram-pm.o	:=-Wa,-march=armv7-a

include drivers/memory/Makefile.asm-offsets

drivers/memory/ti-emif-sram-pm.o: include/generated/ti-emif-asm-offsets.h
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
