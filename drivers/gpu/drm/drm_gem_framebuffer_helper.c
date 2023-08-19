/*
 * drm gem framebuffer helper functions
 *
 * Copyright (C) 2017 Noralf Trønnes
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/dma-buf.h>
#include <linux/dma-fence.h>
#include <linux/reservation.h>
#include <linux/slab.h>

#include <drm/drmP.h>
#include <drm/drm_atomic.h>
#include <drm/drm_fb_helper.h>
#include <drm/drm_fourcc.h>
#include <drm/drm_framebuffer.h>
#include <drm/drm_gem.h>
#include <drm/drm_gem_framebuffer_helper.h>
#include <drm/drm_modeset_helper.h>
<<<<<<< HEAD
#include <drm/drm_simple_kms_helper.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/**
 * DOC: overview
 *
 * This library provides helpers for drivers that don't subclass
<<<<<<< HEAD
 * &drm_framebuffer and use &drm_gem_object for their backing storage.
 *
 * Drivers without additional needs to validate framebuffers can simply use
 * drm_gem_fb_create() and everything is wired up automatically. Other drivers
 * can use all parts independently.
 */

/**
 * drm_gem_fb_get_obj() - Get GEM object backing the framebuffer
 * @fb: Framebuffer
 * @plane: Plane index
 *
 * No additional reference is taken beyond the one that the &drm_frambuffer
 * already holds.
 *
 * Returns:
 * Pointer to &drm_gem_object for the given framebuffer and plane index or NULL
 * if it does not exist.
=======
 * &drm_framebuffer and and use &drm_gem_object for their backing storage.
 *
 * Drivers without additional needs to validate framebuffers can simply use
 * drm_gem_fb_create() and everything is wired up automatically. But all
 * parts can be used individually.
 */

/**
 * drm_gem_fb_get_obj() - Get GEM object for framebuffer
 * @fb: The framebuffer
 * @plane: Which plane
 *
 * Returns the GEM object for given framebuffer.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
struct drm_gem_object *drm_gem_fb_get_obj(struct drm_framebuffer *fb,
					  unsigned int plane)
{
	if (plane >= 4)
		return NULL;

	return fb->obj[plane];
}
EXPORT_SYMBOL_GPL(drm_gem_fb_get_obj);

static struct drm_framebuffer *
drm_gem_fb_alloc(struct drm_device *dev,
		 const struct drm_mode_fb_cmd2 *mode_cmd,
		 struct drm_gem_object **obj, unsigned int num_planes,
		 const struct drm_framebuffer_funcs *funcs)
{
	struct drm_framebuffer *fb;
	int ret, i;

	fb = kzalloc(sizeof(*fb), GFP_KERNEL);
	if (!fb)
		return ERR_PTR(-ENOMEM);

	drm_helper_mode_fill_fb_struct(dev, fb, mode_cmd);

	for (i = 0; i < num_planes; i++)
		fb->obj[i] = obj[i];

	ret = drm_framebuffer_init(dev, fb, funcs);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "Failed to init framebuffer: %d\n",
			      ret);
		kfree(fb);
		return ERR_PTR(ret);
	}

	return fb;
}

/**
 * drm_gem_fb_destroy - Free GEM backed framebuffer
<<<<<<< HEAD
 * @fb: Framebuffer
=======
 * @fb: DRM framebuffer
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * Frees a GEM backed framebuffer with its backing buffer(s) and the structure
 * itself. Drivers can use this as their &drm_framebuffer_funcs->destroy
 * callback.
 */
void drm_gem_fb_destroy(struct drm_framebuffer *fb)
{
	int i;

	for (i = 0; i < 4; i++)
		drm_gem_object_put_unlocked(fb->obj[i]);

	drm_framebuffer_cleanup(fb);
	kfree(fb);
}
EXPORT_SYMBOL(drm_gem_fb_destroy);

