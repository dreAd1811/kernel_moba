# SPDX-License-Identifier: GPL-2.0
uvcvideo-objs  := uvc_driver.o uvc_queue.o uvc_v4l2.o uvc_video.o uvc_ctrl.o \
<<<<<<< HEAD
		  uvc_status.o uvc_isight.o uvc_debugfs.o uvc_metadata.o
=======
		  uvc_status.o uvc_isight.o uvc_debugfs.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
ifeq ($(CONFIG_MEDIA_CONTROLLER),y)
uvcvideo-objs  += uvc_entity.o
endif
obj-$(CONFIG_USB_VIDEO_CLASS) += uvcvideo.o
