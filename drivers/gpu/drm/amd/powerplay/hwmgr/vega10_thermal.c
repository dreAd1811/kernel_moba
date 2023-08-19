/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#include "vega10_thermal.h"
#include "vega10_hwmgr.h"
<<<<<<< HEAD
#include "vega10_ppsmc.h"
#include "vega10_inc.h"
#include "soc15_common.h"
=======
#include "vega10_smumgr.h"
#include "vega10_ppsmc.h"
#include "vega10_inc.h"
#include "pp_soc15.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "pp_debug.h"

static int vega10_get_current_rpm(struct pp_hwmgr *hwmgr, uint32_t *current_rpm)
{
<<<<<<< HEAD
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentRpm);
	*current_rpm = smum_get_argument(hwmgr);
=======
	PP_ASSERT_WITH_CODE(!smum_send_msg_to_smc(hwmgr->smumgr,
				PPSMC_MSG_GetCurrentRpm),
			"Attempt to get current RPM from SMC Failed!",
			return -1);
	PP_ASSERT_WITH_CODE(!vega10_read_arg_from_smc(hwmgr->smumgr,
			current_rpm),
			"Attempt to read current RPM from SMC Failed!",
			return -1);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

int vega10_fan_ctrl_get_fan_speed_info(struct pp_hwmgr *hwmgr,
		struct phm_fan_speed_info *fan_speed_info)
{

	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return 0;

	fan_speed_info->supports_percent_read = true;
	fan_speed_info->supports_percent_write = true;
	fan_speed_info->min_percent = 0;
	fan_speed_info->max_percent = 100;

<<<<<<< HEAD
	if (PP_CAP(PHM_PlatformCaps_FanSpeedInTableIsRPM) &&
=======
	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_FanSpeedInTableIsRPM) &&
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		hwmgr->thermal_controller.fanInfo.
		ucTachometerPulsesPerRevolution) {
		fan_speed_info->supports_rpm_read = true;
		fan_speed_info->supports_rpm_write = true;
		fan_speed_info->min_rpm =
				hwmgr->thermal_controller.fanInfo.ulMinRPM;
		fan_speed_info->max_rpm =
				hwmgr->thermal_controller.fanInfo.ulMaxRPM;
	} else {
		fan_speed_info->min_rpm = 0;
		fan_speed_info->max_rpm = 0;
	}

	return 0;
}

int vega10_fan_ctrl_get_fan_speed_percent(struct pp_hwmgr *hwmgr,
		uint32_t *speed)
{
	uint32_t current_rpm;
	uint32_t percent = 0;

	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return 0;

	if (vega10_get_current_rpm(hwmgr, &current_rpm))
		return -1;

	if (hwmgr->thermal_controller.
			advanceFanControlParameters.usMaxFanRPM != 0)
		percent = current_rpm * 100 /
			hwmgr->thermal_controller.
			advanceFanControlParameters.usMaxFanRPM;

	*speed = percent > 100 ? 100 : percent;

	return 0;
}

int vega10_fan_ctrl_get_fan_speed_rpm(struct pp_hwmgr *hwmgr, uint32_t *speed)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;
	struct vega10_hwmgr *data = hwmgr->backend;
=======
	struct vega10_hwmgr *data = (struct vega10_hwmgr *)(hwmgr->backend);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	uint32_t tach_period;
	uint32_t crystal_clock_freq;
	int result = 0;

	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return -1;

<<<<<<< HEAD
	if (data->smu_features[GNLD_FAN_CONTROL].supported) {
		result = vega10_get_current_rpm(hwmgr, speed);
	} else {
		tach_period =
			REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_STATUS),
					  CG_TACH_STATUS,
					  TACH_PERIOD);
=======
	if (data->smu_features[GNLD_FAN_CONTROL].supported)
		result = vega10_get_current_rpm(hwmgr, speed);
	else {
		uint32_t reg = soc15_get_register_offset(THM_HWID, 0,
				mmCG_TACH_STATUS_BASE_IDX, mmCG_TACH_STATUS);
		tach_period = (cgs_read_register(hwmgr->device,
				reg) & CG_TACH_STATUS__TACH_PERIOD_MASK) >>
				CG_TACH_STATUS__TACH_PERIOD__SHIFT;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		if (tach_period == 0)
			return -EINVAL;

<<<<<<< HEAD
		crystal_clock_freq = amdgpu_asic_get_xclk((struct amdgpu_device *)hwmgr->adev);
=======
		crystal_clock_freq = smu7_get_xclk(hwmgr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		*speed = 60 * crystal_clock_freq * 10000 / tach_period;
	}

	return result;
}

