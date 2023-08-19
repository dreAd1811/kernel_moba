# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the USB input drivers
#

<<<<<<< HEAD
usbhid-y	:= hid-core.o
=======
usbhid-y	:= hid-core.o hid-quirks.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
usbhid-$(CONFIG_USB_HIDDEV)	+= hiddev.o
usbhid-$(CONFIG_HID_PID)	+= hid-pidff.o

obj-$(CONFIG_USB_HID)		+= usbhid.o
obj-$(CONFIG_USB_KBD)		+= usbkbd.o
obj-$(CONFIG_USB_MOUSE)		+= usbmouse.o

