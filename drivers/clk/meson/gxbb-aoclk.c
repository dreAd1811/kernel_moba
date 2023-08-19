<<<<<<< HEAD
// SPDX-License-Identifier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */
#include <linux/platform_device.h>
#include <linux/mfd/syscon.h>
#include "clk-regmap.h"
#include "meson-aoclk.h"
#include "gxbb-aoclk.h"

#define GXBB_AO_GATE(_name, _bit)					\
static struct clk_regmap _name##_ao = {					\
	.data = &(struct clk_regmap_gate_data) {			\
		.offset = AO_RTI_GEN_CNTL_REG0,				\
		.bit_idx = (_bit),					\
	},								\
	.hw.init = &(struct clk_init_data) {				\
		.name = #_name "_ao",					\
		.ops = &clk_regmap_gate_ops,				\
		.parent_names = (const char *[]){ "clk81" },		\
		.num_parents = 1,					\
		.flags = CLK_IGNORE_UNUSED,				\
=======
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may do so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 * The full GNU General Public License is included in this distribution
 * in the file called COPYING.
 *
 * BSD LICENSE
 *
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <linux/clk-provider.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/reset-controller.h>
#include <linux/mfd/syscon.h>
#include <linux/regmap.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <dt-bindings/clock/gxbb-aoclkc.h>
#include <dt-bindings/reset/gxbb-aoclkc.h>
#include "gxbb-aoclk.h"

static DEFINE_SPINLOCK(gxbb_aoclk_lock);

struct gxbb_aoclk_reset_controller {
	struct reset_controller_dev reset;
	unsigned int *data;
	struct regmap *regmap;
};

static int gxbb_aoclk_do_reset(struct reset_controller_dev *rcdev,
			       unsigned long id)
{
	struct gxbb_aoclk_reset_controller *reset =
		container_of(rcdev, struct gxbb_aoclk_reset_controller, reset);

	return regmap_write(reset->regmap, AO_RTI_GEN_CNTL_REG0,
			    BIT(reset->data[id]));
}

static const struct reset_control_ops gxbb_aoclk_reset_ops = {
	.reset = gxbb_aoclk_do_reset,
};

#define GXBB_AO_GATE(_name, _bit)					\
static struct aoclk_gate_regmap _name##_ao = {				\
	.bit_idx = (_bit),						\
	.lock = &gxbb_aoclk_lock,					\
	.hw.init = &(struct clk_init_data) {				\
		.name = #_name "_ao",					\
		.ops = &meson_aoclk_gate_regmap_ops,			\
		.parent_names = (const char *[]){ "clk81" },		\
		.num_parents = 1,					\
		.flags = (CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED),	\
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},								\
}

GXBB_AO_GATE(remote, 0);
GXBB_AO_GATE(i2c_master, 1);
GXBB_AO_GATE(i2c_slave, 2);
GXBB_AO_GATE(uart1, 3);
GXBB_AO_GATE(uart2, 5);
GXBB_AO_GATE(ir_blaster, 6);

static struct aoclk_cec_32k cec_32k_ao = {
<<<<<<< HEAD
=======
	.lock = &gxbb_aoclk_lock,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.hw.init = &(struct clk_init_data) {
		.name = "cec_32k_ao",
		.ops = &meson_aoclk_cec_32k_ops,
		.parent_names = (const char *[]){ "xtal" },
		.num_parents = 1,
		.flags = CLK_IGNORE_UNUSED,
	},
};

