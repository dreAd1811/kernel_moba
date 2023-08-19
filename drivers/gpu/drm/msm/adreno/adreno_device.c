/*
 * Copyright (C) 2013-2014 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 *
 * Copyright (c) 2014,2017 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

<<<<<<< HEAD
=======
#include <linux/pm_opp.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "adreno_gpu.h"

#define ANY_ID 0xff

bool hang_debug = false;
MODULE_PARM_DESC(hang_debug, "Dump registers when hang is detected (can be slow!)");
module_param_named(hang_debug, hang_debug, bool, 0600);

static const struct adreno_info gpulist[] = {
	{
		.rev   = ADRENO_REV(3, 0, 5, ANY_ID),
		.revn  = 305,
		.name  = "A305",
<<<<<<< HEAD
		.fw = {
			[ADRENO_FW_PM4] = "a300_pm4.fw",
			[ADRENO_FW_PFP] = "a300_pfp.fw",
		},
		.gmem  = SZ_256K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
=======
		.pm4fw = "a300_pm4.fw",
		.pfpfw = "a300_pfp.fw",
		.gmem  = SZ_256K,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		.init  = a3xx_gpu_init,
	}, {
		.rev   = ADRENO_REV(3, 0, 6, 0),
		.revn  = 307,        /* because a305c is revn==306 */
		.name  = "A306",
<<<<<<< HEAD
		.fw = {
			[ADRENO_FW_PM4] = "a300_pm4.fw",
			[ADRENO_FW_PFP] = "a300_pfp.fw",
		},
		.gmem  = SZ_128K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
=======
		.pm4fw = "a300_pm4.fw",
		.pfpfw = "a300_pfp.fw",
		.gmem  = SZ_128K,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		.init  = a3xx_gpu_init,
	}, {
		.rev   = ADRENO_REV(3, 2, ANY_ID, ANY_ID),
		.revn  = 320,
		.name  = "A320",
<<<<<<< HEAD
		.fw = {
			[ADRENO_FW_PM4] = "a300_pm4.fw",
			[ADRENO_FW_PFP] = "a300_pfp.fw",
		},
		.gmem  = SZ_512K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
=======
		.pm4fw = "a300_pm4.fw",
		.pfpfw = "a300_pfp.fw",
		.gmem  = SZ_512K,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		.init  = a3xx_gpu_init,
	}, {
		.rev   = ADRENO_REV(3, 3, 0, ANY_ID),
		.revn  = 330,
		.name  = "A330",
<<<<<<< HEAD
		.fw = {
			[ADRENO_FW_PM4] = "a330_pm4.fw",
			[ADRENO_FW_PFP] = "a330_pfp.fw",
		},
		.gmem  = SZ_1M,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
=======
		.pm4fw = "a330_pm4.fw",
		.pfpfw = "a330_pfp.fw",
		.gmem  = SZ_1M,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		.init  = a3xx_gpu_init,
	}, {
		.rev   = ADRENO_REV(4, 2, 0, ANY_ID),
		.revn  = 420,
		.name  = "A420",
<<<<<<< HEAD
		.fw = {
			[ADRENO_FW_PM4] = "a420_pm4.fw",
			[ADRENO_FW_PFP] = "a420_pfp.fw",
		},
		.gmem  = (SZ_1M + SZ_512K),
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
=======
		.pm4fw = "a420_pm4.fw",
		.pfpfw = "a420_pfp.fw",
		.gmem  = (SZ_1M + SZ_512K),
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		.init  = a4xx_gpu_init,
	}, {
		.rev   = ADRENO_REV(4, 3, 0, ANY_ID),
		.revn  = 430,
		.name  = "A430",
<<<<<<< HEAD
		.fw = {
			[ADRENO_FW_PM4] = "a420_pm4.fw",
			[ADRENO_FW_PFP] = "a420_pfp.fw",
		},
		.gmem  = (SZ_1M + SZ_512K),
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
=======
		.pm4fw = "a420_pm4.fw",
		.pfpfw = "a420_pfp.fw",
		.gmem  = (SZ_1M + SZ_512K),
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		.init  = a4xx_gpu_init,
	}, {
		.rev = ADRENO_REV(5, 3, 0, 2),
		.revn = 530,
		.name = "A530",
<<<<<<< HEAD
		.fw = {
			[ADRENO_FW_PM4] = "a530_pm4.fw",
			[ADRENO_FW_PFP] = "a530_pfp.fw",
			[ADRENO_FW_GPMU] = "a530v3_gpmu.fw2",
		},
		.gmem = SZ_1M,
		/*
		 * Increase inactive period to 250 to avoid bouncing
		 * the GDSC which appears to make it grumpy
		 */
		.inactive_period = 250,
		.quirks = ADRENO_QUIRK_TWO_PASS_USE_WFI |
			ADRENO_QUIRK_FAULT_DETECT_MASK,
		.init = a5xx_gpu_init,
		.zapfw = "a530_zap.mdt",
	}, {
		.rev = ADRENO_REV(6, 3, 0, ANY_ID),
		.revn = 630,
		.name = "A630",
		.fw = {
			[ADRENO_FW_SQE] = "a630_sqe.fw",
			[ADRENO_FW_GMU] = "a630_gmu.bin",
		},
		.gmem = SZ_1M,
		.init = a6xx_gpu_init,
	},
};

