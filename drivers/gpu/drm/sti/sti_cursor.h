<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2013
 * Authors: Vincent Abriou <vincent.abriou@st.com> for STMicroelectronics.
=======
/*
 * Copyright (C) STMicroelectronics SA 2013
 * Authors: Vincent Abriou <vincent.abriou@st.com> for STMicroelectronics.
 * License terms:  GNU General Public License (GPL), version 2
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef _STI_CURSOR_H_
#define _STI_CURSOR_H_

struct drm_plane *sti_cursor_create(struct drm_device *drm_dev,
				    struct device *dev, int desc,
				    void __iomem *baseaddr,
				    unsigned int possible_crtcs);

#endif