/**
 * drm_gem_fb_create_handle - Create handle for GEM backed framebuffer
<<<<<<< HEAD
 * @fb: Framebuffer
 * @file: DRM file to register the handle for
 * @handle: Pointer to return the created handle
 *
 * This function creates a handle for the GEM object backing the framebuffer.
 * Drivers can use this as their &drm_framebuffer_funcs->create_handle
 * callback. The GETFB IOCTL calls into this callback.
=======
 * @fb: DRM framebuffer
 * @file: drm file
 * @handle: handle created
 *
 * Drivers can use this as their &drm_framebuffer_funcs->create_handle
 * callback.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
int drm_gem_fb_create_handle(struct drm_framebuffer *fb, struct drm_file *file,
			     unsigned int *handle)
{
	return drm_gem_handle_create(file, fb->obj[0], handle);
}
EXPORT_SYMBOL(drm_gem_fb_create_handle);

/**
<<<<<<< HEAD
 * drm_gem_fb_create_with_funcs() - Helper function for the
 *                                  &drm_mode_config_funcs.fb_create
 *                                  callback
 * @dev: DRM device
 * @file: DRM file that holds the GEM handle(s) backing the framebuffer
 * @mode_cmd: Metadata from the userspace framebuffer creation request
=======
 * drm_gem_fb_create_with_funcs() - helper function for the
 *                                  &drm_mode_config_funcs.fb_create
 *                                  callback
 * @dev: DRM device
 * @file: drm file for the ioctl call
 * @mode_cmd: metadata from the userspace fb creation request
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @funcs: vtable to be used for the new framebuffer object
 *
 * This can be used to set &drm_framebuffer_funcs for drivers that need the
 * &drm_framebuffer_funcs.dirty callback. Use drm_gem_fb_create() if you don't
 * need to change &drm_framebuffer_funcs.
 * The function does buffer size validation.
<<<<<<< HEAD
 *
 * Returns:
 * Pointer to a &drm_framebuffer on success or an error pointer on failure.
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
struct drm_framebuffer *
drm_gem_fb_create_with_funcs(struct drm_device *dev, struct drm_file *file,
			     const struct drm_mode_fb_cmd2 *mode_cmd,
			     const struct drm_framebuffer_funcs *funcs)
{
	const struct drm_format_info *info;
	struct drm_gem_object *objs[4];
	struct drm_framebuffer *fb;
	int ret, i;

	info = drm_get_format_info(dev, mode_cmd);
	if (!info)
		return ERR_PTR(-EINVAL);

	for (i = 0; i < info->num_planes; i++) {
		unsigned int width = mode_cmd->width / (i ? info->hsub : 1);
		unsigned int height = mode_cmd->height / (i ? info->vsub : 1);
		unsigned int min_size;

		objs[i] = drm_gem_object_lookup(file, mode_cmd->handles[i]);
		if (!objs[i]) {
<<<<<<< HEAD
			DRM_DEBUG_KMS("Failed to lookup GEM object\n");
=======
			DRM_DEV_ERROR(dev->dev, "Failed to lookup GEM\n");
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			ret = -ENOENT;
			goto err_gem_object_put;
		}

		min_size = (height - 1) * mode_cmd->pitches[i]
			 + width * info->cpp[i]
			 + mode_cmd->offsets[i];

		if (objs[i]->size < min_size) {
			drm_gem_object_put_unlocked(objs[i]);
			ret = -EINVAL;
			goto err_gem_object_put;
		}
	}

	fb = drm_gem_fb_alloc(dev, mode_cmd, objs, i, funcs);
	if (IS_ERR(fb)) {
		ret = PTR_ERR(fb);
		goto err_gem_object_put;
	}

	return fb;

err_gem_object_put:
	for (i--; i >= 0; i--)
		drm_gem_object_put_unlocked(objs[i]);

	return ERR_PTR(ret);
}
EXPORT_SYMBOL_GPL(drm_gem_fb_create_with_funcs);

static const struct drm_framebuffer_funcs drm_gem_fb_funcs = {
	.destroy	= drm_gem_fb_destroy,
	.create_handle	= drm_gem_fb_create_handle,
};

/**
<<<<<<< HEAD
 * drm_gem_fb_create() - Helper function for the
 *                       &drm_mode_config_funcs.fb_create callback
 * @dev: DRM device
 * @file: DRM file that holds the GEM handle(s) backing the framebuffer
 * @mode_cmd: Metadata from the userspace framebuffer creation request
 *
 * This function creates a new framebuffer object described by
 * &drm_mode_fb_cmd2. This description includes handles for the buffer(s)
 * backing the framebuffer.
=======
 * drm_gem_fb_create() - &drm_mode_config_funcs.fb_create callback function
 * @dev: DRM device
 * @file: drm file for the ioctl call
 * @mode_cmd: metadata from the userspace fb creation request
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * If your hardware has special alignment or pitch requirements these should be
 * checked before calling this function. The function does buffer size
 * validation. Use drm_gem_fb_create_with_funcs() if you need to set
 * &drm_framebuffer_funcs.dirty.
<<<<<<< HEAD
 *
 * Drivers can use this as their &drm_mode_config_funcs.fb_create callback.
 * The ADDFB2 IOCTL calls into this callback.
 *
 * Returns:
 * Pointer to a &drm_framebuffer on success or an error pointer on failure.
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
struct drm_framebuffer *
drm_gem_fb_create(struct drm_device *dev, struct drm_file *file,
		  const struct drm_mode_fb_cmd2 *mode_cmd)
{
	return drm_gem_fb_create_with_funcs(dev, file, mode_cmd,
					    &drm_gem_fb_funcs);
}
EXPORT_SYMBOL_GPL(drm_gem_fb_create);

/**
<<<<<<< HEAD
 * drm_gem_fb_prepare_fb() - Prepare a GEM backed framebuffer
 * @plane: Plane
 * @state: Plane state the fence will be attached to
 *
 * This function prepares a GEM backed framebuffer for scanout by checking if
 * the plane framebuffer has a DMA-BUF attached. If it does, it extracts the
 * exclusive fence and attaches it to the plane state for the atomic helper to
 * wait on. This function can be used as the &drm_plane_helper_funcs.prepare_fb
 * callback.
=======
 * drm_gem_fb_prepare_fb() - Prepare gem framebuffer
 * @plane: Which plane
 * @state: Plane state attach fence to
 *
 * This can be used as the &drm_plane_helper_funcs.prepare_fb hook.
 *
 * This function checks if the plane FB has an dma-buf attached, extracts
 * the exclusive fence and attaches it to plane state for the atomic helper
 * to wait on.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * There is no need for &drm_plane_helper_funcs.cleanup_fb hook for simple
 * gem based framebuffer drivers which have their buffers always pinned in
 * memory.
 */
