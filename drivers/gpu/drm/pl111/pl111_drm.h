/*
 *
 * (C) COPYRIGHT 2012-2013 ARM Limited. All rights reserved.
 *
 *
 * Parts of this file were based on sources as follows:
 *
 * Copyright (c) 2006-2008 Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (C) 2011 Texas Instruments
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms of
 * such GNU licence.
 *
 */

#ifndef _PL111_DRM_H_
#define _PL111_DRM_H_

#include <drm/drm_gem.h>
#include <drm/drm_simple_kms_helper.h>
<<<<<<< HEAD
#include <drm/drm_connector.h>
#include <drm/drm_encoder.h>
#include <drm/drm_panel.h>
#include <drm/drm_bridge.h>
#include <linux/clk-provider.h>
#include <linux/interrupt.h>
=======
#include <linux/clk-provider.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define CLCD_IRQ_NEXTBASE_UPDATE BIT(2)

struct drm_minor;

<<<<<<< HEAD
/**
 * struct pl111_variant_data - encodes IP differences
 * @name: the name of this variant
 * @is_pl110: this is the early PL110 variant
 * @is_lcdc: this is the ST Microelectronics Nomadik LCDC variant
 * @external_bgr: this is the Versatile Pl110 variant with external
 *	BGR/RGB routing
 * @broken_clockdivider: the clock divider is broken and we need to
 *	use the supplied clock directly
 * @broken_vblank: the vblank IRQ is broken on this variant
 * @st_bitmux_control: this variant is using the ST Micro bitmux
 *	extensions to the control register
 * @formats: array of supported pixel formats on this variant
 * @nformats: the length of the array of supported pixel formats
 * @fb_bpp: desired bits per pixel on the default framebuffer
 */
struct pl111_variant_data {
	const char *name;
	bool is_pl110;
	bool is_lcdc;
	bool external_bgr;
	bool broken_clockdivider;
	bool broken_vblank;
	bool st_bitmux_control;
	const u32 *formats;
	unsigned int nformats;
	unsigned int fb_bpp;
=======
struct pl111_drm_connector {
	struct drm_connector connector;
	struct drm_panel *panel;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct pl111_drm_dev_private {
	struct drm_device *drm;

<<<<<<< HEAD
	struct drm_connector *connector;
	struct drm_panel *panel;
	struct drm_bridge *bridge;
	struct drm_simple_display_pipe pipe;

	void *regs;
	u32 memory_bw;
	u32 ienb;
	u32 ctrl;
=======
	struct pl111_drm_connector connector;
	struct drm_simple_display_pipe pipe;
	struct drm_fbdev_cma *fbdev;

	void *regs;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* The pixel clock (a reference to our clock divider off of CLCDCLK). */
	struct clk *clk;
	/* pl111's internal clock divider. */
	struct clk_hw clk_div;
	/* Lock to sync access to CLCD_TIM2 between the common clock
	 * subsystem and pl111_display_enable().
	 */
	spinlock_t tim2_lock;
<<<<<<< HEAD
	const struct pl111_variant_data *variant;
	void (*variant_display_enable) (struct drm_device *drm, u32 format);
	void (*variant_display_disable) (struct drm_device *drm);
	bool use_device_memory;
};

int pl111_display_init(struct drm_device *dev);
irqreturn_t pl111_irq(int irq, void *data);
=======
};

#define to_pl111_connector(x) \
	container_of(x, struct pl111_drm_connector, connector)

int pl111_display_init(struct drm_device *dev);
int pl111_enable_vblank(struct drm_device *drm, unsigned int crtc);
void pl111_disable_vblank(struct drm_device *drm, unsigned int crtc);
irqreturn_t pl111_irq(int irq, void *data);
int pl111_connector_init(struct drm_device *dev);
int pl111_encoder_init(struct drm_device *dev);
int pl111_dumb_create(struct drm_file *file_priv,
		      struct drm_device *dev,
		      struct drm_mode_create_dumb *args);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int pl111_debugfs_init(struct drm_minor *minor);

#endif /* _PL111_DRM_H_ */
