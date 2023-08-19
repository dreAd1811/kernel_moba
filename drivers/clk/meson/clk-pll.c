<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright (c) 2015 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 *
<<<<<<< HEAD
 * Copyright (c) 2018 Baylibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
=======
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

/*
 * In the most basic form, a Meson PLL is composed as follows:
 *
 *                     PLL
 *      +------------------------------+
 *      |                              |
 * in -----[ /N ]---[ *M ]---[ >>OD ]----->> out
 *      |         ^        ^           |
 *      +------------------------------+
 *                |        |
 *               FREF     VCO
 *
<<<<<<< HEAD
 * out = in * (m + frac / frac_max) / (n << sum(ods))
=======
 * out = (in * M / N) >> OD
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#include <linux/clk-provider.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/io.h>
<<<<<<< HEAD
#include <linux/math64.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/slab.h>
#include <linux/string.h>

#include "clkc.h"

<<<<<<< HEAD
static inline struct meson_clk_pll_data *
meson_clk_pll_data(struct clk_regmap *clk)
{
	return (struct meson_clk_pll_data *)clk->data;
}

static unsigned long __pll_params_to_rate(unsigned long parent_rate,
					  const struct pll_rate_table *pllt,
					  u16 frac,
					  struct meson_clk_pll_data *pll)
{
	u64 rate = (u64)parent_rate * pllt->m;
	unsigned int od = pllt->od + pllt->od2 + pllt->od3;

	if (frac && MESON_PARM_APPLICABLE(&pll->frac)) {
		u64 frac_rate = (u64)parent_rate * frac;

		rate += DIV_ROUND_UP_ULL(frac_rate,
					 (1 << pll->frac.width));
	}

	return DIV_ROUND_UP_ULL(rate, pllt->n << od);
}
=======
#define MESON_PLL_RESET				BIT(29)
#define MESON_PLL_LOCK				BIT(31)

#define to_meson_clk_pll(_hw) container_of(_hw, struct meson_clk_pll, hw)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static unsigned long meson_clk_pll_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
<<<<<<< HEAD
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	struct pll_rate_table pllt;
	u16 frac;

	pllt.n = meson_parm_read(clk->map, &pll->n);
	pllt.m = meson_parm_read(clk->map, &pll->m);
	pllt.od = meson_parm_read(clk->map, &pll->od);

	pllt.od2 = MESON_PARM_APPLICABLE(&pll->od2) ?
		meson_parm_read(clk->map, &pll->od2) :
		0;

	pllt.od3 = MESON_PARM_APPLICABLE(&pll->od3) ?
		meson_parm_read(clk->map, &pll->od3) :
		0;

	frac = MESON_PARM_APPLICABLE(&pll->frac) ?
		meson_parm_read(clk->map, &pll->frac) :
		0;

	return __pll_params_to_rate(parent_rate, &pllt, frac, pll);
}

static u16 __pll_params_with_frac(unsigned long rate,
				  unsigned long parent_rate,
				  const struct pll_rate_table *pllt,
				  struct meson_clk_pll_data *pll)
{
	u16 frac_max = (1 << pll->frac.width);
	u64 val = (u64)rate * pllt->n;

	val <<= pllt->od + pllt->od2 + pllt->od3;

	if (pll->flags & CLK_MESON_PLL_ROUND_CLOSEST)
		val = DIV_ROUND_CLOSEST_ULL(val * frac_max, parent_rate);
	else
		val = div_u64(val * frac_max, parent_rate);

	val -= pllt->m * frac_max;

	return min((u16)val, (u16)(frac_max - 1));
}

static const struct pll_rate_table *
meson_clk_get_pll_settings(unsigned long rate,
			   struct meson_clk_pll_data *pll)
{
	const struct pll_rate_table *table = pll->table;
	unsigned int i = 0;

	if (!table)
		return NULL;

	/* Find the first table element exceeding rate */
	while (table[i].rate && table[i].rate <= rate)
		i++;

	if (i != 0) {
		if (MESON_PARM_APPLICABLE(&pll->frac) ||
		    !(pll->flags & CLK_MESON_PLL_ROUND_CLOSEST) ||
		    (abs(rate - table[i - 1].rate) <
		     abs(rate - table[i].rate)))
			i--;
	}

	return (struct pll_rate_table *)&table[i];
