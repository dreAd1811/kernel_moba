# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the nGene device driver
#

ngene-objs := ngene-core.o ngene-i2c.o ngene-cards.o ngene-dvb.o

obj-$(CONFIG_DVB_NGENE) += ngene.o

<<<<<<< HEAD
ccflags-y += -Idrivers/media/dvb-frontends/
ccflags-y += -Idrivers/media/tuners/
=======
ccflags-y += -Idrivers/media/dvb-core/
ccflags-y += -Idrivers/media/dvb-frontends/
ccflags-y += -Idrivers/media/tuners/

# For the staging CI driver cxd2099
ccflags-y += -Idrivers/staging/media/cxd2099/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
