<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0+ */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * vsp1_drm.h  --  R-Car VSP1 DRM/KMS Interface
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinchart (laurent.pinchart@ideasonboard.com)
<<<<<<< HEAD
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
#ifndef __VSP1_DRM_H__
#define __VSP1_DRM_H__

<<<<<<< HEAD
#include <linux/mutex.h>
#include <linux/videodev2.h>
#include <linux/wait.h>

#include <media/vsp1.h>
=======
#include <linux/videodev2.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include "vsp1_pipe.h"

/**
 * vsp1_drm_pipeline - State for the API exposed to the DRM driver
 * @pipe: the VSP1 pipeline used for display
<<<<<<< HEAD
 * @width: output display width
 * @height: output display height
 * @force_brx_release: when set, release the BRx during the next reconfiguration
 * @wait_queue: wait queue to wait for BRx release completion
 * @uif: UIF entity if available for the pipeline
 * @crc: CRC computation configuration
=======
 * @enabled: pipeline state at the beginning of an update
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @du_complete: frame completion callback for the DU driver (optional)
 * @du_private: data to be passed to the du_complete callback
 */
struct vsp1_drm_pipeline {
	struct vsp1_pipeline pipe;
<<<<<<< HEAD

	unsigned int width;
	unsigned int height;

	bool force_brx_release;
	wait_queue_head_t wait_queue;

	struct vsp1_entity *uif;
	struct vsp1_du_crc_config crc;

	/* Frame synchronisation */
	void (*du_complete)(void *data, bool completed, u32 crc);
=======
	bool enabled;

	/* Frame synchronisation */
	void (*du_complete)(void *, bool);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	void *du_private;
};

/**
 * vsp1_drm - State for the API exposed to the DRM driver
 * @pipe: the VSP1 DRM pipeline used for display
<<<<<<< HEAD
 * @lock: protects the BRU and BRS allocation
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @inputs: source crop rectangle, destination compose rectangle and z-order
 *	position for every input (indexed by RPF index)
 */
struct vsp1_drm {
	struct vsp1_drm_pipeline pipe[VSP1_MAX_LIF];
<<<<<<< HEAD
	struct mutex lock;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	struct {
		struct v4l2_rect crop;
		struct v4l2_rect compose;
		unsigned int zpos;
	} inputs[VSP1_MAX_RPF];
};

static inline struct vsp1_drm_pipeline *
to_vsp1_drm_pipeline(struct vsp1_pipeline *pipe)
{
	return container_of(pipe, struct vsp1_drm_pipeline, pipe);
}

int vsp1_drm_init(struct vsp1_device *vsp1);
void vsp1_drm_cleanup(struct vsp1_device *vsp1);

#endif /* __VSP1_DRM_H__ */
