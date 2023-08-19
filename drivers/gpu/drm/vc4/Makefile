# SPDX-License-Identifier: GPL-2.0
# Please keep these build lists sorted!

# core driver code
vc4-y := \
	vc4_bo.o \
	vc4_crtc.o \
	vc4_drv.o \
	vc4_dpi.o \
	vc4_dsi.o \
	vc4_fence.o \
	vc4_kms.o \
	vc4_gem.o \
	vc4_hdmi.o \
	vc4_vec.o \
	vc4_hvs.o \
	vc4_irq.o \
<<<<<<< HEAD
	vc4_perfmon.o \
	vc4_plane.o \
	vc4_render_cl.o \
	vc4_trace_points.o \
	vc4_txp.o \
=======
	vc4_plane.o \
	vc4_render_cl.o \
	vc4_trace_points.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	vc4_v3d.o \
	vc4_validate.o \
	vc4_validate_shaders.o

vc4-$(CONFIG_DEBUG_FS) += vc4_debugfs.o

obj-$(CONFIG_DRM_VC4)  += vc4.o
<<<<<<< HEAD
=======

CFLAGS_vc4_trace_points.o := -I$(src)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
