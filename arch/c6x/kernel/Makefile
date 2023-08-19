# SPDX-License-Identifier: GPL-2.0
#
# Makefile for arch/c6x/kernel/
#

extra-y := head.o vmlinux.lds

obj-y := process.o traps.o irq.o signal.o ptrace.o
obj-y += setup.o sys_c6x.o time.o devicetree.o
obj-y += switch_to.o entry.o vectors.o c6x_ksyms.o
<<<<<<< HEAD
obj-y += soc.o
=======
obj-y += soc.o dma.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

obj-$(CONFIG_MODULES)           += module.o