/**
* Set Fan Speed Control to static mode,
* so that the user can decide what speed to use.
* @param    hwmgr  the address of the powerplay hardware manager.
*           mode the fan control mode, 0 default, 1 by percent, 5, by RPM
* @exception Should always succeed.
*/
int vega10_fan_ctrl_set_static_mode(struct pp_hwmgr *hwmgr, uint32_t mode)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;

	if (hwmgr->fan_ctrl_is_in_default_mode) {
		hwmgr->fan_ctrl_default_mode =
			REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, FDO_PWM_MODE);
		hwmgr->tmin =
			REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, TMIN);
		hwmgr->fan_ctrl_is_in_default_mode = false;
	}

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, TMIN, 0));
	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, FDO_PWM_MODE, mode));
=======
	uint32_t reg;

	reg = soc15_get_register_offset(THM_HWID, 0,
			mmCG_FDO_CTRL2_BASE_IDX, mmCG_FDO_CTRL2);

	if (hwmgr->fan_ctrl_is_in_default_mode) {
		hwmgr->fan_ctrl_default_mode =
				(cgs_read_register(hwmgr->device, reg) &
				CG_FDO_CTRL2__FDO_PWM_MODE_MASK) >>
				CG_FDO_CTRL2__FDO_PWM_MODE__SHIFT;
		hwmgr->tmin = (cgs_read_register(hwmgr->device, reg) &
				CG_FDO_CTRL2__TMIN_MASK) >>
				CG_FDO_CTRL2__TMIN__SHIFT;
		hwmgr->fan_ctrl_is_in_default_mode = false;
	}

	cgs_write_register(hwmgr->device, reg,
			(cgs_read_register(hwmgr->device, reg) &
			~CG_FDO_CTRL2__TMIN_MASK) |
			(0 << CG_FDO_CTRL2__TMIN__SHIFT));
	cgs_write_register(hwmgr->device, reg,
			(cgs_read_register(hwmgr->device, reg) &
			~CG_FDO_CTRL2__FDO_PWM_MODE_MASK) |
			(mode << CG_FDO_CTRL2__FDO_PWM_MODE__SHIFT));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

/**
* Reset Fan Speed Control to default mode.
* @param    hwmgr  the address of the powerplay hardware manager.
* @exception Should always succeed.
*/
int vega10_fan_ctrl_set_default_mode(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;

	if (!hwmgr->fan_ctrl_is_in_default_mode) {
		WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, FDO_PWM_MODE,
				hwmgr->fan_ctrl_default_mode));
		WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, TMIN,
				hwmgr->tmin << CG_FDO_CTRL2__TMIN__SHIFT));
=======
	uint32_t reg;

	reg = soc15_get_register_offset(THM_HWID, 0,
			mmCG_FDO_CTRL2_BASE_IDX, mmCG_FDO_CTRL2);

	if (!hwmgr->fan_ctrl_is_in_default_mode) {
		cgs_write_register(hwmgr->device, reg,
				(cgs_read_register(hwmgr->device, reg) &
				~CG_FDO_CTRL2__FDO_PWM_MODE_MASK) |
				(hwmgr->fan_ctrl_default_mode <<
				CG_FDO_CTRL2__FDO_PWM_MODE__SHIFT));
		cgs_write_register(hwmgr->device, reg,
				(cgs_read_register(hwmgr->device, reg) &
				~CG_FDO_CTRL2__TMIN_MASK) |
				(hwmgr->tmin << CG_FDO_CTRL2__TMIN__SHIFT));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		hwmgr->fan_ctrl_is_in_default_mode = true;
	}

	return 0;
}

/**
 * @fn vega10_enable_fan_control_feature
 * @brief Enables the SMC Fan Control Feature.
 *
 * @param    hwmgr - the address of the powerplay hardware manager.
 * @return   0 on success. -1 otherwise.
 */