<<<<<<< HEAD
static const unsigned int gxbb_aoclk_reset[] = {
=======
static unsigned int gxbb_aoclk_reset[] = {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	[RESET_AO_REMOTE] = 16,
	[RESET_AO_I2C_MASTER] = 18,
	[RESET_AO_I2C_SLAVE] = 19,
	[RESET_AO_UART1] = 17,
	[RESET_AO_UART2] = 22,
	[RESET_AO_IR_BLASTER] = 23,
};

<<<<<<< HEAD
static struct clk_regmap *gxbb_aoclk_gate[] = {
=======
static struct aoclk_gate_regmap *gxbb_aoclk_gate[] = {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	[CLKID_AO_REMOTE] = &remote_ao,
	[CLKID_AO_I2C_MASTER] = &i2c_master_ao,
	[CLKID_AO_I2C_SLAVE] = &i2c_slave_ao,
	[CLKID_AO_UART1] = &uart1_ao,
	[CLKID_AO_UART2] = &uart2_ao,
	[CLKID_AO_IR_BLASTER] = &ir_blaster_ao,
};

<<<<<<< HEAD
static const struct clk_hw_onecell_data gxbb_aoclk_onecell_data = {
=======
static struct clk_hw_onecell_data gxbb_aoclk_onecell_data = {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.hws = {
		[CLKID_AO_REMOTE] = &remote_ao.hw,
		[CLKID_AO_I2C_MASTER] = &i2c_master_ao.hw,
		[CLKID_AO_I2C_SLAVE] = &i2c_slave_ao.hw,
		[CLKID_AO_UART1] = &uart1_ao.hw,
		[CLKID_AO_UART2] = &uart2_ao.hw,
		[CLKID_AO_IR_BLASTER] = &ir_blaster_ao.hw,
		[CLKID_AO_CEC_32K] = &cec_32k_ao.hw,
	},
<<<<<<< HEAD
	.num = NR_CLKS,
};

static int gxbb_register_cec_ao_32k(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct regmap *regmap;
	int ret;
=======
	.num = 7,
};

static int gxbb_aoclkc_probe(struct platform_device *pdev)
{
	struct gxbb_aoclk_reset_controller *rstc;
	struct device *dev = &pdev->dev;
	struct regmap *regmap;
	int ret, clkid;

	rstc = devm_kzalloc(dev, sizeof(*rstc), GFP_KERNEL);
	if (!rstc)
		return -ENOMEM;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	regmap = syscon_node_to_regmap(of_get_parent(dev->of_node));
	if (IS_ERR(regmap)) {
		dev_err(dev, "failed to get regmap\n");
<<<<<<< HEAD
		return PTR_ERR(regmap);
=======
		return -ENODEV;
	}

	/* Reset Controller */
	rstc->regmap = regmap;
	rstc->data = gxbb_aoclk_reset;
	rstc->reset.ops = &gxbb_aoclk_reset_ops;
	rstc->reset.nr_resets = ARRAY_SIZE(gxbb_aoclk_reset);
	rstc->reset.of_node = dev->of_node;
	ret = devm_reset_controller_register(dev, &rstc->reset);

	/*
	 * Populate regmap and register all clks
	 */
	for (clkid = 0; clkid < ARRAY_SIZE(gxbb_aoclk_gate); clkid++) {
		gxbb_aoclk_gate[clkid]->regmap = regmap;

		ret = devm_clk_hw_register(dev,
					gxbb_aoclk_onecell_data.hws[clkid]);
		if (ret)
			return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	/* Specific clocks */
	cec_32k_ao.regmap = regmap;
	ret = devm_clk_hw_register(dev, &cec_32k_ao.hw);
<<<<<<< HEAD
	if (ret) {
		dev_err(&pdev->dev, "clk cec_32k_ao register failed.\n");
		return ret;
	}

	return 0;
}

static const struct meson_aoclk_data gxbb_aoclkc_data = {
	.reset_reg	= AO_RTI_GEN_CNTL_REG0,
	.num_reset	= ARRAY_SIZE(gxbb_aoclk_reset),
	.reset		= gxbb_aoclk_reset,
	.num_clks	= ARRAY_SIZE(gxbb_aoclk_gate),
	.clks		= gxbb_aoclk_gate,
	.hw_data	= &gxbb_aoclk_onecell_data,
};

static int gxbb_aoclkc_probe(struct platform_device *pdev)
{
	int ret = gxbb_register_cec_ao_32k(pdev);
	if (ret)
		return ret;

	return meson_aoclkc_probe(pdev);
}

static const struct of_device_id gxbb_aoclkc_match_table[] = {
	{
		.compatible	= "amlogic,meson-gx-aoclkc",
		.data		= &gxbb_aoclkc_data,
	},
=======
	if (ret)
		return ret;

	return of_clk_add_hw_provider(dev->of_node, of_clk_hw_onecell_get,
			&gxbb_aoclk_onecell_data);
}

static const struct of_device_id gxbb_aoclkc_match_table[] = {
	{ .compatible = "amlogic,meson-gx-aoclkc" },
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	{ }
};

static struct platform_driver gxbb_aoclkc_driver = {
	.probe		= gxbb_aoclkc_probe,
	.driver		= {
		.name	= "gxbb-aoclkc",
		.of_match_table = gxbb_aoclkc_match_table,
	},
};
builtin_platform_driver(gxbb_aoclkc_driver);
