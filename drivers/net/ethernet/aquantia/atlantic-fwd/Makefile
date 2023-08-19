<<<<<<< HEAD
################################################################################
#
# aQuantia Ethernet Controller AQtion Linux Driver
# Copyright(c) 2014-2017 aQuantia Corporation.
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
# You should have received a copy of the GNU General Public License along
# with this program. If not, see <http://www.gnu.org/licenses/>.
#
# The full GNU General Public License is included in this distribution in
# the file called "COPYING".
#
# Contact Information: <rdc-drv@aquantia.com>
# aQuantia Corporation, 105 E. Tasman Dr. San Jose, CA 95134, USA
#
################################################################################

#
# Makefile for the AQtion(tm) Ethernet driver
#
=======
# SPDX-License-Identifier: GPL-2.0-only
# Atlantic Network Driver
#
# Copyright(c) 2014-2019 aQuantia Corporation.
# Copyright(c) 2019-2020 Marvell International Ltd.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

obj-$(CONFIG_AQFWD) += atlantic-fwd.o

atlantic-fwd-objs := atl_fw.o \
<<<<<<< HEAD
=======
		     atl2_fw.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		     atl_hw.o \
		     atl_main.o \
		     atl_ring.o \
		     atl_ethtool.o \
		     atl_trace.o \
<<<<<<< HEAD
		     atl_fwd.o \
		     atl_compat.o \
		     atl_hwmon.o

CFLAGS_atl_trace.o := -I$(src)
=======
		     atl_compat.o \
		     atl_hwmon.o \
		     atl_ptp.o \
		     atl_hw_ptp.o

atlantic-fwd-$(CONFIG_ATLFWD_FWD) += atl_fwd.o
atlantic-fwd-$(CONFIG_ATLFWD_FWD_NETLINK) += atl_fwdnl.o \
					      atl_fwdnl_params.o
atlantic-fwd-$(CONFIG_MACSEC) += atl_macsec.o macsec/macsec_api.o

atlantic-fwd-$(CONFIG_AQFWD_QCOM) += atl_qcom.o
atlantic-fwd-$(CONFIG_AQFWD_QCOM_IPA) += atl_qcom_ipa.o

ccflags-y += -I$(src)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