static int vega10_enable_fan_control_feature(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	struct vega10_hwmgr *data = hwmgr->backend;

	if (data->smu_features[GNLD_FAN_CONTROL].supported) {
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(
				hwmgr, true,
=======
	struct vega10_hwmgr *data = (struct vega10_hwmgr *)(hwmgr->backend);

	if (data->smu_features[GNLD_FAN_CONTROL].supported) {
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(
				hwmgr->smumgr, true,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				data->smu_features[GNLD_FAN_CONTROL].
				smu_feature_bitmap),
				"Attempt to Enable FAN CONTROL feature Failed!",
				return -1);
		data->smu_features[GNLD_FAN_CONTROL].enabled = true;
	}

	return 0;
}

static int vega10_disable_fan_control_feature(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	struct vega10_hwmgr *data = hwmgr->backend;

	if (data->smu_features[GNLD_FAN_CONTROL].supported) {
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(
				hwmgr, false,
=======
	struct vega10_hwmgr *data = (struct vega10_hwmgr *)(hwmgr->backend);

	if (data->smu_features[GNLD_FAN_CONTROL].supported) {
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(
				hwmgr->smumgr, false,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				data->smu_features[GNLD_FAN_CONTROL].
				smu_feature_bitmap),
				"Attempt to Enable FAN CONTROL feature Failed!",
				return -1);
		data->smu_features[GNLD_FAN_CONTROL].enabled = false;
	}

	return 0;
}

int vega10_fan_ctrl_start_smc_fan_control(struct pp_hwmgr *hwmgr)
{
	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return -1;

	PP_ASSERT_WITH_CODE(!vega10_enable_fan_control_feature(hwmgr),
			"Attempt to Enable SMC FAN CONTROL Feature Failed!",
			return -1);

	return 0;
}


int vega10_fan_ctrl_stop_smc_fan_control(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	struct vega10_hwmgr *data = hwmgr->backend;
=======
	struct vega10_hwmgr *data = (struct vega10_hwmgr *)(hwmgr->backend);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return -1;

	if (data->smu_features[GNLD_FAN_CONTROL].supported) {
		PP_ASSERT_WITH_CODE(!vega10_disable_fan_control_feature(hwmgr),
				"Attempt to Disable SMC FAN CONTROL Feature Failed!",
				return -1);
	}
	return 0;
}

/**
* Set Fan Speed in percent.
* @param    hwmgr  the address of the powerplay hardware manager.
* @param    speed is the percentage value (0% - 100%) to be set.
* @exception Fails is the 100% setting appears to be 0.
*/
int vega10_fan_ctrl_set_fan_speed_percent(struct pp_hwmgr *hwmgr,
		uint32_t speed)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t duty100;
	uint32_t duty;
	uint64_t tmp64;
=======
	uint32_t duty100;
	uint32_t duty;
	uint64_t tmp64;
	uint32_t reg;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return 0;

	if (speed > 100)
		speed = 100;

<<<<<<< HEAD
	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
		vega10_fan_ctrl_stop_smc_fan_control(hwmgr);

	duty100 = REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL1),
				    CG_FDO_CTRL1, FMAX_DUTY100);
=======
	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_MicrocodeFanControl))
		vega10_fan_ctrl_stop_smc_fan_control(hwmgr);

	reg = soc15_get_register_offset(THM_HWID, 0,
			mmCG_FDO_CTRL1_BASE_IDX, mmCG_FDO_CTRL1);

	duty100 = (cgs_read_register(hwmgr->device, reg) &
			CG_FDO_CTRL1__FMAX_DUTY100_MASK) >>
			CG_FDO_CTRL1__FMAX_DUTY100__SHIFT;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (duty100 == 0)
		return -EINVAL;

	tmp64 = (uint64_t)speed * duty100;
	do_div(tmp64, 100);
	duty = (uint32_t)tmp64;

<<<<<<< HEAD
	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL0,
		REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL0),
			CG_FDO_CTRL0, FDO_STATIC_DUTY, duty));
=======
	reg = soc15_get_register_offset(THM_HWID, 0,
			mmCG_FDO_CTRL0_BASE_IDX, mmCG_FDO_CTRL0);
	cgs_write_register(hwmgr->device, reg,
			(cgs_read_register(hwmgr->device, reg) &
			~CG_FDO_CTRL0__FDO_STATIC_DUTY_MASK) |
			(duty << CG_FDO_CTRL0__FDO_STATIC_DUTY__SHIFT));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return vega10_fan_ctrl_set_static_mode(hwmgr, FDO_PWM_MODE_STATIC);
}

