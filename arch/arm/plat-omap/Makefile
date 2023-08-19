#
# Makefile for the linux kernel.
#

ccflags-$(CONFIG_ARCH_MULTIPLATFORM) := -I$(srctree)/arch/arm/plat-omap/include

# Common support
obj-y := sram.o dma.o counter_32k.o

# omap_device support (OMAP2+ only at the moment)

<<<<<<< HEAD
=======
obj-$(CONFIG_OMAP_DM_TIMER) += dmtimer.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
obj-$(CONFIG_OMAP_DEBUG_LEDS) += debug-leds.o
