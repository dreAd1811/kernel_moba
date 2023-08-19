# SPDX-License-Identifier: GPL-2.0
smsmdtv-objs := smscoreapi.o sms-cards.o smsendian.o
smsdvb-objs := smsdvb-main.o

obj-$(CONFIG_SMS_SIANO_MDTV) += smsmdtv.o smsdvb.o

ifeq ($(CONFIG_SMS_SIANO_RC),y)
  smsmdtv-objs += smsir.o
endif

ifeq ($(CONFIG_SMS_SIANO_DEBUGFS),y)
  smsdvb-objs += smsdvb-debugfs.o
endif
<<<<<<< HEAD
=======

ccflags-y += -Idrivers/media/dvb-core
ccflags-y += $(extra-cflags-y) $(extra-cflags-m)

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