/**
* Reset Fan Speed to default.
* @param    hwmgr  the address of the powerplay hardware manager.
* @exception Always succeeds.
*/
int vega10_fan_ctrl_reset_fan_speed_to_default(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return 0;

	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
		return vega10_fan_ctrl_start_smc_fan_control(hwmgr);
	else
		return vega10_fan_ctrl_set_default_mode(hwmgr);
=======
	int result;

	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return 0;

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_MicrocodeFanControl)) {
		result = vega10_fan_ctrl_start_smc_fan_control(hwmgr);
	} else
		result = vega10_fan_ctrl_set_default_mode(hwmgr);

	return result;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
* Set Fan Speed in RPM.
* @param    hwmgr  the address of the powerplay hardware manager.
* @param    speed is the percentage value (min - max) to be set.
* @exception Fails is the speed not lie between min and max.
*/
int vega10_fan_ctrl_set_fan_speed_rpm(struct pp_hwmgr *hwmgr, uint32_t speed)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t tach_period;
	uint32_t crystal_clock_freq;
	int result = 0;

	if (hwmgr->thermal_controller.fanInfo.bNoFan ||
	    (speed < hwmgr->thermal_controller.fanInfo.ulMinRPM) ||
	    (speed > hwmgr->thermal_controller.fanInfo.ulMaxRPM))
		return -1;

	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
		result = vega10_fan_ctrl_stop_smc_fan_control(hwmgr);

	if (!result) {
		crystal_clock_freq = amdgpu_asic_get_xclk((struct amdgpu_device *)hwmgr->adev);
		tach_period = 60 * crystal_clock_freq * 10000 / (8 * speed);
		WREG32_SOC15(THM, 0, mmCG_TACH_STATUS,
				REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_STATUS),
					CG_TACH_STATUS, TACH_PERIOD,
					tach_period));
=======
	uint32_t tach_period;
	uint32_t crystal_clock_freq;
	int result = 0;
	uint32_t reg;

	if (hwmgr->thermal_controller.fanInfo.bNoFan ||
			(speed < hwmgr->thermal_controller.fanInfo.ulMinRPM) ||
			(speed > hwmgr->thermal_controller.fanInfo.ulMaxRPM))
		return -1;

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_MicrocodeFanControl))
		result = vega10_fan_ctrl_stop_smc_fan_control(hwmgr);

	if (!result) {
		crystal_clock_freq = smu7_get_xclk(hwmgr);
		tach_period = 60 * crystal_clock_freq * 10000 / (8 * speed);
		reg = soc15_get_register_offset(THM_HWID, 0,
				mmCG_TACH_STATUS_BASE_IDX, mmCG_TACH_STATUS);
		cgs_write_register(hwmgr->device, reg,
				(cgs_read_register(hwmgr->device, reg) &
				~CG_TACH_STATUS__TACH_PERIOD_MASK) |
				(tach_period << CG_TACH_STATUS__TACH_PERIOD__SHIFT));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
	return vega10_fan_ctrl_set_static_mode(hwmgr, FDO_PWM_MODE_STATIC_RPM);
}

/**
* Reads the remote temperature from the SIslands thermal controller.
*
* @param    hwmgr The address of the hardware manager.
*/
int vega10_thermal_get_temperature(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;
	int temp;

	temp = RREG32_SOC15(THM, 0, mmCG_MULT_THERMAL_STATUS);

	temp = (temp & CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK) >>
			CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT;
=======
	int temp;
	uint32_t reg;

	reg = soc15_get_register_offset(THM_HWID, 0,
			mmCG_TACH_STATUS_BASE_IDX,  mmCG_MULT_THERMAL_STATUS);

	temp = cgs_read_register(hwmgr->device, reg);

	temp = (temp & CG_MULT_THERMAL_STATUS__ASIC_MAX_TEMP_MASK) >>
			CG_MULT_THERMAL_STATUS__ASIC_MAX_TEMP__SHIFT;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	temp = temp & 0x1ff;

	temp *= PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	return temp;
}

