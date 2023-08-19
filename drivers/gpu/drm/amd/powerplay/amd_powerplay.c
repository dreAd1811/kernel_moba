/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#include "pp_debug.h"
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/gfp.h>
#include <linux/slab.h>
<<<<<<< HEAD
#include <linux/firmware.h>
#include "amd_shared.h"
#include "amd_powerplay.h"
#include "power_state.h"
#include "amdgpu.h"
#include "hwmgr.h"


static const struct amd_pm_funcs pp_dpm_funcs;

static int amd_powerplay_create(struct amdgpu_device *adev)
{
	struct pp_hwmgr *hwmgr;

	if (adev == NULL)
		return -EINVAL;

	hwmgr = kzalloc(sizeof(struct pp_hwmgr), GFP_KERNEL);
	if (hwmgr == NULL)
		return -ENOMEM;

	hwmgr->adev = adev;
	hwmgr->not_vf = !amdgpu_sriov_vf(adev);
	hwmgr->pm_en = (amdgpu_dpm && hwmgr->not_vf) ? true : false;
	hwmgr->device = amdgpu_cgs_create_device(adev);
	mutex_init(&hwmgr->smu_lock);
	hwmgr->chip_family = adev->family;
	hwmgr->chip_id = adev->asic_type;
	hwmgr->feature_mask = adev->powerplay.pp_feature;
	hwmgr->display_config = &adev->pm.pm_display_cfg;
	adev->powerplay.pp_handle = hwmgr;
	adev->powerplay.pp_funcs = &pp_dpm_funcs;
	return 0;
}


static void amd_powerplay_destroy(struct amdgpu_device *adev)
{
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	kfree(hwmgr->hardcode_pp_table);
	hwmgr->hardcode_pp_table = NULL;

	kfree(hwmgr);
	hwmgr = NULL;
}

static int pp_early_init(void *handle)
{
	int ret;
	struct amdgpu_device *adev = handle;

	ret = amd_powerplay_create(adev);

	if (ret != 0)
		return ret;

	ret = hwmgr_early_init(adev->powerplay.pp_handle);
	if (ret)
		return -EINVAL;
=======
#include "amd_shared.h"
#include "amd_powerplay.h"
#include "pp_instance.h"
#include "power_state.h"
#include "eventmanager.h"


static inline int pp_check(struct pp_instance *handle)
{
	if (handle == NULL || handle->pp_valid != PP_VALID)
		return -EINVAL;

	if (handle->smu_mgr == NULL || handle->smu_mgr->smumgr_funcs == NULL)
		return -EINVAL;

	if (handle->pm_en == 0)
		return PP_DPM_DISABLED;

	if (handle->hwmgr == NULL || handle->hwmgr->hwmgr_func == NULL
		|| handle->eventmgr == NULL)
		return PP_DPM_DISABLED;

	return 0;
}

static int pp_early_init(void *handle)
{
	int ret;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	ret = smum_early_init(pp_handle);
	if (ret)
		return ret;

	if ((pp_handle->pm_en == 0)
		|| cgs_is_virtualization_enabled(pp_handle->device))
		return PP_DPM_DISABLED;

	ret = hwmgr_early_init(pp_handle);
	if (ret) {
		pp_handle->pm_en = 0;
		return PP_DPM_DISABLED;
	}

	ret = eventmgr_early_init(pp_handle);
	if (ret) {
		kfree(pp_handle->hwmgr);
		pp_handle->hwmgr = NULL;
		pp_handle->pm_en = 0;
		return PP_DPM_DISABLED;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

static int pp_sw_init(void *handle)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;
	int ret = 0;

	ret = hwmgr_sw_init(hwmgr);

	pr_debug("powerplay sw init %s\n", ret ? "failed" : "successfully");

=======
	struct pp_smumgr *smumgr;
	int ret = 0;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	ret = pp_check(pp_handle);

	if (ret == 0 || ret == PP_DPM_DISABLED) {
		smumgr = pp_handle->smu_mgr;

		if (smumgr->smumgr_funcs->smu_init == NULL)
			return -EINVAL;

		ret = smumgr->smumgr_funcs->smu_init(smumgr);

		pr_info("amdgpu: powerplay sw initialized\n");
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_sw_fini(void *handle)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	hwmgr_sw_fini(hwmgr);

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_SMU) {
		release_firmware(adev->pm.fw);
		adev->pm.fw = NULL;
		amdgpu_ucode_fini_bo(adev);
	}

	return 0;
=======
	struct pp_smumgr *smumgr;
	int ret = 0;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	ret = pp_check(pp_handle);
	if (ret == 0 || ret == PP_DPM_DISABLED) {
		smumgr = pp_handle->smu_mgr;

		if (smumgr->smumgr_funcs->smu_fini == NULL)
			return -EINVAL;

		ret = smumgr->smumgr_funcs->smu_fini(smumgr);
	}
	return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int pp_hw_init(void *handle)
{
<<<<<<< HEAD
	int ret = 0;
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_SMU)
		amdgpu_ucode_init_bo(adev);

	ret = hwmgr_hw_init(hwmgr);

	if (ret)
		pr_err("powerplay hw init failed\n");

	return ret;
=======
	struct pp_smumgr *smumgr;
	struct pp_eventmgr *eventmgr;
	int ret = 0;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	ret = pp_check(pp_handle);

	if (ret == 0 || ret == PP_DPM_DISABLED) {
		smumgr = pp_handle->smu_mgr;

		if (smumgr->smumgr_funcs->start_smu == NULL)
			return -EINVAL;

		if(smumgr->smumgr_funcs->start_smu(smumgr)) {
			pr_err("smc start failed\n");
			smumgr->smumgr_funcs->smu_fini(smumgr);
			return -EINVAL;;
		}
		if (ret == PP_DPM_DISABLED)
			return PP_DPM_DISABLED;
	}

	ret = hwmgr_hw_init(pp_handle);
	if (ret)
		goto err;

	eventmgr = pp_handle->eventmgr;
	if (eventmgr->pp_eventmgr_init == NULL ||
		eventmgr->pp_eventmgr_init(eventmgr))
		goto err;

	return 0;
err:
	pp_handle->pm_en = 0;
	kfree(pp_handle->eventmgr);
	kfree(pp_handle->hwmgr);
	pp_handle->hwmgr = NULL;
	pp_handle->eventmgr = NULL;
	return PP_DPM_DISABLED;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int pp_hw_fini(void *handle)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	hwmgr_hw_fini(hwmgr);

	return 0;
}

static void pp_reserve_vram_for_smu(struct amdgpu_device *adev)
{
	int r = -EINVAL;
	void *cpu_ptr = NULL;
	uint64_t gpu_addr;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	if (amdgpu_bo_create_kernel(adev, adev->pm.smu_prv_buffer_size,
						PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
						&adev->pm.smu_prv_buffer,
						&gpu_addr,
						&cpu_ptr)) {
		DRM_ERROR("amdgpu: failed to create smu prv buffer\n");
		return;
	}

	if (hwmgr->hwmgr_func->notify_cac_buffer_info)
		r = hwmgr->hwmgr_func->notify_cac_buffer_info(hwmgr,
					lower_32_bits((unsigned long)cpu_ptr),
					upper_32_bits((unsigned long)cpu_ptr),
					lower_32_bits(gpu_addr),
					upper_32_bits(gpu_addr),
					adev->pm.smu_prv_buffer_size);

	if (r) {
		amdgpu_bo_free_kernel(&adev->pm.smu_prv_buffer, NULL, NULL);
		adev->pm.smu_prv_buffer = NULL;
		DRM_ERROR("amdgpu: failed to notify SMU buffer address\n");
	}
}

static int pp_late_init(void *handle)
{
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	if (hwmgr && hwmgr->pm_en) {
		mutex_lock(&hwmgr->smu_lock);
		hwmgr_handle_task(hwmgr,
					AMD_PP_TASK_COMPLETE_INIT, NULL);
		mutex_unlock(&hwmgr->smu_lock);
	}
	if (adev->pm.smu_prv_buffer_size != 0)
		pp_reserve_vram_for_smu(adev);

	return 0;
}

static void pp_late_fini(void *handle)
{
	struct amdgpu_device *adev = handle;

	if (adev->pm.smu_prv_buffer)
		amdgpu_bo_free_kernel(&adev->pm.smu_prv_buffer, NULL, NULL);
	amd_powerplay_destroy(adev);
}


=======
	struct pp_eventmgr *eventmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret == 0) {
		eventmgr = pp_handle->eventmgr;

		if (eventmgr->pp_eventmgr_fini != NULL)
			eventmgr->pp_eventmgr_fini(eventmgr);

		hwmgr_hw_fini(pp_handle);
	}
	return 0;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static bool pp_is_idle(void *handle)
{
	return false;
}

static int pp_wait_for_idle(void *handle)
{
	return 0;
}

static int pp_sw_reset(void *handle)
{
	return 0;
}

<<<<<<< HEAD
static int pp_set_powergating_state(void *handle,
				    enum amd_powergating_state state)
{
	return 0;
=======

int amd_set_clockgating_by_smu(void *handle, uint32_t msg_id)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->update_clock_gatings == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

	return hwmgr->hwmgr_func->update_clock_gatings(hwmgr, &msg_id);
}

static int pp_set_powergating_state(void *handle,
				    enum amd_powergating_state state)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->enable_per_cu_power_gating == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

	/* Enable/disable GFX per cu powergating through SMU */
	return hwmgr->hwmgr_func->enable_per_cu_power_gating(hwmgr,
			state == AMD_PG_STATE_GATE);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int pp_suspend(void *handle)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	return hwmgr_suspend(hwmgr);
=======
	struct pp_eventmgr *eventmgr;
	struct pem_event_data event_data = { {0} };
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret == PP_DPM_DISABLED)
		return 0;
	else if (ret != 0)
		return ret;

	eventmgr = pp_handle->eventmgr;
	pem_handle_event(eventmgr, AMD_PP_EVENT_SUSPEND, &event_data);

	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int pp_resume(void *handle)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	return hwmgr_resume(hwmgr);
}

