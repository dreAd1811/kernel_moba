<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (c) 2015, 2018-2019, The Linux Foundation. All rights reserved. */
=======
/*
 * Copyright (c) 2015, 2017-2019, The Linux Foundation. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#ifndef __QCOM_CLK_ALPHA_PLL_H__
#define __QCOM_CLK_ALPHA_PLL_H__

#include <linux/clk-provider.h>
#include "clk-regmap.h"

<<<<<<< HEAD
/* Alpha PLL types */
enum {
	CLK_ALPHA_PLL_TYPE_DEFAULT,
	CLK_ALPHA_PLL_TYPE_HUAYRA,
	CLK_ALPHA_PLL_TYPE_BRAMMO,
	CLK_ALPHA_PLL_TYPE_FABIA,
	CLK_ALPHA_PLL_TYPE_LUCID,
	CLK_ALPHA_PLL_TYPE_ZONDA,
	CLK_ALPHA_PLL_TYPE_AGERA,
	CLK_ALPHA_PLL_TYPE_MAX,
};

enum {
	PLL_OFF_MODE,
	PLL_OFF_L_VAL,
	PLL_OFF_CAL_L_VAL,
	PLL_OFF_ALPHA_VAL,
	PLL_OFF_ALPHA_VAL_U,
	PLL_OFF_USER_CTL,
	PLL_OFF_USER_CTL_U,
	PLL_OFF_USER_CTL_U1,
	PLL_OFF_CONFIG_CTL,
	PLL_OFF_CONFIG_CTL_U,
	PLL_OFF_CONFIG_CTL_U1,
	PLL_OFF_TEST_CTL,
	PLL_OFF_TEST_CTL_U,
	PLL_OFF_TEST_CTL_U1,
	PLL_OFF_STATUS,
	PLL_OFF_OPMODE,
	PLL_OFF_FRAC,
	PLL_OFF_MAX_REGS
};

extern const u8 clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_MAX][PLL_OFF_MAX_REGS];

=======
struct pll_vco_data {
	unsigned long freq;
	u8 post_div_val;
};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct pll_vco {
	unsigned long min_freq;
	unsigned long max_freq;
	u32 val;
};

<<<<<<< HEAD
/**
 * struct clk_alpha_pll - phase locked loop (PLL)
 * @offset: base address of registers
 * @vco_table: array of VCO settings
 * @regs: alpha pll register map (see @clk_alpha_pll_regs)
=======
enum pll_type {
	ALPHA_PLL,
	TRION_PLL,
	REGERA_PLL,
	FABIA_PLL,
	AGERA_PLL,
	LUCID_PLL,
};

/**
 * struct clk_alpha_pll - phase locked loop (PLL)
 * @offset: base address of registers
 * @soft_vote: soft voting variable for multiple PLL software instances
 * @soft_vote_mask: soft voting mask for multiple PLL software instances
 * @inited: flag that's set when the PLL is initialized
 * @vco_table: array of VCO settings
 * @vco_data: array of VCO data settings like post div
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @clkr: regmap clock handle
 */
struct clk_alpha_pll {
	u32 offset;
<<<<<<< HEAD
	const u8 *regs;
	struct alpha_pll_config *config;
	const struct pll_vco *vco_table;
	size_t num_vco;
#define SUPPORTS_OFFLINE_REQ	BIT(0)
#define SUPPORTS_FSM_MODE	BIT(2)
#define SUPPORTS_DYNAMIC_UPDATE	BIT(3)
	u8 flags;

	struct clk_regmap clkr;
=======
	struct alpha_pll_config *config;
	bool inited;

	u32 *soft_vote;
	u32 soft_vote_mask;
	/* Soft voting values */
#define PLL_SOFT_VOTE_PRIMARY	BIT(0)
#define PLL_SOFT_VOTE_CPU	BIT(1)
#define PLL_SOFT_VOTE_AUX	BIT(2)

	const struct pll_vco *vco_table;
	size_t num_vco;

	const struct pll_vco_data *vco_data;
	size_t num_vco_data;

#define SUPPORTS_OFFLINE_REQ	BIT(0)
#define SUPPORTS_16BIT_ALPHA	BIT(1)
#define SUPPORTS_FSM_MODE	BIT(2)
	/*
	 * Some PLLs support dynamically updating their rate without disabling
	 * the PLL first. Set this flag to enable this support.
	 */
#define SUPPORTS_DYNAMIC_UPDATE	BIT(3)
#define SUPPORTS_SLEW		BIT(4)
	/* Associated with soft_vote for multiple PLL software instances */
#define SUPPORTS_FSM_VOTE	BIT(5)
#define SUPPORTS_NO_SLEW	BIT(6)
#define SUPPORTS_NO_PLL_LATCH	BIT(7)
	u8 flags;

	struct clk_regmap clkr;
	enum pll_type type;
	unsigned long min_supported_freq;
};

