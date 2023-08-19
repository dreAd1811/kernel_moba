/*
 * ARC PGU DRM driver.
 *
 * Copyright (C) 2016 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <drm/drm_crtc_helper.h>
<<<<<<< HEAD
=======
#include <drm/drm_encoder_slave.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <drm/drm_atomic_helper.h>

#include "arcpgu.h"

#define XRES_DEF	640
#define YRES_DEF	480

#define XRES_MAX	8192
#define YRES_MAX	8192


struct arcpgu_drm_connector {
	struct drm_connector connector;
<<<<<<< HEAD
=======
	struct drm_encoder_slave *encoder_slave;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static int arcpgu_drm_connector_get_modes(struct drm_connector *connector)
{
	int count;

	count = drm_add_modes_noedid(connector, XRES_MAX, YRES_MAX);
	drm_set_preferred_mode(connector, XRES_DEF, YRES_DEF);
	return count;
}

static void arcpgu_drm_connector_destroy(struct drm_connector *connector)
{
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
}

static const struct drm_connector_helper_funcs
arcpgu_drm_connector_helper_funcs = {
	.get_modes = arcpgu_drm_connector_get_modes,
};

static const struct drm_connector_funcs arcpgu_drm_connector_funcs = {
	.dpms = drm_helper_connector_dpms,
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = arcpgu_drm_connector_destroy,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
};

static struct drm_encoder_funcs arcpgu_drm_encoder_funcs = {
	.destroy = drm_encoder_cleanup,
};

int arcpgu_drm_sim_init(struct drm_device *drm, struct device_node *np)
{
	struct arcpgu_drm_connector *arcpgu_connector;
<<<<<<< HEAD
	struct drm_encoder *encoder;
=======
	struct drm_encoder_slave *encoder;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct drm_connector *connector;
	int ret;

	encoder = devm_kzalloc(drm->dev, sizeof(*encoder), GFP_KERNEL);
	if (encoder == NULL)
		return -ENOMEM;

<<<<<<< HEAD
	encoder->possible_crtcs = 1;
	encoder->possible_clones = 0;

	ret = drm_encoder_init(drm, encoder, &arcpgu_drm_encoder_funcs,
=======
	encoder->base.possible_crtcs = 1;
	encoder->base.possible_clones = 0;

	ret = drm_encoder_init(drm, &encoder->base, &arcpgu_drm_encoder_funcs,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			       DRM_MODE_ENCODER_VIRTUAL, NULL);
	if (ret)
		return ret;

	arcpgu_connector = devm_kzalloc(drm->dev, sizeof(*arcpgu_connector),
					GFP_KERNEL);
	if (!arcpgu_connector) {
		ret = -ENOMEM;
		goto error_encoder_cleanup;
	}

	connector = &arcpgu_connector->connector;
	drm_connector_helper_add(connector, &arcpgu_drm_connector_helper_funcs);

	ret = drm_connector_init(drm, connector, &arcpgu_drm_connector_funcs,
			DRM_MODE_CONNECTOR_VIRTUAL);
	if (ret < 0) {
		dev_err(drm->dev, "failed to initialize drm connector\n");
		goto error_encoder_cleanup;
	}

<<<<<<< HEAD
	ret = drm_connector_attach_encoder(connector, encoder);
=======
	ret = drm_mode_connector_attach_encoder(connector, &encoder->base);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret < 0) {
		dev_err(drm->dev, "could not attach connector to encoder\n");
		drm_connector_unregister(connector);
		goto error_connector_cleanup;
	}

<<<<<<< HEAD
=======
	arcpgu_connector->encoder_slave = encoder;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;

error_connector_cleanup:
	drm_connector_cleanup(connector);

error_encoder_cleanup:
<<<<<<< HEAD
	drm_encoder_cleanup(encoder);
=======
	drm_encoder_cleanup(&encoder->base);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}
