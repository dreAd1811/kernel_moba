<<<<<<< HEAD
# SPDX-License-Identifier: GPL-2.0
# Copyright(c) 2013 - 2018 Intel Corporation.
=======
################################################################################
#
# Intel(R) Ethernet Switch Host Interface Driver
# Copyright(c) 2013 - 2016 Intel Corporation.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms and conditions of the GNU General Public License,
# version 2, as published by the Free Software Foundation.
#
# This program is distributed in the hope it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# The full GNU General Public License is included in this distribution in
# the file called "COPYING".
#
# Contact Information:
# e1000-devel Mailing List <e1000-devel@lists.sourceforge.net>
# Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
#
################################################################################
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#
# Makefile for the Intel(R) Ethernet Switch Host Interface Driver
#

obj-$(CONFIG_FM10K) += fm10k.o

fm10k-y := fm10k_main.o \
	   fm10k_common.o \
	   fm10k_pci.o \
	   fm10k_netdev.o \
	   fm10k_ethtool.o \
	   fm10k_pf.o \
	   fm10k_vf.o \
	   fm10k_mbx.o \
	   fm10k_iov.o \
	   fm10k_tlv.o

fm10k-$(CONFIG_DEBUG_FS) += fm10k_debugfs.o
fm10k-$(CONFIG_DCB) += fm10k_dcbnl.o