enum postdiv_type {
	POSTDIV_EVEN,
	POSTDIV_ODD,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

/**
 * struct clk_alpha_pll_postdiv - phase locked loop (PLL) post-divider
 * @offset: base address of registers
<<<<<<< HEAD
 * @regs: alpha pll register map (see @clk_alpha_pll_regs)
 * @width: width of post-divider
 * @post_div_shift: shift to differentiate between odd & even post-divider
 * @post_div_table: table with PLL odd and even post-divider settings
 * @num_post_div: Number of PLL post-divider settings
 *
=======
 * @width: width of post-divider
 * @post_div_shift: shift to differentiate between odd and even post-divider
 * @post_div_table: table with PLL odd and even post-divider settings
 * @num_post_div: Number of PLL post-divider settings
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @clkr: regmap clock handle
 */
struct clk_alpha_pll_postdiv {
	u32 offset;
	u8 width;
<<<<<<< HEAD
	const u8 *regs;
	struct clk_regmap clkr;
	int post_div_shift;
	const struct clk_div_table *post_div_table;
	size_t num_post_div;
=======
	int post_div_shift;
	const struct clk_div_table *post_div_table;
	size_t num_post_div;
	struct clk_regmap clkr;
	enum pll_type type;
	enum postdiv_type postdiv;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct alpha_pll_config {
	u32 l;
<<<<<<< HEAD
	u32 cal_l;
	u32 alpha;
	u32 alpha_hi;
=======
	u32 frac;
	u32 alpha;
	u32 alpha_u;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 user_ctl_val;
	u32 user_ctl_hi_val;
	u32 user_ctl_hi1_val;
	u32 config_ctl_val;
	u32 config_ctl_hi_val;
	u32 config_ctl_hi1_val;
	u32 test_ctl_val;
<<<<<<< HEAD
	u32 test_ctl_hi_val;
=======
	u32 test_ctl_mask;
	u32 test_ctl_hi_val;
	u32 test_ctl_hi_mask;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 test_ctl_hi1_val;
	u32 main_output_mask;
	u32 aux_output_mask;
	u32 aux2_output_mask;
	u32 early_output_mask;
<<<<<<< HEAD
	u32 alpha_en_mask;
	u32 alpha_mode_mask;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 pre_div_val;
	u32 pre_div_mask;
	u32 post_div_val;
	u32 post_div_mask;
<<<<<<< HEAD
	u32 test_ctl_mask;
	u32 test_ctl_hi_mask;
	u32 vco_val;
	u32 vco_mask;
	const u32 *custom_reg_offset;
	const u32 *custom_reg_val;
	size_t num_custom_reg;
=======
	u32 vco_val;
	u32 vco_mask;
	u32 alpha_en_mask;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

extern const struct clk_ops clk_alpha_pll_ops;
extern const struct clk_ops clk_alpha_pll_hwfsm_ops;
extern const struct clk_ops clk_alpha_pll_postdiv_ops;
<<<<<<< HEAD
extern const struct clk_ops clk_alpha_pll_huayra_ops;
extern const struct clk_ops clk_alpha_pll_postdiv_ro_ops;

extern const struct clk_ops clk_alpha_pll_fabia_ops;
extern const struct clk_ops clk_alpha_pll_fixed_fabia_ops;
extern const struct clk_ops clk_alpha_pll_postdiv_fabia_ops;

=======
extern const struct clk_ops clk_trion_pll_ops;
extern const struct clk_ops clk_trion_fixed_pll_ops;
extern const struct clk_ops clk_trion_pll_postdiv_ops;
extern const struct clk_ops clk_regera_pll_ops;
extern const struct clk_ops clk_alpha_pll_slew_ops;
extern const struct clk_ops clk_pll_sleep_vote_ops;
extern const struct clk_ops clk_fabia_pll_ops;
extern const struct clk_ops clk_fabia_fixed_pll_ops;
extern const struct clk_ops clk_generic_pll_postdiv_ops;
extern const struct clk_ops clk_agera_pll_ops;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
extern const struct clk_ops clk_alpha_pll_lucid_ops;
extern const struct clk_ops clk_alpha_pll_fixed_lucid_ops;
extern const struct clk_ops clk_alpha_pll_postdiv_lucid_ops;

<<<<<<< HEAD
extern const struct clk_ops clk_alpha_pll_zonda_ops;
extern const struct clk_ops clk_alpha_pll_postdiv_zonda_ops;

extern const struct clk_ops clk_alpha_pll_agera_ops;

void clk_alpha_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
			     const struct alpha_pll_config *config);
int clk_fabia_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
void clk_lucid_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
void clk_zonda_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
int clk_agera_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
=======
int clk_alpha_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
			     const struct alpha_pll_config *config);
int clk_trion_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
int clk_regera_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
int clk_fabia_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
int clk_agera_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
int clk_lucid_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
				const struct alpha_pll_config *config);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
