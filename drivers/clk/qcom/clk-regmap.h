<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (c) 2014, 2017-2018, The Linux Foundation. All rights reserved. */
=======
/*
 * Copyright (c) 2014, 2017, The Linux Foundation. All rights reserved.
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

#ifndef __QCOM_CLK_REGMAP_H__
#define __QCOM_CLK_REGMAP_H__

#include <linux/clk-provider.h>
#include <linux/debugfs.h>

struct regmap;

/**
 * struct clk_regmap - regmap supporting clock
 * @hw:		handle between common and hardware-specific interfaces
<<<<<<< HEAD
 * @dependent_hw: dependent clocks clock hw
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @regmap:	regmap to use for regmap helpers and/or by providers
 * @enable_reg: register when using regmap enable/disable ops
 * @enable_mask: mask when using regmap enable/disable ops
 * @enable_is_inverted: flag to indicate set enable_mask bits to disable
 *                      when using clock_enable_regmap and friends APIs.
 */
struct clk_regmap {
	struct clk_hw hw;
<<<<<<< HEAD
	struct clk_hw *dependent_hw;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct regmap *regmap;
	unsigned int enable_reg;
	unsigned int enable_mask;
	bool enable_is_inverted;
};
#define to_clk_regmap(_hw) container_of(_hw, struct clk_regmap, hw)

int clk_is_enabled_regmap(struct clk_hw *hw);
int clk_enable_regmap(struct clk_hw *hw);
void clk_disable_regmap(struct clk_hw *hw);
int devm_clk_register_regmap(struct device *dev, struct clk_regmap *rclk);

struct clk_register_data {
	char *name;
	u32 offset;
};

#endif
