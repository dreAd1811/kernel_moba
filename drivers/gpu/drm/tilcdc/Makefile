# SPDX-License-Identifier: GPL-2.0
ifeq (, $(findstring -W,$(EXTRA_CFLAGS)))
	ccflags-y += -Werror
endif

<<<<<<< HEAD
=======
obj-$(CONFIG_DRM_TILCDC_SLAVE_COMPAT) += tilcdc_slave_compat.o \
					 tilcdc_slave_compat.dtb.o

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
tilcdc-y := \
	tilcdc_plane.o \
	tilcdc_crtc.o \
	tilcdc_tfp410.o \
	tilcdc_panel.o \
	tilcdc_external.o \
	tilcdc_drv.o

obj-$(CONFIG_DRM_TILCDC)	+= tilcdc.o