static int pp_set_clockgating_state(void *handle,
					  enum amd_clockgating_state state)
{
	return 0;
}

static const struct amd_ip_funcs pp_ip_funcs = {
	.name = "powerplay",
	.early_init = pp_early_init,
	.late_init = pp_late_init,
=======
	struct pp_eventmgr *eventmgr;
	struct pem_event_data event_data = { {0} };
	struct pp_smumgr *smumgr;
	int ret, ret1;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	ret1 = pp_check(pp_handle);

	if (ret1 != 0 && ret1 != PP_DPM_DISABLED)
		return ret1;

	smumgr = pp_handle->smu_mgr;

	if (smumgr->smumgr_funcs->start_smu == NULL)
		return -EINVAL;

	ret = smumgr->smumgr_funcs->start_smu(smumgr);
	if (ret) {
		pr_err("smc start failed\n");
		smumgr->smumgr_funcs->smu_fini(smumgr);
		return ret;
	}

	if (ret1 == PP_DPM_DISABLED)
		return 0;

	eventmgr = pp_handle->eventmgr;

	pem_handle_event(eventmgr, AMD_PP_EVENT_RESUME, &event_data);

	return 0;
}

const struct amd_ip_funcs pp_ip_funcs = {
	.name = "powerplay",
	.early_init = pp_early_init,
	.late_init = NULL,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.sw_init = pp_sw_init,
	.sw_fini = pp_sw_fini,
	.hw_init = pp_hw_init,
	.hw_fini = pp_hw_fini,
<<<<<<< HEAD
	.late_fini = pp_late_fini,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.suspend = pp_suspend,
	.resume = pp_resume,
	.is_idle = pp_is_idle,
	.wait_for_idle = pp_wait_for_idle,
	.soft_reset = pp_sw_reset,
<<<<<<< HEAD
	.set_clockgating_state = pp_set_clockgating_state,
	.set_powergating_state = pp_set_powergating_state,
};

const struct amdgpu_ip_block_version pp_smu_ip_block =
{
	.type = AMD_IP_BLOCK_TYPE_SMC,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &pp_ip_funcs,
};

=======
	.set_clockgating_state = NULL,
	.set_powergating_state = pp_set_powergating_state,
};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int pp_dpm_load_fw(void *handle)
{
	return 0;
}

static int pp_dpm_fw_loading_complete(void *handle)
{
	return 0;
}

<<<<<<< HEAD
static int pp_set_clockgating_by_smu(void *handle, uint32_t msg_id)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (hwmgr->hwmgr_func->update_clock_gatings == NULL) {
=======
static int pp_dpm_force_performance_level(void *handle,
					enum amd_dpm_forced_level level)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->force_dpm_level == NULL) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

<<<<<<< HEAD
	return hwmgr->hwmgr_func->update_clock_gatings(hwmgr, &msg_id);
}

static void pp_dpm_en_umd_pstate(struct pp_hwmgr  *hwmgr,
						enum amd_dpm_forced_level *level)
{
	uint32_t profile_mode_mask = AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD |
					AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK |
					AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK |
					AMD_DPM_FORCED_LEVEL_PROFILE_PEAK;

	if (!(hwmgr->dpm_level & profile_mode_mask)) {
		/* enter umd pstate, save current level, disable gfx cg*/
		if (*level & profile_mode_mask) {
			hwmgr->saved_dpm_level = hwmgr->dpm_level;
			hwmgr->en_umd_pstate = true;
			amdgpu_device_ip_set_clockgating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_GFX,
						AMD_CG_STATE_UNGATE);
			amdgpu_device_ip_set_powergating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_GFX,
					AMD_PG_STATE_UNGATE);
		}
	} else {
		/* exit umd pstate, restore level, enable gfx cg*/
		if (!(*level & profile_mode_mask)) {
			if (*level == AMD_DPM_FORCED_LEVEL_PROFILE_EXIT)
				*level = hwmgr->saved_dpm_level;
			hwmgr->en_umd_pstate = false;
			amdgpu_device_ip_set_clockgating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_GFX,
					AMD_CG_STATE_GATE);
			amdgpu_device_ip_set_powergating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_GFX,
					AMD_PG_STATE_GATE);
		}
	}
}

static int pp_dpm_force_performance_level(void *handle,
					enum amd_dpm_forced_level level)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (level == hwmgr->dpm_level)
		return 0;

	mutex_lock(&hwmgr->smu_lock);
	pp_dpm_en_umd_pstate(hwmgr, &level);
	hwmgr->request_dpm_level = level;
	hwmgr_handle_task(hwmgr, AMD_PP_TASK_READJUST_POWER_STATE, NULL);
	mutex_unlock(&hwmgr->smu_lock);

=======
	mutex_lock(&pp_handle->pp_lock);
	hwmgr->hwmgr_func->force_dpm_level(hwmgr, level);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

static enum amd_dpm_forced_level pp_dpm_get_performance_level(
								void *handle)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	enum amd_dpm_forced_level level;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	level = hwmgr->dpm_level;
	mutex_unlock(&hwmgr->smu_lock);
	return level;
}

static uint32_t pp_dpm_get_sclk(void *handle, bool low)
{
	struct pp_hwmgr *hwmgr = handle;
	uint32_t clk = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return 0;
=======
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;
	enum amd_dpm_forced_level level;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
	mutex_lock(&pp_handle->pp_lock);
	level = hwmgr->dpm_level;
	mutex_unlock(&pp_handle->pp_lock);
	return level;
}

static int pp_dpm_get_sclk(void *handle, bool low)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->get_sclk == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	clk = hwmgr->hwmgr_func->get_sclk(hwmgr, low);
	mutex_unlock(&hwmgr->smu_lock);
	return clk;
}

static uint32_t pp_dpm_get_mclk(void *handle, bool low)
{
	struct pp_hwmgr *hwmgr = handle;
	uint32_t clk = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return 0;
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->get_sclk(hwmgr, low);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

static int pp_dpm_get_mclk(void *handle, bool low)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->get_mclk == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	clk = hwmgr->hwmgr_func->get_mclk(hwmgr, low);
	mutex_unlock(&hwmgr->smu_lock);
	return clk;
}

static void pp_dpm_powergate_vce(void *handle, bool gate)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return;

	if (hwmgr->hwmgr_func->powergate_vce == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return;
	}
	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->powergate_vce(hwmgr, gate);
	mutex_unlock(&hwmgr->smu_lock);
}

static void pp_dpm_powergate_uvd(void *handle, bool gate)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return;

	if (hwmgr->hwmgr_func->powergate_uvd == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return;
	}
	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->powergate_uvd(hwmgr, gate);
	mutex_unlock(&hwmgr->smu_lock);
}

static int pp_dpm_dispatch_tasks(void *handle, enum amd_pp_task task_id,
		enum amd_pm_state_type *user_state)
{
	int ret = 0;
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr_handle_task(hwmgr, task_id, user_state);
	mutex_unlock(&hwmgr->smu_lock);

=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->get_mclk(hwmgr, low);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

static int pp_dpm_powergate_vce(void *handle, bool gate)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->powergate_vce == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->powergate_vce(hwmgr, gate);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

static int pp_dpm_powergate_uvd(void *handle, bool gate)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->powergate_uvd == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->powergate_uvd(hwmgr, gate);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

static enum PP_StateUILabel power_state_convert(enum amd_pm_state_type  state)
{
	switch (state) {
	case POWER_STATE_TYPE_BATTERY:
		return PP_StateUILabel_Battery;
	case POWER_STATE_TYPE_BALANCED:
		return PP_StateUILabel_Balanced;
	case POWER_STATE_TYPE_PERFORMANCE:
		return PP_StateUILabel_Performance;
	default:
		return PP_StateUILabel_None;
	}
}

static int pp_dpm_dispatch_tasks(void *handle, enum amd_pp_event event_id,
		void *input, void *output)
{
	int ret = 0;
	struct pem_event_data data = { {0} };
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;
	mutex_lock(&pp_handle->pp_lock);
	switch (event_id) {
	case AMD_PP_EVENT_DISPLAY_CONFIG_CHANGE:
		ret = pem_handle_event(pp_handle->eventmgr, event_id, &data);
		break;
	case AMD_PP_EVENT_ENABLE_USER_STATE:
	{
		enum amd_pm_state_type  ps;

		if (input == NULL) {
			ret = -EINVAL;
			break;
		}
		ps = *(unsigned long *)input;

		data.requested_ui_label = power_state_convert(ps);
		ret = pem_handle_event(pp_handle->eventmgr, event_id, &data);
		break;
	}
	case AMD_PP_EVENT_COMPLETE_INIT:
		ret = pem_handle_event(pp_handle->eventmgr, event_id, &data);
		break;
	case AMD_PP_EVENT_READJUST_POWER_STATE:
		ret = pem_handle_event(pp_handle->eventmgr, event_id, &data);
		break;
	default:
		break;
	}
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static enum amd_pm_state_type pp_dpm_get_current_power_state(void *handle)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	struct pp_power_state *state;
	enum amd_pm_state_type pm_type;

	if (!hwmgr || !hwmgr->pm_en || !hwmgr->current_ps)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
=======
	struct pp_hwmgr *hwmgr;
	struct pp_power_state *state;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;
	enum amd_pm_state_type pm_type;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->current_ps == NULL)
		return -EINVAL;

	mutex_lock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	state = hwmgr->current_ps;

	switch (state->classification.ui_label) {
	case PP_StateUILabel_Battery:
		pm_type = POWER_STATE_TYPE_BATTERY;
		break;
	case PP_StateUILabel_Balanced:
		pm_type = POWER_STATE_TYPE_BALANCED;
		break;
	case PP_StateUILabel_Performance:
		pm_type = POWER_STATE_TYPE_PERFORMANCE;
		break;
	default:
		if (state->classification.flags & PP_StateClassificationFlag_Boot)
			pm_type = POWER_STATE_TYPE_INTERNAL_BOOT;
		else
			pm_type = POWER_STATE_TYPE_DEFAULT;
		break;
	}
<<<<<<< HEAD
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return pm_type;
}

<<<<<<< HEAD
static void pp_dpm_set_fan_control_mode(void *handle, uint32_t mode)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return;

	if (hwmgr->hwmgr_func->set_fan_control_mode == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return;
	}
	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_fan_control_mode(hwmgr, mode);
	mutex_unlock(&hwmgr->smu_lock);
}

static uint32_t pp_dpm_get_fan_control_mode(void *handle)
{
	struct pp_hwmgr *hwmgr = handle;
	uint32_t mode = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return 0;
=======
static int pp_dpm_set_fan_control_mode(void *handle, uint32_t mode)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->set_fan_control_mode == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->set_fan_control_mode(hwmgr, mode);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

static int pp_dpm_get_fan_control_mode(void *handle)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->get_fan_control_mode == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	mode = hwmgr->hwmgr_func->get_fan_control_mode(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);
	return mode;
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->get_fan_control_mode(hwmgr);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int pp_dpm_set_fan_speed_percent(void *handle, uint32_t percent)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->set_fan_speed_percent == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_fan_speed_percent(hwmgr, percent);
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->set_fan_speed_percent(hwmgr, percent);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_get_fan_speed_percent(void *handle, uint32_t *speed)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->get_fan_speed_percent == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_fan_speed_percent(hwmgr, speed);
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->get_fan_speed_percent(hwmgr, speed);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_get_fan_speed_rpm(void *handle, uint32_t *rpm)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->get_fan_speed_rpm == NULL)
		return -EINVAL;

<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_fan_speed_rpm(hwmgr, rpm);
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->get_fan_speed_rpm(hwmgr, rpm);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

static int pp_dpm_get_temperature(void *handle)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->get_temperature == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->get_temperature(hwmgr);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_get_pp_num_states(void *handle,
		struct pp_states_info *data)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int i;

	memset(data, 0, sizeof(*data));

	if (!hwmgr || !hwmgr->pm_en ||!hwmgr->ps)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
=======
	struct pp_hwmgr *hwmgr;
	int i;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->ps == NULL)
		return -EINVAL;

	mutex_lock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	data->nums = hwmgr->num_ps;

	for (i = 0; i < hwmgr->num_ps; i++) {
		struct pp_power_state *state = (struct pp_power_state *)
				((unsigned long)hwmgr->ps + i * hwmgr->ps_size);
		switch (state->classification.ui_label) {
		case PP_StateUILabel_Battery:
			data->states[i] = POWER_STATE_TYPE_BATTERY;
			break;
		case PP_StateUILabel_Balanced:
			data->states[i] = POWER_STATE_TYPE_BALANCED;
			break;
		case PP_StateUILabel_Performance:
			data->states[i] = POWER_STATE_TYPE_PERFORMANCE;
			break;
		default:
			if (state->classification.flags & PP_StateClassificationFlag_Boot)
				data->states[i] = POWER_STATE_TYPE_INTERNAL_BOOT;
			else
				data->states[i] = POWER_STATE_TYPE_DEFAULT;
		}
	}
<<<<<<< HEAD
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

static int pp_dpm_get_pp_table(void *handle, char **table)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int size = 0;

	if (!hwmgr || !hwmgr->pm_en ||!hwmgr->soft_pp_table)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	*table = (char *)hwmgr->soft_pp_table;
	size = hwmgr->soft_pp_table_size;
	mutex_unlock(&hwmgr->smu_lock);
	return size;
}

static int amd_powerplay_reset(void *handle)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret;

	ret = hwmgr_hw_fini(hwmgr);
	if (ret)
		return ret;

	ret = hwmgr_hw_init(hwmgr);
	if (ret)
		return ret;

	return hwmgr_handle_task(hwmgr, AMD_PP_TASK_COMPLETE_INIT, NULL);
}

static int pp_dpm_set_pp_table(void *handle, const char *buf, size_t size)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = -ENOMEM;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;
	int size = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (!hwmgr->soft_pp_table)
		return -EINVAL;

	mutex_lock(&pp_handle->pp_lock);
	*table = (char *)hwmgr->soft_pp_table;
	size = hwmgr->soft_pp_table_size;
	mutex_unlock(&pp_handle->pp_lock);
	return size;
}

static int pp_dpm_set_pp_table(void *handle, const char *buf, size_t size)
{
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
	mutex_lock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!hwmgr->hardcode_pp_table) {
		hwmgr->hardcode_pp_table = kmemdup(hwmgr->soft_pp_table,
						   hwmgr->soft_pp_table_size,
						   GFP_KERNEL);
<<<<<<< HEAD
		if (!hwmgr->hardcode_pp_table)
			goto err;
=======
		if (!hwmgr->hardcode_pp_table) {
			mutex_unlock(&pp_handle->pp_lock);
			return -ENOMEM;
		}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	memcpy(hwmgr->hardcode_pp_table, buf, size);

	hwmgr->soft_pp_table = hwmgr->hardcode_pp_table;
<<<<<<< HEAD

	ret = amd_powerplay_reset(handle);
	if (ret)
		goto err;
=======
	mutex_unlock(&pp_handle->pp_lock);

	ret = amd_powerplay_reset(handle);
	if (ret)
		return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->avfs_control) {
		ret = hwmgr->hwmgr_func->avfs_control(hwmgr, false);
		if (ret)
<<<<<<< HEAD
			goto err;
	}
	mutex_unlock(&hwmgr->smu_lock);
	return 0;
err:
	mutex_unlock(&hwmgr->smu_lock);
	return ret;
