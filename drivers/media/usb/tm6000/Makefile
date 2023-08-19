# SPDX-License-Identifier: GPL-2.0
tm6000-y := tm6000-cards.o \
		   tm6000-core.o  \
		   tm6000-i2c.o   \
		   tm6000-video.o \
		   tm6000-stds.o \
		   tm6000-input.o

obj-$(CONFIG_VIDEO_TM6000) += tm6000.o
obj-$(CONFIG_VIDEO_TM6000_ALSA) += tm6000-alsa.o
obj-$(CONFIG_VIDEO_TM6000_DVB) += tm6000-dvb.o

<<<<<<< HEAD
ccflags-y += -Idrivers/media/tuners
=======
ccflags-y += -Idrivers/media/i2c
ccflags-y += -Idrivers/media/tuners
ccflags-y += -Idrivers/media/dvb-core
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
ccflags-y += -Idrivers/media/dvb-frontends