/**
* Set the requested temperature range for high and low alert signals
*
* @param    hwmgr The address of the hardware manager.
* @param    range Temperature range to be programmed for
*           high and low alert signals
* @exception PP_Result_BadInput if the input data is not valid.
*/
static int vega10_thermal_set_temperature_range(struct pp_hwmgr *hwmgr,
		struct PP_TemperatureRange *range)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;
	int low = VEGA10_THERMAL_MINIMUM_ALERT_TEMP *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	int high = VEGA10_THERMAL_MAXIMUM_ALERT_TEMP *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	uint32_t val;
=======
	uint32_t low = VEGA10_THERMAL_MINIMUM_ALERT_TEMP *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	uint32_t high = VEGA10_THERMAL_MAXIMUM_ALERT_TEMP *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	uint32_t val, reg;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (low < range->min)
		low = range->min;
	if (high > range->max)
		high = range->max;

	if (low > high)
		return -EINVAL;

<<<<<<< HEAD
	val = RREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL);

	val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, MAX_IH_CREDIT, 5);
	val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, THERM_IH_HW_ENA, 1);
	val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, DIG_THERM_INTH, (high / PP_TEMPERATURE_UNITS_PER_CENTIGRADES));
	val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, DIG_THERM_INTL, (low / PP_TEMPERATURE_UNITS_PER_CENTIGRADES));
	val &= (~THM_THERMAL_INT_CTRL__THERM_TRIGGER_MASK_MASK) &
			(~THM_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK) &
			(~THM_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK);

	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL, val);
=======
	reg = soc15_get_register_offset(THM_HWID, 0,
			mmTHM_THERMAL_INT_CTRL_BASE_IDX, mmTHM_THERMAL_INT_CTRL);

	val = cgs_read_register(hwmgr->device, reg);

	val &= (~THM_THERMAL_INT_CTRL__MAX_IH_CREDIT_MASK);
	val |=  (5 << THM_THERMAL_INT_CTRL__MAX_IH_CREDIT__SHIFT);

	val &= (~THM_THERMAL_INT_CTRL__THERM_IH_HW_ENA_MASK);
	val |= (1 << THM_THERMAL_INT_CTRL__THERM_IH_HW_ENA__SHIFT);

	val &= (~THM_THERMAL_INT_CTRL__DIG_THERM_INTH_MASK);
	val |= ((high / PP_TEMPERATURE_UNITS_PER_CENTIGRADES)
			<< THM_THERMAL_INT_CTRL__DIG_THERM_INTH__SHIFT);

	val &= (~THM_THERMAL_INT_CTRL__DIG_THERM_INTL_MASK);
	val |= ((low / PP_TEMPERATURE_UNITS_PER_CENTIGRADES)
			<< THM_THERMAL_INT_CTRL__DIG_THERM_INTL__SHIFT);

	val = val & (~THM_THERMAL_INT_CTRL__THERM_TRIGGER_MASK_MASK);

	cgs_write_register(hwmgr->device, reg, val);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

/**
* Programs thermal controller one-time setting registers
*
* @param    hwmgr The address of the hardware manager.
*/
static int vega10_thermal_initialize(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;

	if (hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution) {
		WREG32_SOC15(THM, 0, mmCG_TACH_CTRL,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_CTRL),
				CG_TACH_CTRL, EDGE_PER_REV,
				hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution - 1));
	}

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
		REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
			CG_FDO_CTRL2, TACH_PWM_RESP_RATE, 0x28));
=======
	uint32_t reg;

	if (hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution) {
		reg = soc15_get_register_offset(THM_HWID, 0,
				mmCG_TACH_CTRL_BASE_IDX, mmCG_TACH_CTRL);
		cgs_write_register(hwmgr->device, reg,
				(cgs_read_register(hwmgr->device, reg) &
				~CG_TACH_CTRL__EDGE_PER_REV_MASK) |
				((hwmgr->thermal_controller.fanInfo.
				ucTachometerPulsesPerRevolution - 1) <<
				CG_TACH_CTRL__EDGE_PER_REV__SHIFT));
	}

	reg = soc15_get_register_offset(THM_HWID, 0,
			mmCG_FDO_CTRL2_BASE_IDX, mmCG_FDO_CTRL2);
	cgs_write_register(hwmgr->device, reg,
			(cgs_read_register(hwmgr->device, reg) &
			~CG_FDO_CTRL2__TACH_PWM_RESP_RATE_MASK) |
			(0x28 << CG_FDO_CTRL2__TACH_PWM_RESP_RATE__SHIFT));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