=======
			return ret;
	}

	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int pp_dpm_force_clock_level(void *handle,
		enum pp_clock_type type, uint32_t mask)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->force_clock_level == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL)
		ret = hwmgr->hwmgr_func->force_clock_level(hwmgr, type, mask);
	else
		ret = -EINVAL;
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	hwmgr->hwmgr_func->force_clock_level(hwmgr, type, mask);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_print_clock_levels(void *handle,
		enum pp_clock_type type, char *buf)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->print_clock_levels == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->print_clock_levels(hwmgr, type, buf);
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->print_clock_levels(hwmgr, type, buf);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_get_sclk_od(void *handle)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->get_sclk_od == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_sclk_od(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->get_sclk_od(hwmgr);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_set_sclk_od(void *handle, uint32_t value)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->set_sclk_od == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_sclk_od(hwmgr, value);
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->set_sclk_od(hwmgr, value);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_get_mclk_od(void *handle)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->get_mclk_od == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_mclk_od(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->get_mclk_od(hwmgr);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_set_mclk_od(void *handle, uint32_t value)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->hwmgr_func->set_mclk_od == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_mclk_od(hwmgr, value);
	mutex_unlock(&hwmgr->smu_lock);
=======
	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->set_mclk_od(hwmgr, value);
	mutex_unlock(&pp_handle->pp_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static int pp_dpm_read_sensor(void *handle, int idx,
			      void *value, int *size)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en || !value)
		return -EINVAL;

	switch (idx) {
	case AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK:
		*((uint32_t *)value) = hwmgr->pstate_sclk;
		return 0;
	case AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK:
		*((uint32_t *)value) = hwmgr->pstate_mclk;
		return 0;
	default:
		mutex_lock(&hwmgr->smu_lock);
		ret = hwmgr->hwmgr_func->read_sensor(hwmgr, idx, value, size);
		mutex_unlock(&hwmgr->smu_lock);
		return ret;
	}
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->read_sensor == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

	mutex_lock(&pp_handle->pp_lock);
	ret = hwmgr->hwmgr_func->read_sensor(hwmgr, idx, value, size);
	mutex_unlock(&pp_handle->pp_lock);

	return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static struct amd_vce_state*
pp_dpm_get_vce_clock_state(void *handle, unsigned idx)
{
<<<<<<< HEAD
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return NULL;

	if (idx < hwmgr->num_vce_state_tables)
=======
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return NULL;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr && idx < hwmgr->num_vce_state_tables)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return &hwmgr->vce_states[idx];
	return NULL;
}

<<<<<<< HEAD
static int pp_get_power_profile_mode(void *handle, char *buf)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en || !buf)
		return -EINVAL;

	if (hwmgr->hwmgr_func->get_power_profile_mode == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return snprintf(buf, PAGE_SIZE, "\n");
	}

	return hwmgr->hwmgr_func->get_power_profile_mode(hwmgr, buf);
}

static int pp_set_power_profile_mode(void *handle, long *input, uint32_t size)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = -EINVAL;

	if (!hwmgr || !hwmgr->pm_en)
		return ret;

	if (hwmgr->hwmgr_func->set_power_profile_mode == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return ret;
	}
	mutex_lock(&hwmgr->smu_lock);
	if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL)
		ret = hwmgr->hwmgr_func->set_power_profile_mode(hwmgr, input, size);
	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}

static int pp_odn_edit_dpm_table(void *handle, uint32_t type, long *input, uint32_t size)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (hwmgr->hwmgr_func->odn_edit_dpm_table == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return -EINVAL;
	}

	return hwmgr->hwmgr_func->odn_edit_dpm_table(hwmgr, type, input, size);
}

static int pp_dpm_switch_power_profile(void *handle,
		enum PP_SMC_POWER_PROFILE type, bool en)
{
	struct pp_hwmgr *hwmgr = handle;
	long workload;
	uint32_t index;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (hwmgr->hwmgr_func->set_power_profile_mode == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return -EINVAL;
	}

	if (!(type < PP_SMC_POWER_PROFILE_CUSTOM))
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	if (!en) {
		hwmgr->workload_mask &= ~(1 << hwmgr->workload_prority[type]);
		index = fls(hwmgr->workload_mask);
		index = index > 0 && index <= Workload_Policy_Max ? index - 1 : 0;
		workload = hwmgr->workload_setting[index];
	} else {
		hwmgr->workload_mask |= (1 << hwmgr->workload_prority[type]);
		index = fls(hwmgr->workload_mask);
		index = index <= Workload_Policy_Max ? index - 1 : 0;
		workload = hwmgr->workload_setting[index];
	}

	if (hwmgr->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL)
		hwmgr->hwmgr_func->set_power_profile_mode(hwmgr, &workload, 0);
	mutex_unlock(&hwmgr->smu_lock);

	return 0;
}

static int pp_set_power_limit(void *handle, uint32_t limit)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (hwmgr->hwmgr_func->set_power_limit == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return -EINVAL;
	}

	if (limit == 0)
		limit = hwmgr->default_power_limit;

	if (limit > hwmgr->default_power_limit)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_power_limit(hwmgr, limit);
	hwmgr->power_limit = limit;
	mutex_unlock(&hwmgr->smu_lock);
	return 0;
}

static int pp_get_power_limit(void *handle, uint32_t *limit, bool default_limit)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en ||!limit)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	if (default_limit)
		*limit = hwmgr->default_power_limit;
	else
		*limit = hwmgr->power_limit;

	mutex_unlock(&hwmgr->smu_lock);

	return 0;
}

static int pp_display_configuration_change(void *handle,
	const struct amd_pp_display_configuration *display_config)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	phm_store_dal_configuration_data(hwmgr, display_config);
	mutex_unlock(&hwmgr->smu_lock);
	return 0;
}

static int pp_get_display_power_level(void *handle,
		struct amd_pp_simple_clock_info *output)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!output)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_get_dal_power_level(hwmgr, output);
	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}

