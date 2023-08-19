# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the linux kernel.
#

extra-y	:= head.o vmlinux.lds

obj-y	:= setup.o or32_ksyms.o process.o dma.o \
	   traps.o time.o irq.o entry.o ptrace.o signal.o \
<<<<<<< HEAD
	   sys_call_table.o unwinder.o

obj-$(CONFIG_SMP)		+= smp.o sync-timer.o
obj-$(CONFIG_STACKTRACE)	+= stacktrace.o
=======
	   sys_call_table.o

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
obj-$(CONFIG_MODULES)		+= module.o
obj-$(CONFIG_OF)		+= prom.o

clean:
