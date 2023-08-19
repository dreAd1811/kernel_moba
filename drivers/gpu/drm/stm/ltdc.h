<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Authors: Philippe Cornu <philippe.cornu@st.com>
 *          Yannick Fertre <yannick.fertre@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          Mickael Reulier <mickael.reulier@st.com>
<<<<<<< HEAD
=======
 *
 * License terms:  GNU General Public License (GPL), version 2
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef _LTDC_H_
#define _LTDC_H_

struct ltdc_caps {
	u32 hw_version;		/* hardware version */
	u32 nb_layers;		/* number of supported layers */
	u32 reg_ofs;		/* register offset for applicable regs */
	u32 bus_width;		/* bus width (32 or 64 bits) */
	const u32 *pix_fmt_hw;	/* supported pixel formats */
<<<<<<< HEAD
	bool non_alpha_only_l1; /* non-native no-alpha formats on layer 1 */
	int pad_max_freq_hz;	/* max frequency supported by pad */
};

#define LTDC_MAX_LAYER	4

struct fps_info {
	unsigned int counter;
	ktime_t last_timestamp;
};

struct ltdc_device {
	void __iomem *regs;
	struct clk *pixel_clk;	/* lcd pixel clock */
=======
};

struct ltdc_device {
	struct drm_fbdev_cma *fbdev;
	void __iomem *regs;
	struct clk *pixel_clk;	/* lcd pixel clock */
	struct drm_bridge *bridge;
	bool is_panel_bridge;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct mutex err_lock;	/* protecting error_status */
	struct ltdc_caps caps;
	u32 error_status;
	u32 irq_status;
<<<<<<< HEAD
	struct fps_info plane_fpsi[LTDC_MAX_LAYER];
};

=======
};

int ltdc_crtc_enable_vblank(struct drm_device *dev, unsigned int pipe);
void ltdc_crtc_disable_vblank(struct drm_device *dev, unsigned int pipe);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int ltdc_load(struct drm_device *ddev);
void ltdc_unload(struct drm_device *ddev);

#endif