static int pp_get_current_clocks(void *handle,
		struct amd_pp_clock_info *clocks)
{
	struct amd_pp_simple_clock_info simple_clocks = { 0 };
	struct pp_clock_info hw_clocks;
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	phm_get_dal_power_level(hwmgr, &simple_clocks);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_PowerContainment))
		ret = phm_get_clock_info(hwmgr, &hwmgr->current_ps->hardware,
					&hw_clocks, PHM_PerformanceLevelDesignation_PowerContainment);
	else
		ret = phm_get_clock_info(hwmgr, &hwmgr->current_ps->hardware,
					&hw_clocks, PHM_PerformanceLevelDesignation_Activity);

	if (ret) {
		pr_info("Error in phm_get_clock_info \n");
		mutex_unlock(&hwmgr->smu_lock);
		return -EINVAL;
	}

	clocks->min_engine_clock = hw_clocks.min_eng_clk;
	clocks->max_engine_clock = hw_clocks.max_eng_clk;
	clocks->min_memory_clock = hw_clocks.min_mem_clk;
	clocks->max_memory_clock = hw_clocks.max_mem_clk;
	clocks->min_bus_bandwidth = hw_clocks.min_bus_bandwidth;
	clocks->max_bus_bandwidth = hw_clocks.max_bus_bandwidth;

	clocks->max_engine_clock_in_sr = hw_clocks.max_eng_clk;
	clocks->min_engine_clock_in_sr = hw_clocks.min_eng_clk;

	if (simple_clocks.level == 0)
		clocks->max_clocks_state = PP_DAL_POWERLEVEL_7;
	else
		clocks->max_clocks_state = simple_clocks.level;

	if (0 == phm_get_current_shallow_sleep_clocks(hwmgr, &hwmgr->current_ps->hardware, &hw_clocks)) {
		clocks->max_engine_clock_in_sr = hw_clocks.max_eng_clk;
		clocks->min_engine_clock_in_sr = hw_clocks.min_eng_clk;
	}
	mutex_unlock(&hwmgr->smu_lock);
	return 0;
}

static int pp_get_clock_by_type(void *handle, enum amd_pp_clock_type type, struct amd_pp_clocks *clocks)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (clocks == NULL)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_get_clock_by_type(hwmgr, type, clocks);
	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}

static int pp_get_clock_by_type_with_latency(void *handle,
		enum amd_pp_clock_type type,
		struct pp_clock_levels_with_latency *clocks)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!clocks)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_get_clock_by_type_with_latency(hwmgr, type, clocks);
	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}

static int pp_get_clock_by_type_with_voltage(void *handle,
		enum amd_pp_clock_type type,
		struct pp_clock_levels_with_voltage *clocks)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!clocks)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	ret = phm_get_clock_by_type_with_voltage(hwmgr, type, clocks);

	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}

static int pp_set_watermarks_for_clocks_ranges(void *handle,
		void *clock_ranges)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en || !clock_ranges)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_set_watermarks_for_clocks_ranges(hwmgr,
			clock_ranges);
	mutex_unlock(&hwmgr->smu_lock);

	return ret;
}

static int pp_display_clock_voltage_request(void *handle,
		struct pp_display_clock_request *clock)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!clock)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_display_clock_voltage_request(hwmgr, clock);
	mutex_unlock(&hwmgr->smu_lock);

	return ret;
}

static int pp_get_display_mode_validation_clocks(void *handle,
		struct amd_pp_simple_clock_info *clocks)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!clocks)
		return -EINVAL;

	clocks->level = PP_DAL_POWERLEVEL_7;

	mutex_lock(&hwmgr->smu_lock);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_DynamicPatchPowerState))
		ret = phm_get_max_high_clocks(hwmgr, clocks);

	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}

static int pp_dpm_powergate_mmhub(void *handle)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (hwmgr->hwmgr_func->powergate_mmhub == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

	return hwmgr->hwmgr_func->powergate_mmhub(hwmgr);
}

static int pp_dpm_powergate_gfx(void *handle, bool gate)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return 0;

	if (hwmgr->hwmgr_func->powergate_gfx == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

	return hwmgr->hwmgr_func->powergate_gfx(hwmgr, gate);
}

static int pp_set_powergating_by_smu(void *handle,
				uint32_t block_type, bool gate)
{
	int ret = 0;

	switch (block_type) {
	case AMD_IP_BLOCK_TYPE_UVD:
	case AMD_IP_BLOCK_TYPE_VCN:
		pp_dpm_powergate_uvd(handle, gate);
		break;
	case AMD_IP_BLOCK_TYPE_VCE:
		pp_dpm_powergate_vce(handle, gate);
		break;
	case AMD_IP_BLOCK_TYPE_GMC:
		pp_dpm_powergate_mmhub(handle);
		break;
	case AMD_IP_BLOCK_TYPE_GFX:
		ret = pp_dpm_powergate_gfx(handle, gate);
		break;
	default:
		break;
	}
	return ret;
}

static int pp_notify_smu_enable_pwe(void *handle)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (hwmgr->hwmgr_func->smus_notify_pwe == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return -EINVAL;;
	}

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->smus_notify_pwe(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);

	return 0;
}

static const struct amd_pm_funcs pp_dpm_funcs = {
=======
static int pp_dpm_reset_power_profile_state(void *handle,
		struct amd_pp_profile *request)
{
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	if (!request || pp_check(pp_handle))
		return -EINVAL;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->set_power_profile_state == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

	if (request->type == AMD_PP_GFX_PROFILE) {
		hwmgr->gfx_power_profile = hwmgr->default_gfx_power_profile;
		return hwmgr->hwmgr_func->set_power_profile_state(hwmgr,
				&hwmgr->gfx_power_profile);
	} else if (request->type == AMD_PP_COMPUTE_PROFILE) {
		hwmgr->compute_power_profile =
				hwmgr->default_compute_power_profile;
		return hwmgr->hwmgr_func->set_power_profile_state(hwmgr,
				&hwmgr->compute_power_profile);
	} else
		return -EINVAL;
}

static int pp_dpm_get_power_profile_state(void *handle,
		struct amd_pp_profile *query)
{
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	if (!query || pp_check(pp_handle))
		return -EINVAL;

	hwmgr = pp_handle->hwmgr;

	if (query->type == AMD_PP_GFX_PROFILE)
		memcpy(query, &hwmgr->gfx_power_profile,
				sizeof(struct amd_pp_profile));
	else if (query->type == AMD_PP_COMPUTE_PROFILE)
		memcpy(query, &hwmgr->compute_power_profile,
				sizeof(struct amd_pp_profile));
	else
		return -EINVAL;

	return 0;
}

static int pp_dpm_set_power_profile_state(void *handle,
		struct amd_pp_profile *request)
{
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = -1;

	if (!request || pp_check(pp_handle))
		return -EINVAL;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->hwmgr_func->set_power_profile_state == NULL) {
		pr_info("%s was not implemented.\n", __func__);
		return 0;
	}

	if (request->min_sclk ||
		request->min_mclk ||
		request->activity_threshold ||
		request->up_hyst ||
		request->down_hyst) {
		if (request->type == AMD_PP_GFX_PROFILE)
			memcpy(&hwmgr->gfx_power_profile, request,
					sizeof(struct amd_pp_profile));
		else if (request->type == AMD_PP_COMPUTE_PROFILE)
			memcpy(&hwmgr->compute_power_profile, request,
					sizeof(struct amd_pp_profile));
		else
			return -EINVAL;

		if (request->type == hwmgr->current_power_profile)
			ret = hwmgr->hwmgr_func->set_power_profile_state(
					hwmgr,
					request);
	} else {
		/* set power profile if it exists */
		switch (request->type) {
		case AMD_PP_GFX_PROFILE:
			ret = hwmgr->hwmgr_func->set_power_profile_state(
					hwmgr,
					&hwmgr->gfx_power_profile);
			break;
		case AMD_PP_COMPUTE_PROFILE:
			ret = hwmgr->hwmgr_func->set_power_profile_state(
					hwmgr,
					&hwmgr->compute_power_profile);
			break;
		default:
			return -EINVAL;
		}
	}

	if (!ret)
		hwmgr->current_power_profile = request->type;

	return 0;
}