/**
* Enable thermal alerts on the RV770 thermal controller.
*
* @param    hwmgr The address of the hardware manager.
*/
static int vega10_thermal_enable_alert(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;
	struct vega10_hwmgr *data = hwmgr->backend;
	uint32_t val = 0;
=======
	struct vega10_hwmgr *data = (struct vega10_hwmgr *)(hwmgr->backend);
	uint32_t val = 0;
	uint32_t reg;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (data->smu_features[GNLD_FW_CTF].supported) {
		if (data->smu_features[GNLD_FW_CTF].enabled)
			printk("[Thermal_EnableAlert] FW CTF Already Enabled!\n");

<<<<<<< HEAD
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
=======
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr->smumgr,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				true,
				data->smu_features[GNLD_FW_CTF].smu_feature_bitmap),
				"Attempt to Enable FW CTF feature Failed!",
				return -1);
		data->smu_features[GNLD_FW_CTF].enabled = true;
	}

	val |= (1 << THM_THERMAL_INT_ENA__THERM_INTH_CLR__SHIFT);
	val |= (1 << THM_THERMAL_INT_ENA__THERM_INTL_CLR__SHIFT);
	val |= (1 << THM_THERMAL_INT_ENA__THERM_TRIGGER_CLR__SHIFT);

<<<<<<< HEAD
	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, val);
=======
	reg = soc15_get_register_offset(THM_HWID, 0, mmTHM_THERMAL_INT_ENA_BASE_IDX, mmTHM_THERMAL_INT_ENA);
	cgs_write_register(hwmgr->device, reg, val);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

/**
* Disable thermal alerts on the RV770 thermal controller.
* @param    hwmgr The address of the hardware manager.
*/
int vega10_thermal_disable_alert(struct pp_hwmgr *hwmgr)
{
<<<<<<< HEAD
	struct amdgpu_device *adev = hwmgr->adev;
	struct vega10_hwmgr *data = hwmgr->backend;
=======
	struct vega10_hwmgr *data = (struct vega10_hwmgr *)(hwmgr->backend);
	uint32_t reg;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (data->smu_features[GNLD_FW_CTF].supported) {
		if (!data->smu_features[GNLD_FW_CTF].enabled)
			printk("[Thermal_EnableAlert] FW CTF Already disabled!\n");


<<<<<<< HEAD
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
=======
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr->smumgr,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			false,
			data->smu_features[GNLD_FW_CTF].smu_feature_bitmap),
			"Attempt to disable FW CTF feature Failed!",
			return -1);
		data->smu_features[GNLD_FW_CTF].enabled = false;
	}

<<<<<<< HEAD
	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, 0);
