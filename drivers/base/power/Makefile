# SPDX-License-Identifier: GPL-2.0
obj-$(CONFIG_PM)	+= sysfs.o generic_ops.o common.o qos.o runtime.o wakeirq.o
<<<<<<< HEAD
obj-$(CONFIG_PM_SLEEP)	+= main.o wakeup.o
obj-$(CONFIG_PM_TRACE_RTC)	+= trace.o
=======
obj-$(CONFIG_PM_SLEEP)	+= main.o wakeup.o wakeup_stats.o
obj-$(CONFIG_PM_TRACE_RTC)	+= trace.o
obj-$(CONFIG_PM_OPP)	+= opp/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
obj-$(CONFIG_PM_GENERIC_DOMAINS)	+=  domain.o domain_governor.o
obj-$(CONFIG_HAVE_CLK)	+= clock_ops.o

ccflags-$(CONFIG_DEBUG_DRIVER) := -DDEBUG
