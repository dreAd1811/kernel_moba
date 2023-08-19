<<<<<<< HEAD
# SPDX-License-Identifier: GPL-2.0

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
ifeq ($(CONFIG_PM_H1940),y)
	zreladdr-y	+= 0x30108000
	params_phys-y	:= 0x30100100
else
	zreladdr-y	+= 0x30008000
	params_phys-y	:= 0x30000100
endif
