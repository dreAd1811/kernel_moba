# SPDX-License-Identifier: GPL-2.0
#
# Makefile
#

ifdef CONFIG_FUNCTION_TRACER
# Do not trace early boot code and low level code
CFLAGS_REMOVE_timer.o = -pg
CFLAGS_REMOVE_intc.o = -pg
CFLAGS_REMOVE_early_printk.o = -pg
<<<<<<< HEAD
=======
CFLAGS_REMOVE_heartbeat.o = -pg
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
CFLAGS_REMOVE_ftrace.o = -pg
CFLAGS_REMOVE_process.o = -pg
endif

extra-y := head.o vmlinux.lds

obj-y += dma.o exceptions.o \
	hw_exception_handler.o irq.o \
<<<<<<< HEAD
	process.o prom.o ptrace.o \
=======
	platform.o process.o prom.o ptrace.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	reset.o setup.o signal.o sys_microblaze.o timer.o traps.o unwind.o

obj-y += cpu/

<<<<<<< HEAD
=======
obj-$(CONFIG_EARLY_PRINTK)	+= early_printk.o
obj-$(CONFIG_HEART_BEAT)	+= heartbeat.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
obj-$(CONFIG_MODULES)		+= microblaze_ksyms.o module.o
obj-$(CONFIG_MMU)		+= misc.o
obj-$(CONFIG_STACKTRACE)	+= stacktrace.o
obj-$(CONFIG_FUNCTION_TRACER)	+= ftrace.o mcount.o
obj-$(CONFIG_KGDB)		+= kgdb.o

obj-y	+= entry$(MMU).o
