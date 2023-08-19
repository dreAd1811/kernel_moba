/*
 * Copyright (C) 2016 Free Electrons
 * Copyright (C) 2016 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#include <linux/clk-provider.h>
<<<<<<< HEAD
#include <linux/regmap.h>

=======

#include "sun4i_tcon.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "sun4i_hdmi.h"

struct sun4i_ddc {
	struct clk_hw		hw;
	struct sun4i_hdmi	*hdmi;
<<<<<<< HEAD
	struct regmap_field	*reg;
	u8			pre_div;
	u8			m_offset;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static inline struct sun4i_ddc *hw_to_ddc(struct clk_hw *hw)
{
	return container_of(hw, struct sun4i_ddc, hw);
}

static unsigned long sun4i_ddc_calc_divider(unsigned long rate,
					    unsigned long parent_rate,
<<<<<<< HEAD
					    const u8 pre_div,
					    const u8 m_offset,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					    u8 *m, u8 *n)
{
	unsigned long best_rate = 0;
	u8 best_m = 0, best_n = 0, _m, _n;

<<<<<<< HEAD
	for (_m = 0; _m < 8; _m++) {
		for (_n = 0; _n < 8; _n++) {
			unsigned long tmp_rate;

			tmp_rate = (((parent_rate / pre_div) / 10) >> _n) /
				(_m + m_offset);
=======
	for (_m = 0; _m < 16; _m++) {
		for (_n = 0; _n < 8; _n++) {
			unsigned long tmp_rate;

			tmp_rate = (((parent_rate / 2) / 10) >> _n) / (_m + 1);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			if (tmp_rate > rate)
				continue;

			if (abs(rate - tmp_rate) < abs(rate - best_rate)) {
				best_rate = tmp_rate;
				best_m = _m;
				best_n = _n;
			}
		}
	}

	if (m && n) {
		*m = best_m;
		*n = best_n;
	}

	return best_rate;
}

static long sun4i_ddc_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *prate)
{
<<<<<<< HEAD
	struct sun4i_ddc *ddc = hw_to_ddc(hw);

	return sun4i_ddc_calc_divider(rate, *prate, ddc->pre_div,
				      ddc->m_offset, NULL, NULL);
=======
	return sun4i_ddc_calc_divider(rate, *prate, NULL, NULL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static unsigned long sun4i_ddc_recalc_rate(struct clk_hw *hw,
					    unsigned long parent_rate)
{
	struct sun4i_ddc *ddc = hw_to_ddc(hw);
<<<<<<< HEAD
	unsigned int reg;
	u8 m, n;

	regmap_field_read(ddc->reg, &reg);
	m = (reg >> 3) & 0xf;
	n = reg & 0x7;

	return (((parent_rate / ddc->pre_div) / 10) >> n) /
	       (m + ddc->m_offset);
=======
	u32 reg;
	u8 m, n;

	reg = readl(ddc->hdmi->base + SUN4I_HDMI_DDC_CLK_REG);
	m = (reg >> 3) & 0x7;
	n = reg & 0x7;

	return (((parent_rate / 2) / 10) >> n) / (m + 1);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int sun4i_ddc_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct sun4i_ddc *ddc = hw_to_ddc(hw);
	u8 div_m, div_n;

<<<<<<< HEAD
	sun4i_ddc_calc_divider(rate, parent_rate, ddc->pre_div,
			       ddc->m_offset, &div_m, &div_n);

	regmap_field_write(ddc->reg,
			   SUN4I_HDMI_DDC_CLK_M(div_m) |
			   SUN4I_HDMI_DDC_CLK_N(div_n));
=======
	sun4i_ddc_calc_divider(rate, parent_rate, &div_m, &div_n);

	writel(SUN4I_HDMI_DDC_CLK_M(div_m) | SUN4I_HDMI_DDC_CLK_N(div_n),
	       ddc->hdmi->base + SUN4I_HDMI_DDC_CLK_REG);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

static const struct clk_ops sun4i_ddc_ops = {
	.recalc_rate	= sun4i_ddc_recalc_rate,
	.round_rate	= sun4i_ddc_round_rate,
	.set_rate	= sun4i_ddc_set_rate,
};

int sun4i_ddc_create(struct sun4i_hdmi *hdmi, struct clk *parent)
{
	struct clk_init_data init;
	struct sun4i_ddc *ddc;
	const char *parent_name;

	parent_name = __clk_get_name(parent);
	if (!parent_name)
		return -ENODEV;

	ddc = devm_kzalloc(hdmi->dev, sizeof(*ddc), GFP_KERNEL);
	if (!ddc)
		return -ENOMEM;

<<<<<<< HEAD
	ddc->reg = devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					   hdmi->variant->ddc_clk_reg);
	if (IS_ERR(ddc->reg))
		return PTR_ERR(ddc->reg);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	init.name = "hdmi-ddc";
	init.ops = &sun4i_ddc_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	ddc->hdmi = hdmi;
	ddc->hw.init = &init;
<<<<<<< HEAD
	ddc->pre_div = hdmi->variant->ddc_clk_pre_divider;
	ddc->m_offset = hdmi->variant->ddc_clk_m_offset;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	hdmi->ddc_clk = devm_clk_register(hdmi->dev, &ddc->hw);
	if (IS_ERR(hdmi->ddc_clk))
		return PTR_ERR(hdmi->ddc_clk);

	return 0;
}