=======
	struct meson_clk_pll *pll = to_meson_clk_pll(hw);
	struct parm *p;
	unsigned long parent_rate_mhz = parent_rate / 1000000;
	unsigned long rate_mhz;
	u16 n, m, frac = 0, od, od2 = 0;
	u32 reg;

	p = &pll->n;
	reg = readl(pll->base + p->reg_off);
	n = PARM_GET(p->width, p->shift, reg);

	p = &pll->m;
	reg = readl(pll->base + p->reg_off);
	m = PARM_GET(p->width, p->shift, reg);

	p = &pll->od;
	reg = readl(pll->base + p->reg_off);
	od = PARM_GET(p->width, p->shift, reg);

	p = &pll->od2;
	if (p->width) {
		reg = readl(pll->base + p->reg_off);
		od2 = PARM_GET(p->width, p->shift, reg);
	}

	p = &pll->frac;
	if (p->width) {
		reg = readl(pll->base + p->reg_off);
		frac = PARM_GET(p->width, p->shift, reg);
		rate_mhz = (parent_rate_mhz * m + \
				(parent_rate_mhz * frac >> 12)) * 2 / n;
		rate_mhz = rate_mhz >> od >> od2;
	} else
		rate_mhz = (parent_rate_mhz * m / n) >> od >> od2;

	return rate_mhz * 1000000;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static long meson_clk_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *parent_rate)
{
<<<<<<< HEAD
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	const struct pll_rate_table *pllt =
		meson_clk_get_pll_settings(rate, pll);
	u16 frac;

	if (!pllt)
		return meson_clk_pll_recalc_rate(hw, *parent_rate);

	if (!MESON_PARM_APPLICABLE(&pll->frac)
	    || rate == pllt->rate)
		return pllt->rate;

	/*
	 * The rate provided by the setting is not an exact match, let's
	 * try to improve the result using the fractional parameter
	 */
	frac = __pll_params_with_frac(rate, *parent_rate, pllt, pll);

	return __pll_params_to_rate(*parent_rate, pllt, frac, pll);
}

static int meson_clk_pll_wait_lock(struct clk_hw *hw)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	int delay = 24000000;

	do {
		/* Is the clock locked now ? */
		if (meson_parm_read(clk->map, &pll->l))
			return 0;

		delay--;
	} while (delay > 0);

	return -ETIMEDOUT;
}

static void meson_clk_pll_init(struct clk_hw *hw)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);

	if (pll->init_count) {
		meson_parm_write(clk->map, &pll->rst, 1);
		regmap_multi_reg_write(clk->map, pll->init_regs,
				       pll->init_count);
		meson_parm_write(clk->map, &pll->rst, 0);
	}
=======
	struct meson_clk_pll *pll = to_meson_clk_pll(hw);
	const struct pll_rate_table *rate_table = pll->rate_table;
	int i;

	for (i = 0; i < pll->rate_count; i++) {
		if (rate <= rate_table[i].rate)
			return rate_table[i].rate;
	}

	/* else return the smallest value */
	return rate_table[0].rate;
}

static const struct pll_rate_table *meson_clk_get_pll_settings(struct meson_clk_pll *pll,
							       unsigned long rate)
{
	const struct pll_rate_table *rate_table = pll->rate_table;
	int i;

	for (i = 0; i < pll->rate_count; i++) {
		if (rate == rate_table[i].rate)
			return &rate_table[i];
	}
	return NULL;
}

/* Specific wait loop for GXL/GXM GP0 PLL */
static int meson_clk_pll_wait_lock_reset(struct meson_clk_pll *pll,
					 struct parm *p_n)
{
	int delay = 100;
	u32 reg;

	while (delay > 0) {
		reg = readl(pll->base + p_n->reg_off);
		writel(reg | MESON_PLL_RESET, pll->base + p_n->reg_off);
		udelay(10);
		writel(reg & ~MESON_PLL_RESET, pll->base + p_n->reg_off);

		/* This delay comes from AMLogic tree clk-gp0-gxl driver */
		mdelay(1);

		reg = readl(pll->base + p_n->reg_off);
		if (reg & MESON_PLL_LOCK)
			return 0;
		delay--;
	}
	return -ETIMEDOUT;
}

static int meson_clk_pll_wait_lock(struct meson_clk_pll *pll,
				   struct parm *p_n)
{
	int delay = 24000000;
	u32 reg;

	while (delay > 0) {
		reg = readl(pll->base + p_n->reg_off);

		if (reg & MESON_PLL_LOCK)
			return 0;
		delay--;
	}
	return -ETIMEDOUT;
}

