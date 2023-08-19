/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#include <linux/clk-provider.h>

#include "ccu_frac.h"
#include "ccu_gate.h"
#include "ccu_nm.h"

struct _ccu_nm {
	unsigned long	n, min_n, max_n;
	unsigned long	m, min_m, max_m;
};

<<<<<<< HEAD
static unsigned long ccu_nm_calc_rate(unsigned long parent,
				      unsigned long n, unsigned long m)
{
	u64 rate = parent;

	rate *= n;
	do_div(rate, m);

	return rate;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static void ccu_nm_find_best(unsigned long parent, unsigned long rate,
			     struct _ccu_nm *nm)
{
	unsigned long best_rate = 0;
	unsigned long best_n = 0, best_m = 0;
	unsigned long _n, _m;

	for (_n = nm->min_n; _n <= nm->max_n; _n++) {
		for (_m = nm->min_m; _m <= nm->max_m; _m++) {
<<<<<<< HEAD
			unsigned long tmp_rate = ccu_nm_calc_rate(parent,
								  _n, _m);
=======
			unsigned long tmp_rate = parent * _n  / _m;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			if (tmp_rate > rate)
				continue;

			if ((rate - tmp_rate) < (rate - best_rate)) {
				best_rate = tmp_rate;
				best_n = _n;
				best_m = _m;
			}
		}
	}

	nm->n = best_n;
	nm->m = best_m;
}

static void ccu_nm_disable(struct clk_hw *hw)
{
	struct ccu_nm *nm = hw_to_ccu_nm(hw);

	return ccu_gate_helper_disable(&nm->common, nm->enable);
}

static int ccu_nm_enable(struct clk_hw *hw)
{
	struct ccu_nm *nm = hw_to_ccu_nm(hw);

	return ccu_gate_helper_enable(&nm->common, nm->enable);
}

static int ccu_nm_is_enabled(struct clk_hw *hw)
{
	struct ccu_nm *nm = hw_to_ccu_nm(hw);

	return ccu_gate_helper_is_enabled(&nm->common, nm->enable);
}

static unsigned long ccu_nm_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct ccu_nm *nm = hw_to_ccu_nm(hw);
<<<<<<< HEAD
	unsigned long rate;
	unsigned long n, m;
	u32 reg;

	if (ccu_frac_helper_is_enabled(&nm->common, &nm->frac)) {
		rate = ccu_frac_helper_read_rate(&nm->common, &nm->frac);

		if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_div;

		return rate;
	}
=======
	unsigned long n, m;
	u32 reg;

	if (ccu_frac_helper_is_enabled(&nm->common, &nm->frac))
		return ccu_frac_helper_read_rate(&nm->common, &nm->frac);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	reg = readl(nm->common.base + nm->common.reg);

	n = reg >> nm->n.shift;
	n &= (1 << nm->n.width) - 1;
	n += nm->n.offset;
	if (!n)
		n++;

	m = reg >> nm->m.shift;
	m &= (1 << nm->m.width) - 1;
	m += nm->m.offset;
	if (!m)
		m++;

<<<<<<< HEAD
	if (ccu_sdm_helper_is_enabled(&nm->common, &nm->sdm))
		rate = ccu_sdm_helper_read_rate(&nm->common, &nm->sdm, m, n);
	else
		rate = ccu_nm_calc_rate(parent_rate, n, m);

	if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nm->fixed_post_div;

	return rate;
=======
	return parent_rate * n / m;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static long ccu_nm_round_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long *parent_rate)
{
	struct ccu_nm *nm = hw_to_ccu_nm(hw);
	struct _ccu_nm _nm;

<<<<<<< HEAD
	if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nm->fixed_post_div;

	if (rate < nm->min_rate) {
		rate = nm->min_rate;
		if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_div;
		return rate;
	}

	if (ccu_frac_helper_has_rate(&nm->common, &nm->frac, rate)) {
		if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_div;
		return rate;
	}

	if (ccu_sdm_helper_has_rate(&nm->common, &nm->sdm, rate)) {
		if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_div;
		return rate;
	}
=======
	if (ccu_frac_helper_has_rate(&nm->common, &nm->frac, rate))
		return rate;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	_nm.min_n = nm->n.min ?: 1;
	_nm.max_n = nm->n.max ?: 1 << nm->n.width;
	_nm.min_m = 1;
	_nm.max_m = nm->m.max ?: 1 << nm->m.width;

	ccu_nm_find_best(*parent_rate, rate, &_nm);
<<<<<<< HEAD
	rate = ccu_nm_calc_rate(*parent_rate, _nm.n, _nm.m);

	if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nm->fixed_post_div;

	return rate;
=======

	return *parent_rate * _nm.n / _nm.m;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int ccu_nm_set_rate(struct clk_hw *hw, unsigned long rate,
			   unsigned long parent_rate)
{
	struct ccu_nm *nm = hw_to_ccu_nm(hw);
	struct _ccu_nm _nm;
	unsigned long flags;
	u32 reg;

<<<<<<< HEAD
	/* Adjust target rate according to post-dividers */
	if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate * nm->fixed_post_div;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ccu_frac_helper_has_rate(&nm->common, &nm->frac, rate)) {
		spin_lock_irqsave(nm->common.lock, flags);

		/* most SoCs require M to be 0 if fractional mode is used */
		reg = readl(nm->common.base + nm->common.reg);
		reg &= ~GENMASK(nm->m.width + nm->m.shift - 1, nm->m.shift);
		writel(reg, nm->common.base + nm->common.reg);

		spin_unlock_irqrestore(nm->common.lock, flags);

		ccu_frac_helper_enable(&nm->common, &nm->frac);

		return ccu_frac_helper_set_rate(&nm->common, &nm->frac,
						rate, nm->lock);
	} else {
		ccu_frac_helper_disable(&nm->common, &nm->frac);
	}

	_nm.min_n = nm->n.min ?: 1;
	_nm.max_n = nm->n.max ?: 1 << nm->n.width;
	_nm.min_m = 1;
	_nm.max_m = nm->m.max ?: 1 << nm->m.width;

<<<<<<< HEAD
	if (ccu_sdm_helper_has_rate(&nm->common, &nm->sdm, rate)) {
		ccu_sdm_helper_enable(&nm->common, &nm->sdm, rate);

		/* Sigma delta modulation requires specific N and M factors */
		ccu_sdm_helper_get_factors(&nm->common, &nm->sdm, rate,
					   &_nm.m, &_nm.n);
	} else {
		ccu_sdm_helper_disable(&nm->common, &nm->sdm);
		ccu_nm_find_best(parent_rate, rate, &_nm);
	}
=======
	ccu_nm_find_best(parent_rate, rate, &_nm);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	spin_lock_irqsave(nm->common.lock, flags);

	reg = readl(nm->common.base + nm->common.reg);
	reg &= ~GENMASK(nm->n.width + nm->n.shift - 1, nm->n.shift);
	reg &= ~GENMASK(nm->m.width + nm->m.shift - 1, nm->m.shift);

	reg |= (_nm.n - nm->n.offset) << nm->n.shift;
	reg |= (_nm.m - nm->m.offset) << nm->m.shift;
	writel(reg, nm->common.base + nm->common.reg);

	spin_unlock_irqrestore(nm->common.lock, flags);

	ccu_helper_wait_for_lock(&nm->common, nm->lock);

	return 0;
}

const struct clk_ops ccu_nm_ops = {
	.disable	= ccu_nm_disable,
	.enable		= ccu_nm_enable,
	.is_enabled	= ccu_nm_is_enabled,

	.recalc_rate	= ccu_nm_recalc_rate,
	.round_rate	= ccu_nm_round_rate,
	.set_rate	= ccu_nm_set_rate,
};
