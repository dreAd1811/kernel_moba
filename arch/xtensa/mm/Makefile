#
# Makefile for the Linux/Xtensa-specific parts of the memory manager.
#

obj-y			:= init.o misc.o
obj-$(CONFIG_MMU)	+= cache.o fault.o ioremap.o mmu.o tlb.o
obj-$(CONFIG_HIGHMEM)	+= highmem.o
<<<<<<< HEAD
obj-$(CONFIG_KASAN)	+= kasan_init.o

KASAN_SANITIZE_fault.o := n
KASAN_SANITIZE_kasan_init.o := n
KASAN_SANITIZE_mmu.o := n
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