static int pp_dpm_switch_power_profile(void *handle,
		enum amd_pp_profile_type type)
{
	struct pp_hwmgr *hwmgr;
	struct amd_pp_profile request = {0};
	struct pp_instance *pp_handle = (struct pp_instance *)handle;

	if (pp_check(pp_handle))
		return -EINVAL;

	hwmgr = pp_handle->hwmgr;

	if (hwmgr->current_power_profile != type) {
		request.type = type;
		pp_dpm_set_power_profile_state(handle, &request);
	}

	return 0;
}

const struct amd_powerplay_funcs pp_dpm_funcs = {
	.get_temperature = pp_dpm_get_temperature,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.load_firmware = pp_dpm_load_fw,
	.wait_for_fw_loading_complete = pp_dpm_fw_loading_complete,
	.force_performance_level = pp_dpm_force_performance_level,
	.get_performance_level = pp_dpm_get_performance_level,
	.get_current_power_state = pp_dpm_get_current_power_state,
<<<<<<< HEAD
=======
	.get_sclk = pp_dpm_get_sclk,
	.get_mclk = pp_dpm_get_mclk,
	.powergate_vce = pp_dpm_powergate_vce,
	.powergate_uvd = pp_dpm_powergate_uvd,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.dispatch_tasks = pp_dpm_dispatch_tasks,
	.set_fan_control_mode = pp_dpm_set_fan_control_mode,
	.get_fan_control_mode = pp_dpm_get_fan_control_mode,
	.set_fan_speed_percent = pp_dpm_set_fan_speed_percent,
	.get_fan_speed_percent = pp_dpm_get_fan_speed_percent,
	.get_fan_speed_rpm = pp_dpm_get_fan_speed_rpm,
	.get_pp_num_states = pp_dpm_get_pp_num_states,
	.get_pp_table = pp_dpm_get_pp_table,
	.set_pp_table = pp_dpm_set_pp_table,
	.force_clock_level = pp_dpm_force_clock_level,
	.print_clock_levels = pp_dpm_print_clock_levels,
	.get_sclk_od = pp_dpm_get_sclk_od,
	.set_sclk_od = pp_dpm_set_sclk_od,
	.get_mclk_od = pp_dpm_get_mclk_od,
	.set_mclk_od = pp_dpm_set_mclk_od,
	.read_sensor = pp_dpm_read_sensor,
	.get_vce_clock_state = pp_dpm_get_vce_clock_state,
<<<<<<< HEAD
	.switch_power_profile = pp_dpm_switch_power_profile,
	.set_clockgating_by_smu = pp_set_clockgating_by_smu,
	.set_powergating_by_smu = pp_set_powergating_by_smu,
	.get_power_profile_mode = pp_get_power_profile_mode,
	.set_power_profile_mode = pp_set_power_profile_mode,
	.odn_edit_dpm_table = pp_odn_edit_dpm_table,
	.set_power_limit = pp_set_power_limit,
	.get_power_limit = pp_get_power_limit,
/* export to DC */
	.get_sclk = pp_dpm_get_sclk,
	.get_mclk = pp_dpm_get_mclk,
	.display_configuration_change = pp_display_configuration_change,
	.get_display_power_level = pp_get_display_power_level,
	.get_current_clocks = pp_get_current_clocks,
	.get_clock_by_type = pp_get_clock_by_type,
	.get_clock_by_type_with_latency = pp_get_clock_by_type_with_latency,
	.get_clock_by_type_with_voltage = pp_get_clock_by_type_with_voltage,
	.set_watermarks_for_clocks_ranges = pp_set_watermarks_for_clocks_ranges,
	.display_clock_voltage_request = pp_display_clock_voltage_request,
	.get_display_mode_validation_clocks = pp_get_display_mode_validation_clocks,
	.notify_smu_enable_pwe = pp_notify_smu_enable_pwe,
};
=======
	.reset_power_profile_state = pp_dpm_reset_power_profile_state,
	.get_power_profile_state = pp_dpm_get_power_profile_state,
	.set_power_profile_state = pp_dpm_set_power_profile_state,
	.switch_power_profile = pp_dpm_switch_power_profile,
};

int amd_powerplay_create(struct amd_pp_init *pp_init,
				void **handle)
{
	struct pp_instance *instance;

	if (pp_init == NULL || handle == NULL)
		return -EINVAL;

	instance = kzalloc(sizeof(struct pp_instance), GFP_KERNEL);
	if (instance == NULL)
		return -ENOMEM;

	instance->pp_valid = PP_VALID;
	instance->chip_family = pp_init->chip_family;
	instance->chip_id = pp_init->chip_id;
	instance->pm_en = pp_init->pm_en;
	instance->feature_mask = pp_init->feature_mask;
	instance->device = pp_init->device;
	mutex_init(&instance->pp_lock);
	*handle = instance;
	return 0;
}

int amd_powerplay_destroy(void *handle)
{
	struct pp_instance *instance = (struct pp_instance *)handle;

	if (instance->pm_en) {
		kfree(instance->eventmgr);
		kfree(instance->hwmgr);
		instance->hwmgr = NULL;
		instance->eventmgr = NULL;
	}

	kfree(instance->smu_mgr);
	instance->smu_mgr = NULL;
	kfree(instance);
	instance = NULL;
	return 0;
}