static void meson_clk_pll_init_params(struct meson_clk_pll *pll)
{
	int i;

	for (i = 0 ; i < pll->params.params_count ; ++i)
		writel(pll->params.params_table[i].value,
		       pll->base + pll->params.params_table[i].reg_off);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int meson_clk_pll_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
<<<<<<< HEAD
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	const struct pll_rate_table *pllt;
	unsigned long old_rate;
	u16 frac = 0;
=======
	struct meson_clk_pll *pll = to_meson_clk_pll(hw);
	struct parm *p;
	const struct pll_rate_table *rate_set;
	unsigned long old_rate;
	int ret = 0;
	u32 reg;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (parent_rate == 0 || rate == 0)
		return -EINVAL;

	old_rate = rate;

<<<<<<< HEAD
	pllt = meson_clk_get_pll_settings(rate, pll);
	if (!pllt)
		return -EINVAL;

	/* Put the pll in reset to write the params */
	meson_parm_write(clk->map, &pll->rst, 1);

	meson_parm_write(clk->map, &pll->n, pllt->n);
	meson_parm_write(clk->map, &pll->m, pllt->m);
	meson_parm_write(clk->map, &pll->od, pllt->od);

	if (MESON_PARM_APPLICABLE(&pll->od2))
		meson_parm_write(clk->map, &pll->od2, pllt->od2);

	if (MESON_PARM_APPLICABLE(&pll->od3))
		meson_parm_write(clk->map, &pll->od3, pllt->od3);

	if (MESON_PARM_APPLICABLE(&pll->frac)) {
		frac = __pll_params_with_frac(rate, parent_rate, pllt, pll);
		meson_parm_write(clk->map, &pll->frac, frac);
	}

	/* make sure the reset is cleared at this point */
	meson_parm_write(clk->map, &pll->rst, 0);

	if (meson_clk_pll_wait_lock(hw)) {
		pr_warn("%s: pll did not lock, trying to restore old rate %lu\n",
			__func__, old_rate);
		/*
		 * FIXME: Do we really need/want this HACK ?
		 * It looks unsafe. what happens if the clock gets into a
		 * broken state and we can't lock back on the old_rate ? Looks
		 * like an infinite recursion is possible
		 */
		meson_clk_pll_set_rate(hw, old_rate, parent_rate);
	}

	return 0;
}

const struct clk_ops meson_clk_pll_ops = {
	.init		= meson_clk_pll_init,
=======
	rate_set = meson_clk_get_pll_settings(pll, rate);
	if (!rate_set)
		return -EINVAL;

	/* Initialize the PLL in a clean state if specified */
	if (pll->params.params_count)
		meson_clk_pll_init_params(pll);

	/* PLL reset */
	p = &pll->n;
	reg = readl(pll->base + p->reg_off);
	/* If no_init_reset is provided, avoid resetting at this point */
	if (!pll->params.no_init_reset)
		writel(reg | MESON_PLL_RESET, pll->base + p->reg_off);

	reg = PARM_SET(p->width, p->shift, reg, rate_set->n);
	writel(reg, pll->base + p->reg_off);

	p = &pll->m;
	reg = readl(pll->base + p->reg_off);
	reg = PARM_SET(p->width, p->shift, reg, rate_set->m);
	writel(reg, pll->base + p->reg_off);

	p = &pll->od;
	reg = readl(pll->base + p->reg_off);
	reg = PARM_SET(p->width, p->shift, reg, rate_set->od);
	writel(reg, pll->base + p->reg_off);

	p = &pll->od2;
	if (p->width) {
		reg = readl(pll->base + p->reg_off);
		reg = PARM_SET(p->width, p->shift, reg, rate_set->od2);
		writel(reg, pll->base + p->reg_off);
	}

	p = &pll->frac;
	if (p->width) {
		reg = readl(pll->base + p->reg_off);
		reg = PARM_SET(p->width, p->shift, reg, rate_set->frac);
		writel(reg, pll->base + p->reg_off);
	}

	p = &pll->n;
	/* If clear_reset_for_lock is provided, remove the reset bit here */
	if (pll->params.clear_reset_for_lock) {
		reg = readl(pll->base + p->reg_off);
		writel(reg & ~MESON_PLL_RESET, pll->base + p->reg_off);
	}

	/* If reset_lock_loop, use a special loop including resetting */
	if (pll->params.reset_lock_loop)
		ret = meson_clk_pll_wait_lock_reset(pll, p);
	else
		ret = meson_clk_pll_wait_lock(pll, p);
	if (ret) {
		pr_warn("%s: pll did not lock, trying to restore old rate %lu\n",
			__func__, old_rate);
		meson_clk_pll_set_rate(hw, old_rate, parent_rate);
	}

	return ret;
}

const struct clk_ops meson_clk_pll_ops = {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.recalc_rate	= meson_clk_pll_recalc_rate,
	.round_rate	= meson_clk_pll_round_rate,
	.set_rate	= meson_clk_pll_set_rate,
};

const struct clk_ops meson_clk_pll_ro_ops = {
	.recalc_rate	= meson_clk_pll_recalc_rate,
};
