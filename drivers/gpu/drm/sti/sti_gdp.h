<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          for STMicroelectronics.
<<<<<<< HEAD
=======
 * License terms:  GNU General Public License (GPL), version 2
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef _STI_GDP_H_
#define _STI_GDP_H_

#include <linux/types.h>

struct drm_plane *sti_gdp_create(struct drm_device *drm_dev,
				 struct device *dev, int desc,
				 void __iomem *baseaddr,
				 unsigned int possible_crtcs,
				 enum drm_plane_type type);
#endif
