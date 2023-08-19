# SPDX-License-Identifier: GPL-2.0
ccflags-y			:= $(call cc-disable-warning, unused-const-variable)
ccflags-$(CONFIG_PPC_WERROR)	+= -Werror

cxl-y				+= main.o file.o irq.o fault.o native.o
cxl-y				+= context.o sysfs.o pci.o trace.o
<<<<<<< HEAD
cxl-y				+= vphb.o api.o cxllib.o
=======
cxl-y				+= vphb.o phb.o api.o cxllib.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
cxl-$(CONFIG_PPC_PSERIES)	+= flash.o guest.o of.o hcalls.o
cxl-$(CONFIG_DEBUG_FS)		+= debugfs.o
obj-$(CONFIG_CXL)		+= cxl.o
obj-$(CONFIG_CXL_BASE)		+= base.o

# For tracepoints to include our trace.h from tracepoint infrastructure:
CFLAGS_trace.o := -I$(src)
