<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2013-2016, 2019, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
#ifndef __A3XX_H
#define __A3XX_H

#include "a3xx_reg.h"
<<<<<<< HEAD
/**
 * struct adreno_a3xx_core - a3xx specific GPU core definitions
 */
struct adreno_a3xx_core {
	/** @base: Container for the generic &struct adreno_gpu_core */
	struct adreno_gpu_core base;
	/** pm4fw_name: Name of the PM4 microcode file */
	const char *pm4fw_name;
	/** pfpfw_name: Name of the PFP microcode file */
	const char *pfpfw_name;
	/** @vbif: List of registers and values to write for VBIF */
	const struct adreno_reglist *vbif;
	/** @vbif_count: Number of registers in @vbif */
	u32 vbif_count;
};
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define A3XX_IRQ_FLAGS \
	{ BIT(A3XX_INT_RBBM_GPU_IDLE), "RBBM_GPU_IDLE" }, \
	{ BIT(A3XX_INT_RBBM_AHB_ERROR), "RBBM_AHB_ERR" }, \
	{ BIT(A3XX_INT_RBBM_REG_TIMEOUT), "RBBM_REG_TIMEOUT" }, \
	{ BIT(A3XX_INT_RBBM_ME_MS_TIMEOUT), "RBBM_ME_MS_TIMEOUT" }, \
	{ BIT(A3XX_INT_RBBM_PFP_MS_TIMEOUT), "RBBM_PFP_MS_TIMEOUT" }, \
	{ BIT(A3XX_INT_RBBM_ATB_BUS_OVERFLOW), "RBBM_ATB_BUS_OVERFLOW" }, \
	{ BIT(A3XX_INT_VFD_ERROR), "RBBM_VFD_ERROR" }, \
	{ BIT(A3XX_INT_CP_SW_INT), "CP_SW" }, \
	{ BIT(A3XX_INT_CP_T0_PACKET_IN_IB), "CP_T0_PACKET_IN_IB" }, \
	{ BIT(A3XX_INT_CP_OPCODE_ERROR), "CP_OPCODE_ERROR" }, \
	{ BIT(A3XX_INT_CP_RESERVED_BIT_ERROR), "CP_RESERVED_BIT_ERROR" }, \
	{ BIT(A3XX_INT_CP_HW_FAULT), "CP_HW_FAULT" }, \
	{ BIT(A3XX_INT_CP_DMA), "CP_DMA" }, \
	{ BIT(A3XX_INT_CP_IB2_INT), "CP_IB2_INT" }, \
	{ BIT(A3XX_INT_CP_IB1_INT), "CP_IB1_INT" }, \
	{ BIT(A3XX_INT_CP_RB_INT), "CP_RB_INT" }, \
	{ BIT(A3XX_INT_CP_REG_PROTECT_FAULT), "CP_REG_PROTECT_FAULT" }, \
	{ BIT(A3XX_INT_CP_RB_DONE_TS), "CP_RB_DONE_TS" }, \
	{ BIT(A3XX_INT_CP_VS_DONE_TS), "CP_VS_DONE_TS" }, \
	{ BIT(A3XX_INT_CP_PS_DONE_TS), "CP_PS_DONE_TS" }, \
	{ BIT(A3XX_INT_CACHE_FLUSH_TS), "CACHE_FLUSH_TS" }, \
	{ BIT(A3XX_INT_CP_AHB_ERROR_HALT), "CP_AHB_ERROR_HALT" }, \
	{ BIT(A3XX_INT_MISC_HANG_DETECT), "MISC_HANG_DETECT" }, \
	{ BIT(A3XX_INT_UCHE_OOB_ACCESS), "UCHE_OOB_ACCESS" }

<<<<<<< HEAD
/**
 * to_a3xx_core - return the a3xx specific GPU core struct
 * @adreno_dev: An Adreno GPU device handle
 *
 * Returns:
 * A pointer to the a3xx specific GPU core struct
 */
static inline const struct adreno_a3xx_core *
to_a3xx_core(struct adreno_device *adreno_dev)
{
	const struct adreno_gpu_core *core = adreno_dev->gpucore;

	return container_of(core, struct adreno_a3xx_core, base);
}

unsigned int a3xx_irq_pending(struct adreno_device *adreno_dev);

=======
unsigned int a3xx_irq_pending(struct adreno_device *adreno_dev);

int a3xx_microcode_read(struct adreno_device *adreno_dev);
int a3xx_microcode_load(struct adreno_device *adreno_dev,
				unsigned int start_type);
int a3xx_perfcounter_enable(struct adreno_device *adreno_dev,
	unsigned int group, unsigned int counter, unsigned int countable);
uint64_t a3xx_perfcounter_read(struct adreno_device *adreno_dev,
	unsigned int group, unsigned int counter);

void a3xx_a4xx_err_callback(struct adreno_device *adreno_dev, int bit);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void a3xx_snapshot(struct adreno_device *adreno_dev,
		struct kgsl_snapshot *snapshot);
#endif /*__A3XX_H */