int drm_gem_fb_prepare_fb(struct drm_plane *plane,
			  struct drm_plane_state *state)
{
	struct dma_buf *dma_buf;
	struct dma_fence *fence;

<<<<<<< HEAD
	if (!state->fb)
=======
	if ((plane->state->fb == state->fb) || !state->fb)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return 0;

	dma_buf = drm_gem_fb_get_obj(state->fb, 0)->dma_buf;
	if (dma_buf) {
		fence = reservation_object_get_excl_rcu(dma_buf->resv);
		drm_atomic_set_fence_for_plane(state, fence);
	}

	return 0;
}
EXPORT_SYMBOL_GPL(drm_gem_fb_prepare_fb);

/**
<<<<<<< HEAD
 * drm_gem_fb_simple_display_pipe_prepare_fb - prepare_fb helper for
 *     &drm_simple_display_pipe
 * @pipe: Simple display pipe
 * @plane_state: Plane state
 *
 * This function uses drm_gem_fb_prepare_fb() to check if the plane FB has a
 * &dma_buf attached, extracts the exclusive fence and attaches it to plane
 * state for the atomic helper to wait on. Drivers can use this as their
 * &drm_simple_display_pipe_funcs.prepare_fb callback.
 */
int drm_gem_fb_simple_display_pipe_prepare_fb(struct drm_simple_display_pipe *pipe,
					      struct drm_plane_state *plane_state)
{
	return drm_gem_fb_prepare_fb(&pipe->plane, plane_state);
}
EXPORT_SYMBOL(drm_gem_fb_simple_display_pipe_prepare_fb);

/**
 * drm_gem_fbdev_fb_create - Create a GEM backed &drm_framebuffer for fbdev
 *                           emulation
 * @dev: DRM device
 * @sizes: fbdev size description
 * @pitch_align: Optional pitch alignment
 * @obj: GEM object backing the framebuffer
 * @funcs: Optional vtable to be used for the new framebuffer object when the
 *         dirty callback is needed.
 *
 * This function creates a framebuffer from a &drm_fb_helper_surface_size
 * description for use in the &drm_fb_helper_funcs.fb_probe callback.
 *
 * Returns:
 * Pointer to a &drm_framebuffer on success or an error pointer on failure.
=======
 * drm_gem_fbdev_fb_create - Create a drm_framebuffer for fbdev emulation
 * @dev: DRM device
 * @sizes: fbdev size description
 * @pitch_align: optional pitch alignment
 * @obj: GEM object backing the framebuffer
 * @funcs: vtable to be used for the new framebuffer object
 *
 * This function creates a framebuffer for use with fbdev emulation.
 *
 * Returns:
 * Pointer to a drm_framebuffer on success or an error pointer on failure.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
struct drm_framebuffer *
drm_gem_fbdev_fb_create(struct drm_device *dev,
			struct drm_fb_helper_surface_size *sizes,
			unsigned int pitch_align, struct drm_gem_object *obj,
			const struct drm_framebuffer_funcs *funcs)
{
	struct drm_mode_fb_cmd2 mode_cmd = { 0 };

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;
	mode_cmd.pitches[0] = sizes->surface_width *
			      DIV_ROUND_UP(sizes->surface_bpp, 8);
	if (pitch_align)
		mode_cmd.pitches[0] = roundup(mode_cmd.pitches[0],
					      pitch_align);
	mode_cmd.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
							sizes->surface_depth);
	if (obj->size < mode_cmd.pitches[0] * mode_cmd.height)
		return ERR_PTR(-EINVAL);

<<<<<<< HEAD
	if (!funcs)
		funcs = &drm_gem_fb_funcs;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return drm_gem_fb_alloc(dev, &mode_cmd, &obj, 1, funcs);
}
EXPORT_SYMBOL(drm_gem_fbdev_fb_create);