MODULE_FIRMWARE("qcom/a300_pm4.fw");
MODULE_FIRMWARE("qcom/a300_pfp.fw");
MODULE_FIRMWARE("qcom/a330_pm4.fw");
MODULE_FIRMWARE("qcom/a330_pfp.fw");
MODULE_FIRMWARE("qcom/a420_pm4.fw");
MODULE_FIRMWARE("qcom/a420_pfp.fw");
MODULE_FIRMWARE("qcom/a530_pm4.fw");
MODULE_FIRMWARE("qcom/a530_pfp.fw");
MODULE_FIRMWARE("qcom/a530v3_gpmu.fw2");
MODULE_FIRMWARE("qcom/a530_zap.mdt");
MODULE_FIRMWARE("qcom/a530_zap.b00");
MODULE_FIRMWARE("qcom/a530_zap.b01");
MODULE_FIRMWARE("qcom/a530_zap.b02");
MODULE_FIRMWARE("qcom/a630_sqe.fw");
MODULE_FIRMWARE("qcom/a630_gmu.bin");
=======
		.pm4fw = "a530_pm4.fw",
		.pfpfw = "a530_pfp.fw",
		.gmem = SZ_1M,
		.quirks = ADRENO_QUIRK_TWO_PASS_USE_WFI |
			ADRENO_QUIRK_FAULT_DETECT_MASK,
		.init = a5xx_gpu_init,
		.gpmufw = "a530v3_gpmu.fw2",
		.zapfw = "a530_zap.mdt",
	},
};

MODULE_FIRMWARE("a300_pm4.fw");
MODULE_FIRMWARE("a300_pfp.fw");
MODULE_FIRMWARE("a330_pm4.fw");
MODULE_FIRMWARE("a330_pfp.fw");
MODULE_FIRMWARE("a420_pm4.fw");
MODULE_FIRMWARE("a420_pfp.fw");
MODULE_FIRMWARE("a530_fm4.fw");
MODULE_FIRMWARE("a530_pfp.fw");
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static inline bool _rev_match(uint8_t entry, uint8_t id)
{
	return (entry == ANY_ID) || (entry == id);
}

const struct adreno_info *adreno_info(struct adreno_rev rev)
{
	int i;

	/* identify gpu: */
	for (i = 0; i < ARRAY_SIZE(gpulist); i++) {
		const struct adreno_info *info = &gpulist[i];
		if (_rev_match(info->rev.core, rev.core) &&
				_rev_match(info->rev.major, rev.major) &&
				_rev_match(info->rev.minor, rev.minor) &&
				_rev_match(info->rev.patchid, rev.patchid))
			return info;
	}

	return NULL;
}

struct msm_gpu *adreno_load_gpu(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct platform_device *pdev = priv->gpu_pdev;
<<<<<<< HEAD
	struct msm_gpu *gpu = NULL;
	struct adreno_gpu *adreno_gpu;
	int ret;

	if (pdev)
		gpu = platform_get_drvdata(pdev);

	if (!gpu) {
		dev_err_once(dev->dev, "no GPU device was found\n");
		return NULL;
	}

	adreno_gpu = to_adreno_gpu(gpu);

	/*
	 * The number one reason for HW init to fail is if the firmware isn't
	 * loaded yet. Try that first and don't bother continuing on
	 * otherwise
	 */

	ret = adreno_load_fw(adreno_gpu);
	if (ret)
		return NULL;

	/* Make sure pm runtime is active and reset any previous errors */
	pm_runtime_set_active(&pdev->dev);

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		dev_err(dev->dev, "Couldn't power up the GPU: %d\n", ret);
		return NULL;
	}

	mutex_lock(&dev->struct_mutex);
	ret = msm_gpu_hw_init(gpu);
	mutex_unlock(&dev->struct_mutex);
	pm_runtime_put_autosuspend(&pdev->dev);
	if (ret) {
		dev_err(dev->dev, "gpu hw init failed: %d\n", ret);
		return NULL;
	}

#ifdef CONFIG_DEBUG_FS
	if (gpu->funcs->debugfs_init) {
		gpu->funcs->debugfs_init(gpu, dev->primary);
		gpu->funcs->debugfs_init(gpu, dev->render);
	}
