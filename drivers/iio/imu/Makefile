# SPDX-License-Identifier: GPL-2.0
#
# Makefile for Inertial Measurement Units
#

# When adding new entries keep the list in alphabetical order
adis16400-y             := adis16400_core.o
adis16400-$(CONFIG_IIO_BUFFER) += adis16400_buffer.o
obj-$(CONFIG_ADIS16400) += adis16400.o
obj-$(CONFIG_ADIS16480) += adis16480.o

adis_lib-y += adis.o
adis_lib-$(CONFIG_IIO_ADIS_LIB_BUFFER) += adis_trigger.o
adis_lib-$(CONFIG_IIO_ADIS_LIB_BUFFER) += adis_buffer.o
obj-$(CONFIG_IIO_ADIS_LIB) += adis_lib.o

obj-y += bmi160/
obj-y += inv_mpu6050/
<<<<<<< HEAD
=======
obj-y += inv_mpu/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

obj-$(CONFIG_KMX61) += kmx61.o

obj-y += st_lsm6dsx/
<<<<<<< HEAD
=======
obj-y += st_asm330lhh/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
