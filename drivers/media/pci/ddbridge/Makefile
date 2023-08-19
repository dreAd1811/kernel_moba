# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the ddbridge device driver
#

<<<<<<< HEAD
ddbridge-objs := ddbridge-main.o ddbridge-core.o ddbridge-ci.o \
		ddbridge-hw.o ddbridge-i2c.o ddbridge-max.o ddbridge-mci.o \
		ddbridge-sx8.o

obj-$(CONFIG_DVB_DDBRIDGE) += ddbridge.o

ccflags-y += -Idrivers/media/dvb-frontends/
ccflags-y += -Idrivers/media/tuners/
=======
ddbridge-objs := ddbridge-main.o ddbridge-core.o ddbridge-hw.o \
		ddbridge-i2c.o ddbridge-maxs8.o

obj-$(CONFIG_DVB_DDBRIDGE) += ddbridge.o

ccflags-y += -Idrivers/media/dvb-core/
ccflags-y += -Idrivers/media/dvb-frontends/
ccflags-y += -Idrivers/media/tuners/

# For the staging CI driver cxd2099
ccflags-y += -Idrivers/staging/media/cxd2099/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
