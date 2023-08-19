# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the kernel DVB device drivers.
#

dvb-net-$(CONFIG_DVB_NET) := dvb_net.o
<<<<<<< HEAD
dvb-vb2-$(CONFIG_DVB_MMAP) := dvb_vb2.o

dvb-core-objs := dvbdev.o dmxdev.o dvb_demux.o			\
		 dvb_ca_en50221.o dvb_frontend.o		\
		 $(dvb-net-y) dvb_ringbuffer.o $(dvb-vb2-y) dvb_math.o
=======

dvb-core-objs := dvbdev.o dmxdev.o dvb_demux.o		 	\
		 dvb_ca_en50221.o dvb_frontend.o 		\
		 $(dvb-net-y) dvb_ringbuffer.o dvb_math.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

obj-$(CONFIG_DVB_CORE) += dvb-core.o