#endif
=======
	struct adreno_platform_config *config;
	struct adreno_rev rev;
	const struct adreno_info *info;
	struct msm_gpu *gpu = NULL;

	if (!pdev) {
		dev_err(dev->dev, "no adreno device\n");
		return NULL;
	}

	config = pdev->dev.platform_data;
	rev = config->rev;
	info = adreno_info(config->rev);

	if (!info) {
		dev_warn(dev->dev, "Unknown GPU revision: %u.%u.%u.%u\n",
				rev.core, rev.major, rev.minor, rev.patchid);
		return NULL;
	}

	DBG("Found GPU: %u.%u.%u.%u",  rev.core, rev.major,
			rev.minor, rev.patchid);

	gpu = info->init(dev);
	if (IS_ERR(gpu)) {
		dev_warn(dev->dev, "failed to load adreno gpu\n");
		gpu = NULL;
		/* not fatal */
	}

	if (gpu) {
		int ret;

		pm_runtime_get_sync(&pdev->dev);
		mutex_lock(&dev->struct_mutex);
		ret = msm_gpu_hw_init(gpu);
		mutex_unlock(&dev->struct_mutex);
		pm_runtime_put_sync(&pdev->dev);
		if (ret) {
			dev_err(dev->dev, "gpu hw init failed: %d\n", ret);
			gpu->funcs->destroy(gpu);
			gpu = NULL;
		}
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return gpu;
}

static void set_gpu_pdev(struct drm_device *dev,
		struct platform_device *pdev)
{
	struct msm_drm_private *priv = dev->dev_private;
	priv->gpu_pdev = pdev;
}

<<<<<<< HEAD
static int find_chipid(struct device *dev, struct adreno_rev *rev)
=======
static int find_chipid(struct device *dev, u32 *chipid)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct device_node *node = dev->of_node;
	const char *compat;
	int ret;
<<<<<<< HEAD
	u32 chipid;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* first search the compat strings for qcom,adreno-XYZ.W: */
	ret = of_property_read_string_index(node, "compatible", 0, &compat);
	if (ret == 0) {
<<<<<<< HEAD
		unsigned int r, patch;

		if (sscanf(compat, "qcom,adreno-%u.%u", &r, &patch) == 2) {
			rev->core = r / 100;
			r %= 100;
			rev->major = r / 10;
			r %= 10;
			rev->minor = r;
			rev->patchid = patch;
=======
		unsigned rev, patch;

		if (sscanf(compat, "qcom,adreno-%u.%u", &rev, &patch) == 2) {
			*chipid = 0;
			*chipid |= (rev / 100) << 24;  /* core */
			rev %= 100;
			*chipid |= (rev / 10) << 16;   /* major */
			rev %= 10;
			*chipid |= rev << 8;           /* minor */
			*chipid |= patch;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			return 0;
		}
	}

	/* and if that fails, fall back to legacy "qcom,chipid" property: */
<<<<<<< HEAD
	ret = of_property_read_u32(node, "qcom,chipid", &chipid);
	if (ret) {
		dev_err(dev, "could not parse qcom,chipid: %d\n", ret);
		return ret;
	}

	rev->core = (chipid >> 24) & 0xff;
	rev->major = (chipid >> 16) & 0xff;
	rev->minor = (chipid >> 8) & 0xff;
	rev->patchid = (chipid & 0xff);

	dev_warn(dev, "Using legacy qcom,chipid binding!\n");
	dev_warn(dev, "Use compatible qcom,adreno-%u%u%u.%u instead.\n",
		rev->core, rev->major, rev->minor, rev->patchid);
=======
	ret = of_property_read_u32(node, "qcom,chipid", chipid);
	if (ret)
		return ret;

	dev_warn(dev, "Using legacy qcom,chipid binding!\n");
	dev_warn(dev, "Use compatible qcom,adreno-%u%u%u.%u instead.\n",
			(*chipid >> 24) & 0xff, (*chipid >> 16) & 0xff,
			(*chipid >> 8) & 0xff, *chipid & 0xff);

	return 0;
}

/* Get legacy powerlevels from qcom,gpu-pwrlevels and populate the opp table */
static int adreno_get_legacy_pwrlevels(struct device *dev)
{
	struct device_node *child, *node;
	int ret;

	node = of_get_compatible_child(dev->of_node, "qcom,gpu-pwrlevels");
	if (!node) {
		dev_err(dev, "Could not find the GPU powerlevels\n");
		return -ENXIO;
	}

	for_each_child_of_node(node, child) {
		unsigned int val;

		ret = of_property_read_u32(child, "qcom,gpu-freq", &val);
		if (ret)
			continue;

		/*
		 * Skip the intentionally bogus clock value found at the bottom
		 * of most legacy frequency tables
		 */
		if (val != 27000000)
			dev_pm_opp_add(dev, val, 0);
	}

	of_node_put(node);

	return 0;
}

