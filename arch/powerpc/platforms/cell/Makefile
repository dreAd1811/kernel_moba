# SPDX-License-Identifier: GPL-2.0
obj-$(CONFIG_PPC_CELL_COMMON)		+= cbe_regs.o interrupt.o pervasive.o

obj-$(CONFIG_PPC_CELL_NATIVE)		+= iommu.o setup.o spider-pic.o \
					   pmu.o spider-pci.o
obj-$(CONFIG_CBE_RAS)			+= ras.o

obj-$(CONFIG_CBE_THERM)			+= cbe_thermal.o
obj-$(CONFIG_CBE_CPUFREQ_SPU_GOVERNOR)	+= cpufreq_spudemand.o

obj-$(CONFIG_PPC_IBM_CELL_POWERBUTTON)	+= cbe_powerbutton.o

<<<<<<< HEAD
ifdef CONFIG_SMP
=======
ifeq ($(CONFIG_SMP),y)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
obj-$(CONFIG_PPC_CELL_NATIVE)		+= smp.o
endif

# needed only when building loadable spufs.ko
spu-priv1-$(CONFIG_PPC_CELL_COMMON)	+= spu_priv1_mmio.o
spu-manage-$(CONFIG_PPC_CELL_COMMON)	+= spu_manage.o

obj-$(CONFIG_SPU_BASE)			+= spu_callbacks.o spu_base.o \
					   spu_notify.o \
					   spu_syscalls.o \
					   $(spu-priv1-y) \
					   $(spu-manage-y) \
					   spufs/

obj-$(CONFIG_AXON_MSI)			+= axon_msi.o
