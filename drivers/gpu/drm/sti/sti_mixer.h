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

#ifndef _STI_MIXER_H_
#define _STI_MIXER_H_

#include <drm/drmP.h>

#include "sti_plane.h"

#define to_sti_mixer(x) container_of(x, struct sti_mixer, drm_crtc)

enum sti_mixer_status {
	STI_MIXER_READY,
	STI_MIXER_DISABLING,
	STI_MIXER_DISABLED,
};

/**
 * STI Mixer subdevice structure
 *
 * @dev: driver device
 * @regs: mixer registers
 * @id: id of the mixer
 * @drm_crtc: crtc object link to the mixer
 * @status: to know the status of the mixer
 */
struct sti_mixer {
	struct device *dev;
	void __iomem *regs;
	int id;
	struct drm_crtc drm_crtc;
	enum sti_mixer_status status;
};

const char *sti_mixer_to_str(struct sti_mixer *mixer);

struct sti_mixer *sti_mixer_create(struct device *dev,
				   struct drm_device *drm_dev,
				   int id,
				   void __iomem *baseaddr);

int sti_mixer_set_plane_status(struct sti_mixer *mixer,
			       struct sti_plane *plane, bool status);
int sti_mixer_set_plane_depth(struct sti_mixer *mixer, struct sti_plane *plane);
int sti_mixer_active_video_area(struct sti_mixer *mixer,
				struct drm_display_mode *mode);

void sti_mixer_set_background_status(struct sti_mixer *mixer, bool enable);

int sti_mixer_debugfs_init(struct sti_mixer *mixer, struct drm_minor *minor);

/* depth in Cross-bar control = z order */
#define GAM_MIXER_NB_DEPTH_LEVEL 6

#define STI_MIXER_MAIN 0
#define STI_MIXER_AUX  1

#endif