=======
	reg = soc15_get_register_offset(THM_HWID, 0, mmTHM_THERMAL_INT_ENA_BASE_IDX, mmTHM_THERMAL_INT_ENA);
	cgs_write_register(hwmgr->device, reg, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

/**
* Uninitialize the thermal controller.
* Currently just disables alerts.
* @param    hwmgr The address of the hardware manager.
*/
int vega10_thermal_stop_thermal_controller(struct pp_hwmgr *hwmgr)
{
	int result = vega10_thermal_disable_alert(hwmgr);

	if (!hwmgr->thermal_controller.fanInfo.bNoFan)
		vega10_fan_ctrl_set_default_mode(hwmgr);

	return result;
}

/**
* Set up the fan table to control the fan using the SMC.
* @param    hwmgr  the address of the powerplay hardware manager.
* @param    pInput the pointer to input data
* @param    pOutput the pointer to output data
* @param    pStorage the pointer to temporary storage
* @param    Result the last failure code
* @return   result from set temperature range routine
*/
<<<<<<< HEAD
int vega10_thermal_setup_fan_table(struct pp_hwmgr *hwmgr)
{
	int ret;
	struct vega10_hwmgr *data = hwmgr->backend;
=======
int tf_vega10_thermal_setup_fan_table(struct pp_hwmgr *hwmgr,
		void *input, void *output, void *storage, int result)
{
	int ret;
	struct vega10_hwmgr *data = (struct vega10_hwmgr *)(hwmgr->backend);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	PPTable_t *table = &(data->smc_state_table.pp_table);

	if (!data->smu_features[GNLD_FAN_CONTROL].supported)
		return 0;

	table->FanMaximumRpm = (uint16_t)hwmgr->thermal_controller.
			advanceFanControlParameters.usMaxFanRPM;
	table->FanThrottlingRpm = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanRPMMaxLimit;
	table->FanAcousticLimitRpm = (uint16_t)(hwmgr->thermal_controller.
			advanceFanControlParameters.ulMinFanSCLKAcousticLimit);
	table->FanTargetTemperature = hwmgr->thermal_controller.
			advanceFanControlParameters.usTMax;

<<<<<<< HEAD
	smum_send_msg_to_smc_with_parameter(hwmgr,
=======
	smum_send_msg_to_smc_with_parameter(hwmgr->smumgr,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				PPSMC_MSG_SetFanTemperatureTarget,
				(uint32_t)table->FanTargetTemperature);

	table->FanPwmMin = hwmgr->thermal_controller.
			advanceFanControlParameters.usPWMMin * 255 / 100;
	table->FanTargetGfxclk = (uint16_t)(hwmgr->thermal_controller.
			advanceFanControlParameters.ulTargetGfxClk);
	table->FanGainEdge = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainEdge;
	table->FanGainHotspot = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainHotspot;
	table->FanGainLiquid = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainLiquid;
	table->FanGainVrVddc = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainVrVddc;
	table->FanGainVrMvdd = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainVrMvdd;
	table->FanGainPlx = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainPlx;
	table->FanGainHbm = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainHbm;
	table->FanZeroRpmEnable = hwmgr->thermal_controller.
			advanceFanControlParameters.ucEnableZeroRPM;
	table->FanStopTemp = hwmgr->thermal_controller.
			advanceFanControlParameters.usZeroRPMStopTemperature;
	table->FanStartTemp = hwmgr->thermal_controller.
			advanceFanControlParameters.usZeroRPMStartTemperature;

<<<<<<< HEAD
	ret = smum_smc_table_manager(hwmgr,
				(uint8_t *)(&(data->smc_state_table.pp_table)),
				PPTABLE, false);
=======
	ret = vega10_copy_table_to_smc(hwmgr->smumgr,
			(uint8_t *)(&(data->smc_state_table.pp_table)), PPTABLE);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret)
		pr_info("Failed to update Fan Control Table in PPTable!");

	return ret;
}

/**
* Start the fan control on the SMC.
* @param    hwmgr  the address of the powerplay hardware manager.
* @param    pInput the pointer to input data
* @param    pOutput the pointer to output data
* @param    pStorage the pointer to temporary storage
* @param    Result the last failure code
* @return   result from set temperature range routine
*/
<<<<<<< HEAD
int vega10_thermal_start_smc_fan_control(struct pp_hwmgr *hwmgr)
=======
int tf_vega10_thermal_start_smc_fan_control(struct pp_hwmgr *hwmgr,
		void *input, void *output, void *storage, int result)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
/* If the fantable setup has failed we could have disabled
 * PHM_PlatformCaps_MicrocodeFanControl even after
 * this function was included in the table.
 * Make sure that we still think controlling the fan is OK.
*/
<<<<<<< HEAD
	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
		vega10_fan_ctrl_start_smc_fan_control(hwmgr);
=======
	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_MicrocodeFanControl)) {
		vega10_fan_ctrl_start_smc_fan_control(hwmgr);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

<<<<<<< HEAD

int vega10_start_thermal_controller(struct pp_hwmgr *hwmgr,
				struct PP_TemperatureRange *range)
{
	int ret = 0;
=======
/**
* Set temperature range for high and low alerts
* @param    hwmgr  the address of the powerplay hardware manager.
* @param    pInput the pointer to input data
* @param    pOutput the pointer to output data
* @param    pStorage the pointer to temporary storage
* @param    Result the last failure code
* @return   result from set temperature range routine
*/
int tf_vega10_thermal_set_temperature_range(struct pp_hwmgr *hwmgr,
		void *input, void *output, void *storage, int result)
{
	struct PP_TemperatureRange *range = (struct PP_TemperatureRange *)input;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (range == NULL)
		return -EINVAL;

<<<<<<< HEAD
	vega10_thermal_initialize(hwmgr);
	ret = vega10_thermal_set_temperature_range(hwmgr, range);
	if (ret)
		return -EINVAL;

	vega10_thermal_enable_alert(hwmgr);
=======
	return vega10_thermal_set_temperature_range(hwmgr, range);
}

/**
* Programs one-time setting registers
* @param    hwmgr  the address of the powerplay hardware manager.
* @param    pInput the pointer to input data
* @param    pOutput the pointer to output data
* @param    pStorage the pointer to temporary storage
* @param    Result the last failure code
* @return   result from initialize thermal controller routine
*/
int tf_vega10_thermal_initialize(struct pp_hwmgr *hwmgr,
		void *input, void *output, void *storage, int result)
{
	return vega10_thermal_initialize(hwmgr);
}

/**
* Enable high and low alerts
* @param    hwmgr  the address of the powerplay hardware manager.
* @param    pInput the pointer to input data
* @param    pOutput the pointer to output data
* @param    pStorage the pointer to temporary storage
* @param    Result the last failure code
* @return   result from enable alert routine
*/
int tf_vega10_thermal_enable_alert(struct pp_hwmgr *hwmgr,
		void *input, void *output, void *storage, int result)
{
	return vega10_thermal_enable_alert(hwmgr);
}

/**
* Disable high and low alerts
* @param    hwmgr  the address of the powerplay hardware manager.
* @param    pInput the pointer to input data
* @param    pOutput the pointer to output data
* @param    pStorage the pointer to temporary storage
* @param    Result the last failure code
* @return   result from disable alert routine
*/
static int tf_vega10_thermal_disable_alert(struct pp_hwmgr *hwmgr,
		void *input, void *output, void *storage, int result)
{
	return vega10_thermal_disable_alert(hwmgr);
}

static struct phm_master_table_item
vega10_thermal_start_thermal_controller_master_list[] = {
	{ .tableFunction = tf_vega10_thermal_initialize },
	{ .tableFunction = tf_vega10_thermal_set_temperature_range },
	{ .tableFunction = tf_vega10_thermal_enable_alert },
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/* We should restrict performance levels to low before we halt the SMC.
 * On the other hand we are still in boot state when we do this
 * so it would be pointless.
 * If this assumption changes we have to revisit this table.
 */
<<<<<<< HEAD
	ret = vega10_thermal_setup_fan_table(hwmgr);
	if (ret)
		return -EINVAL;

	vega10_thermal_start_smc_fan_control(hwmgr);

	return 0;
};



=======
	{ .tableFunction = tf_vega10_thermal_setup_fan_table },
	{ .tableFunction = tf_vega10_thermal_start_smc_fan_control },
	{ }
};

static struct phm_master_table_header
vega10_thermal_start_thermal_controller_master = {
	0,
	PHM_MasterTableFlag_None,
	vega10_thermal_start_thermal_controller_master_list
};

static struct phm_master_table_item
vega10_thermal_set_temperature_range_master_list[] = {
	{ .tableFunction = tf_vega10_thermal_disable_alert },
	{ .tableFunction = tf_vega10_thermal_set_temperature_range },
	{ .tableFunction = tf_vega10_thermal_enable_alert },
	{ }
};

struct phm_master_table_header
vega10_thermal_set_temperature_range_master = {
	0,
	PHM_MasterTableFlag_None,
	vega10_thermal_set_temperature_range_master_list
};
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

int vega10_thermal_ctrl_uninitialize_thermal_controller(struct pp_hwmgr *hwmgr)
{
	if (!hwmgr->thermal_controller.fanInfo.bNoFan) {
		vega10_fan_ctrl_set_default_mode(hwmgr);
		vega10_fan_ctrl_stop_smc_fan_control(hwmgr);
	}
	return 0;
}
<<<<<<< HEAD
=======

/**
* Initializes the thermal controller related functions
* in the Hardware Manager structure.
* @param    hwmgr The address of the hardware manager.
* @exception Any error code from the low-level communication.
*/
int pp_vega10_thermal_initialize(struct pp_hwmgr *hwmgr)
{
	int result;

	result = phm_construct_table(hwmgr,
			&vega10_thermal_set_temperature_range_master,
			&(hwmgr->set_temperature_range));

	if (!result) {
		result = phm_construct_table(hwmgr,
				&vega10_thermal_start_thermal_controller_master,
				&(hwmgr->start_thermal_controller));
		if (result)
			phm_destroy_table(hwmgr,
					&(hwmgr->set_temperature_range));
	}

	if (!result)
		hwmgr->fan_ctrl_is_in_default_mode = true;
	return result;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