int amd_powerplay_reset(void *handle)
{
	struct pp_instance *instance = (struct pp_instance *)handle;
	struct pp_eventmgr *eventmgr;
	struct pem_event_data event_data = { {0} };
	int ret;

	if (cgs_is_virtualization_enabled(instance->smu_mgr->device))
		return PP_DPM_DISABLED;

	ret = pp_check(instance);
	if (ret != 0)
		return ret;

	ret = pp_hw_fini(handle);
	if (ret)
		return ret;

	ret = hwmgr_hw_init(instance);
	if (ret)
		return PP_DPM_DISABLED;

	eventmgr = instance->eventmgr;

	if (eventmgr->pp_eventmgr_init == NULL)
		return PP_DPM_DISABLED;

	ret = eventmgr->pp_eventmgr_init(eventmgr);
	if (ret)
		return ret;

	return pem_handle_event(eventmgr, AMD_PP_EVENT_COMPLETE_INIT, &event_data);
}

/* export this function to DAL */

int amd_powerplay_display_configuration_change(void *handle,
	const struct amd_pp_display_configuration *display_config)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;
	mutex_lock(&pp_handle->pp_lock);
	phm_store_dal_configuration_data(hwmgr, display_config);
	mutex_unlock(&pp_handle->pp_lock);
	return 0;
}

int amd_powerplay_get_display_power_level(void *handle,
		struct amd_pp_simple_clock_info *output)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (output == NULL)
		return -EINVAL;

	mutex_lock(&pp_handle->pp_lock);
	ret = phm_get_dal_power_level(hwmgr, output);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

int amd_powerplay_get_current_clocks(void *handle,
		struct amd_pp_clock_info *clocks)
{
	struct amd_pp_simple_clock_info simple_clocks;
	struct pp_clock_info hw_clocks;
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	mutex_lock(&pp_handle->pp_lock);

	phm_get_dal_power_level(hwmgr, &simple_clocks);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_PowerContainment))
		ret = phm_get_clock_info(hwmgr, &hwmgr->current_ps->hardware,
					&hw_clocks, PHM_PerformanceLevelDesignation_PowerContainment);
	else
		ret = phm_get_clock_info(hwmgr, &hwmgr->current_ps->hardware,
					&hw_clocks, PHM_PerformanceLevelDesignation_Activity);

	if (ret != 0) {
		pr_info("Error in phm_get_clock_info \n");
		mutex_unlock(&pp_handle->pp_lock);
		return -EINVAL;
	}

	clocks->min_engine_clock = hw_clocks.min_eng_clk;
	clocks->max_engine_clock = hw_clocks.max_eng_clk;
	clocks->min_memory_clock = hw_clocks.min_mem_clk;
	clocks->max_memory_clock = hw_clocks.max_mem_clk;
	clocks->min_bus_bandwidth = hw_clocks.min_bus_bandwidth;
	clocks->max_bus_bandwidth = hw_clocks.max_bus_bandwidth;

	clocks->max_engine_clock_in_sr = hw_clocks.max_eng_clk;
	clocks->min_engine_clock_in_sr = hw_clocks.min_eng_clk;

	clocks->max_clocks_state = simple_clocks.level;

	if (0 == phm_get_current_shallow_sleep_clocks(hwmgr, &hwmgr->current_ps->hardware, &hw_clocks)) {
		clocks->max_engine_clock_in_sr = hw_clocks.max_eng_clk;
		clocks->min_engine_clock_in_sr = hw_clocks.min_eng_clk;
	}
	mutex_unlock(&pp_handle->pp_lock);
	return 0;
}

int amd_powerplay_get_clock_by_type(void *handle, enum amd_pp_clock_type type, struct amd_pp_clocks *clocks)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (clocks == NULL)
		return -EINVAL;

	mutex_lock(&pp_handle->pp_lock);
	ret = phm_get_clock_by_type(hwmgr, type, clocks);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

int amd_powerplay_get_clock_by_type_with_latency(void *handle,
		enum amd_pp_clock_type type,
		struct pp_clock_levels_with_latency *clocks)
{
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);
	if (ret != 0)
		return ret;

	if (!clocks)
		return -EINVAL;

	mutex_lock(&pp_handle->pp_lock);
	hwmgr = ((struct pp_instance *)handle)->hwmgr;
	ret = phm_get_clock_by_type_with_latency(hwmgr, type, clocks);
	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

int amd_powerplay_get_clock_by_type_with_voltage(void *handle,
		enum amd_pp_clock_type type,
		struct pp_clock_levels_with_voltage *clocks)
{
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);
	if (ret != 0)
		return ret;

	if (!clocks)
		return -EINVAL;

	hwmgr = ((struct pp_instance *)handle)->hwmgr;

	mutex_lock(&pp_handle->pp_lock);

	ret = phm_get_clock_by_type_with_voltage(hwmgr, type, clocks);

	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

int amd_powerplay_set_watermarks_for_clocks_ranges(void *handle,
		struct pp_wm_sets_with_clock_ranges_soc15 *wm_with_clock_ranges)
{
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);
	if (ret != 0)
		return ret;

	if (!wm_with_clock_ranges)
		return -EINVAL;

	hwmgr = ((struct pp_instance *)handle)->hwmgr;

	mutex_lock(&pp_handle->pp_lock);
	ret = phm_set_watermarks_for_clocks_ranges(hwmgr,
			wm_with_clock_ranges);
	mutex_unlock(&pp_handle->pp_lock);

	return ret;
}

int amd_powerplay_display_clock_voltage_request(void *handle,
		struct pp_display_clock_request *clock)
{
	struct pp_hwmgr *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);
	if (ret != 0)
		return ret;

	if (!clock)
		return -EINVAL;

	hwmgr = ((struct pp_instance *)handle)->hwmgr;

	mutex_lock(&pp_handle->pp_lock);
	ret = phm_display_clock_voltage_request(hwmgr, clock);
	mutex_unlock(&pp_handle->pp_lock);

	return ret;
}

int amd_powerplay_get_display_mode_validation_clocks(void *handle,
		struct amd_pp_simple_clock_info *clocks)
{
	struct pp_hwmgr  *hwmgr;
	struct pp_instance *pp_handle = (struct pp_instance *)handle;
	int ret = 0;

	ret = pp_check(pp_handle);

	if (ret != 0)
		return ret;

	hwmgr = pp_handle->hwmgr;

	if (clocks == NULL)
		return -EINVAL;

	mutex_lock(&pp_handle->pp_lock);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_DynamicPatchPowerState))
		ret = phm_get_max_high_clocks(hwmgr, clocks);

	mutex_unlock(&pp_handle->pp_lock);
	return ret;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
