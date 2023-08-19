<<<<<<< HEAD
# SPDX-License-Identifier: GPL-2.0
# Makefile for kernel virtual machines on s390
#
# Copyright IBM Corp. 2008
=======
# Makefile for kernel virtual machines on s390
#
# Copyright IBM Corp. 2008
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License (version 2 only)
# as published by the Free Software Foundation.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

KVM := ../../../virt/kvm
common-objs = $(KVM)/kvm_main.o $(KVM)/eventfd.o  $(KVM)/async_pf.o $(KVM)/irqchip.o $(KVM)/vfio.o

ccflags-y := -Ivirt/kvm -Iarch/s390/kvm

kvm-objs := $(common-objs) kvm-s390.o intercept.o interrupt.o priv.o sigp.o
<<<<<<< HEAD
kvm-objs += diag.o gaccess.o guestdbg.o vsie.o
=======
kvm-objs += diag.o gaccess.o guestdbg.o sthyi.o vsie.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

obj-$(CONFIG_KVM) += kvm.o