static int adreno_get_pwrlevels(struct device *dev,
		struct adreno_platform_config *config)
{
	unsigned long freq = ULONG_MAX;
	struct dev_pm_opp *opp;
	int ret;

	/* You down with OPP? */
	if (!of_find_property(dev->of_node, "operating-points-v2", NULL))
		ret = adreno_get_legacy_pwrlevels(dev);
	else
		ret = dev_pm_opp_of_add_table(dev);

	if (ret)
		return ret;

	/* Find the fastest defined rate */
	opp = dev_pm_opp_find_freq_floor(dev, &freq);
	if (!IS_ERR(opp))
		config->fast_rate = dev_pm_opp_get_freq(opp);

	if (!config->fast_rate) {
		DRM_DEV_INFO(dev,
			"Could not find clock rate. Using default\n");
		/* Pick a suitably safe clock speed for any target */
		config->fast_rate = 200000000;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

static int adreno_bind(struct device *dev, struct device *master, void *data)
{
	static struct adreno_platform_config config = {};
<<<<<<< HEAD
	const struct adreno_info *info;
	struct drm_device *drm = dev_get_drvdata(master);
	struct msm_gpu *gpu;
	int ret;

	ret = find_chipid(dev, &config.rev);
=======
	u32 val;
	int ret;

	ret = find_chipid(dev, &val);
	if (ret) {
		dev_err(dev, "could not find chipid: %d\n", ret);
		return ret;
	}

	config.rev = ADRENO_REV((val >> 24) & 0xff,
			(val >> 16) & 0xff, (val >> 8) & 0xff, val & 0xff);

	/* find clock rates: */
	config.fast_rate = 0;

	ret = adreno_get_pwrlevels(dev, &config);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret)
		return ret;

	dev->platform_data = &config;
<<<<<<< HEAD
	set_gpu_pdev(drm, to_platform_device(dev));

	info = adreno_info(config.rev);

	if (!info) {
		dev_warn(drm->dev, "Unknown GPU revision: %u.%u.%u.%u\n",
			config.rev.core, config.rev.major,
			config.rev.minor, config.rev.patchid);
		return -ENXIO;
	}

	DBG("Found GPU: %u.%u.%u.%u", config.rev.core, config.rev.major,
		config.rev.minor, config.rev.patchid);

	gpu = info->init(drm);
	if (IS_ERR(gpu)) {
		dev_warn(drm->dev, "failed to load adreno gpu\n");
		return PTR_ERR(gpu);
	}

	dev_set_drvdata(dev, gpu);

=======
	set_gpu_pdev(dev_get_drvdata(master), to_platform_device(dev));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

static void adreno_unbind(struct device *dev, struct device *master,
		void *data)
{
<<<<<<< HEAD
	struct msm_gpu *gpu = dev_get_drvdata(dev);

	gpu->funcs->pm_suspend(gpu);
	gpu->funcs->destroy(gpu);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	set_gpu_pdev(dev_get_drvdata(master), NULL);
}

static const struct component_ops a3xx_ops = {
		.bind   = adreno_bind,
		.unbind = adreno_unbind,
};

static int adreno_probe(struct platform_device *pdev)
{
	return component_add(&pdev->dev, &a3xx_ops);
}

static int adreno_remove(struct platform_device *pdev)
{
	component_del(&pdev->dev, &a3xx_ops);
	return 0;
}

static const struct of_device_id dt_match[] = {
	{ .compatible = "qcom,adreno" },
	{ .compatible = "qcom,adreno-3xx" },
	/* for backwards compat w/ downstream kgsl DT files: */
	{ .compatible = "qcom,kgsl-3d0" },
	{}
};

#ifdef CONFIG_PM
static int adreno_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct msm_gpu *gpu = platform_get_drvdata(pdev);

	return gpu->funcs->pm_resume(gpu);
}

static int adreno_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct msm_gpu *gpu = platform_get_drvdata(pdev);

	return gpu->funcs->pm_suspend(gpu);
}
#endif

static const struct dev_pm_ops adreno_pm_ops = {
<<<<<<< HEAD
	SET_SYSTEM_SLEEP_PM_OPS(pm_runtime_force_suspend, pm_runtime_force_resume)
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	SET_RUNTIME_PM_OPS(adreno_suspend, adreno_resume, NULL)
};

static struct platform_driver adreno_driver = {
	.probe = adreno_probe,
	.remove = adreno_remove,
	.driver = {
		.name = "adreno",
		.of_match_table = dt_match,
		.pm = &adreno_pm_ops,
	},
};

void __init adreno_register(void)
{
	platform_driver_register(&adreno_driver);
}

void __exit adreno_unregister(void)
{
	platform_driver_unregister(&adreno_driver);
}
