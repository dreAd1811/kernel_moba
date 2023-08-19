# SPDX-License-Identifier: GPL-2.0
ccflags-$(CONFIG_PPC64)			:= $(NO_MINIMAL_TOC)
ccflags-$(CONFIG_PPC_PSERIES_DEBUG)	+= -DDEBUG

obj-y			:= lpar.o hvCall.o nvram.o reconfig.o \
			   of_helpers.o \
			   setup.o iommu.o event_sources.o ras.o \
			   firmware.o power.o dlpar.o mobility.o rng.o \
			   pci.o pci_dlpar.o eeh_pseries.o msi.o
obj-$(CONFIG_SMP)	+= smp.o
obj-$(CONFIG_SCANLOG)	+= scanlog.o
obj-$(CONFIG_KEXEC_CORE)	+= kexec.o
obj-$(CONFIG_PSERIES_ENERGY)	+= pseries_energy.o

obj-$(CONFIG_HOTPLUG_CPU)	+= hotplug-cpu.o
obj-$(CONFIG_MEMORY_HOTPLUG)	+= hotplug-memory.o

obj-$(CONFIG_HVC_CONSOLE)	+= hvconsole.o
obj-$(CONFIG_HVCS)		+= hvcserver.o
obj-$(CONFIG_HCALL_STATS)	+= hvCall_inst.o
obj-$(CONFIG_CMM)		+= cmm.o
obj-$(CONFIG_DTL)		+= dtl.o
obj-$(CONFIG_IO_EVENT_IRQ)	+= io_event_irq.o
obj-$(CONFIG_LPARCFG)		+= lparcfg.o
obj-$(CONFIG_IBMVIO)		+= vio.o
obj-$(CONFIG_IBMEBUS)		+= ibmebus.o

<<<<<<< HEAD
ifdef CONFIG_PPC_PSERIES
=======
ifeq ($(CONFIG_PPC_PSERIES),y)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
obj-$(CONFIG_SUSPEND)		+= suspend.o
endif
