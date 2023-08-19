/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/clk-provider.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/clkdev.h>
#include <linux/of_address.h>
#include <linux/delay.h>

#include "clk-iproc.h"

#define PLL_VCO_HIGH_SHIFT 19
#define PLL_VCO_LOW_SHIFT  30

/*
 * PLL MACRO_SELECT modes 0 to 5 choose pre-calculated PLL output frequencies
 * from a look-up table. Mode 7 allows user to manipulate PLL clock dividers
 */
#define PLL_USER_MODE 7

/* number of delay loops waiting for PLL to lock */
#define LOCK_DELAY 100

/* number of VCO frequency bands */
#define NUM_FREQ_BANDS 8

#define NUM_KP_BANDS 3
enum kp_band {
	KP_BAND_MID = 0,
	KP_BAND_HIGH,
	KP_BAND_HIGH_HIGH
};

static const unsigned int kp_table[NUM_KP_BANDS][NUM_FREQ_BANDS] = {
	{ 5, 6, 6, 7, 7, 8, 9, 10 },
	{ 4, 4, 5, 5, 6, 7, 8, 9  },
	{ 4, 5, 5, 6, 7, 8, 9, 10 },
};

static const unsigned long ref_freq_table[NUM_FREQ_BANDS][2] = {
	{ 10000000,  12500000  },
	{ 12500000,  15000000  },
	{ 15000000,  20000000  },
	{ 20000000,  25000000  },
	{ 25000000,  50000000  },
	{ 50000000,  75000000  },
	{ 75000000,  100000000 },
	{ 100000000, 125000000 },
};

enum vco_freq_range {
	VCO_LOW       = 700000000U,
	VCO_MID       = 1200000000U,
	VCO_HIGH      = 2200000000U,
	VCO_HIGH_HIGH = 3100000000U,
	VCO_MAX       = 4000000000U,
};

<<<<<<< HEAD
=======
struct iproc_pll;

struct iproc_clk {
	struct clk_hw hw;
	const char *name;
	struct iproc_pll *pll;
	unsigned long rate;
	const struct iproc_clk_ctrl *ctrl;
};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct iproc_pll {
	void __iomem *status_base;
	void __iomem *control_base;
	void __iomem *pwr_base;
	void __iomem *asiu_base;

	const struct iproc_pll_ctrl *ctrl;
	const struct iproc_pll_vco_param *vco_param;
	unsigned int num_vco_entries;
<<<<<<< HEAD
};

struct iproc_clk {
	struct clk_hw hw;
	struct iproc_pll *pll;
	const struct iproc_clk_ctrl *ctrl;
=======

	struct clk_hw_onecell_data *clk_data;
	struct iproc_clk *clks;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

#define to_iproc_clk(hw) container_of(hw, struct iproc_clk, hw)

<<<<<<< HEAD
static int pll_calc_param(unsigned long target_rate,
			unsigned long parent_rate,
			struct iproc_pll_vco_param *vco_out)
{
	u64 ndiv_int, ndiv_frac, residual;

	ndiv_int = target_rate / parent_rate;

	if (!ndiv_int || (ndiv_int > 255))
		return -EINVAL;

	residual = target_rate - (ndiv_int * parent_rate);
	residual <<= 20;

	/*
	 * Add half of the divisor so the result will be rounded to closest
	 * instead of rounded down.
	 */
	residual += (parent_rate / 2);
	ndiv_frac = div64_u64((u64)residual, (u64)parent_rate);

	vco_out->ndiv_int = ndiv_int;
	vco_out->ndiv_frac = ndiv_frac;
	vco_out->pdiv = 1;

	vco_out->rate = vco_out->ndiv_int * parent_rate;
	residual = (u64)vco_out->ndiv_frac * (u64)parent_rate;
	residual >>= 20;
	vco_out->rate += residual;

	return 0;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Based on the target frequency, find a match from the VCO frequency parameter
 * table and return its index
 */
static int pll_get_rate_index(struct iproc_pll *pll, unsigned int target_rate)
{
	int i;

	for (i = 0; i < pll->num_vco_entries; i++)
		if (target_rate == pll->vco_param[i].rate)
			break;

	if (i >= pll->num_vco_entries)
		return -EINVAL;

	return i;
}

static int get_kp(unsigned long ref_freq, enum kp_band kp_index)
{
	int i;

	if (ref_freq < ref_freq_table[0][0])
		return -EINVAL;

	for (i = 0; i < NUM_FREQ_BANDS; i++) {
		if (ref_freq >= ref_freq_table[i][0] &&
		    ref_freq < ref_freq_table[i][1])
			return kp_table[kp_index][i];
	}
	return -EINVAL;
}

static int pll_wait_for_lock(struct iproc_pll *pll)
{
	int i;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;

	for (i = 0; i < LOCK_DELAY; i++) {
		u32 val = readl(pll->status_base + ctrl->status.offset);

		if (val & (1 << ctrl->status.shift))
			return 0;
		udelay(10);
	}

	return -EIO;
}

static void iproc_pll_write(const struct iproc_pll *pll, void __iomem *base,
			    const u32 offset, u32 val)
{
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;

	writel(val, base + offset);

	if (unlikely(ctrl->flags & IPROC_CLK_NEEDS_READ_BACK &&
		     (base == pll->status_base || base == pll->control_base)))
		val = readl(base + offset);
}

static void __pll_disable(struct iproc_pll *pll)
{
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;

	if (ctrl->flags & IPROC_CLK_PLL_ASIU) {
		val = readl(pll->asiu_base + ctrl->asiu.offset);
		val &= ~(1 << ctrl->asiu.en_shift);
		iproc_pll_write(pll, pll->asiu_base, ctrl->asiu.offset, val);
	}

	if (ctrl->flags & IPROC_CLK_EMBED_PWRCTRL) {
		val = readl(pll->control_base + ctrl->aon.offset);
		val |= bit_mask(ctrl->aon.pwr_width) << ctrl->aon.pwr_shift;
		iproc_pll_write(pll, pll->control_base, ctrl->aon.offset, val);
	}

	if (pll->pwr_base) {
		/* latch input value so core power can be shut down */
		val = readl(pll->pwr_base + ctrl->aon.offset);
		val |= 1 << ctrl->aon.iso_shift;
		iproc_pll_write(pll, pll->pwr_base, ctrl->aon.offset, val);

		/* power down the core */
		val &= ~(bit_mask(ctrl->aon.pwr_width) << ctrl->aon.pwr_shift);
		iproc_pll_write(pll, pll->pwr_base, ctrl->aon.offset, val);
	}
}

static int __pll_enable(struct iproc_pll *pll)
{
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;

	if (ctrl->flags & IPROC_CLK_EMBED_PWRCTRL) {
		val = readl(pll->control_base + ctrl->aon.offset);
		val &= ~(bit_mask(ctrl->aon.pwr_width) << ctrl->aon.pwr_shift);
		iproc_pll_write(pll, pll->control_base, ctrl->aon.offset, val);
	}

	if (pll->pwr_base) {
		/* power up the PLL and make sure it's not latched */
		val = readl(pll->pwr_base + ctrl->aon.offset);
		val |= bit_mask(ctrl->aon.pwr_width) << ctrl->aon.pwr_shift;
		val &= ~(1 << ctrl->aon.iso_shift);
		iproc_pll_write(pll, pll->pwr_base, ctrl->aon.offset, val);
	}

	/* certain PLLs also need to be ungated from the ASIU top level */
	if (ctrl->flags & IPROC_CLK_PLL_ASIU) {
		val = readl(pll->asiu_base + ctrl->asiu.offset);
		val |= (1 << ctrl->asiu.en_shift);
		iproc_pll_write(pll, pll->asiu_base, ctrl->asiu.offset, val);
	}

	return 0;
}

static void __pll_put_in_reset(struct iproc_pll *pll)
{
	u32 val;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	const struct iproc_pll_reset_ctrl *reset = &ctrl->reset;

	val = readl(pll->control_base + reset->offset);
	if (ctrl->flags & IPROC_CLK_PLL_RESET_ACTIVE_LOW)
		val |= BIT(reset->reset_shift) | BIT(reset->p_reset_shift);
	else
		val &= ~(BIT(reset->reset_shift) | BIT(reset->p_reset_shift));
	iproc_pll_write(pll, pll->control_base, reset->offset, val);
}

static void __pll_bring_out_reset(struct iproc_pll *pll, unsigned int kp,
				  unsigned int ka, unsigned int ki)
{
	u32 val;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	const struct iproc_pll_reset_ctrl *reset = &ctrl->reset;
	const struct iproc_pll_dig_filter_ctrl *dig_filter = &ctrl->dig_filter;

	val = readl(pll->control_base + dig_filter->offset);
	val &= ~(bit_mask(dig_filter->ki_width) << dig_filter->ki_shift |
		bit_mask(dig_filter->kp_width) << dig_filter->kp_shift |
		bit_mask(dig_filter->ka_width) << dig_filter->ka_shift);
	val |= ki << dig_filter->ki_shift | kp << dig_filter->kp_shift |
	       ka << dig_filter->ka_shift;
	iproc_pll_write(pll, pll->control_base, dig_filter->offset, val);

	val = readl(pll->control_base + reset->offset);
	if (ctrl->flags & IPROC_CLK_PLL_RESET_ACTIVE_LOW)
		val &= ~(BIT(reset->reset_shift) | BIT(reset->p_reset_shift));
	else
		val |= BIT(reset->reset_shift) | BIT(reset->p_reset_shift);
	iproc_pll_write(pll, pll->control_base, reset->offset, val);
}

<<<<<<< HEAD
/*
 * Determines if the change to be applied to the PLL is minor (just an update
 * or the fractional divider). If so, then we can avoid going through a
 * disruptive reset and lock sequence.
 */
static bool pll_fractional_change_only(struct iproc_pll *pll,
				       struct iproc_pll_vco_param *vco)
{
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;
	u32 ndiv_int;
	unsigned int pdiv;

	/* PLL needs to be locked */
	val = readl(pll->status_base + ctrl->status.offset);
	if ((val & (1 << ctrl->status.shift)) == 0)
		return false;

	val = readl(pll->control_base + ctrl->ndiv_int.offset);
	ndiv_int = (val >> ctrl->ndiv_int.shift) &
		bit_mask(ctrl->ndiv_int.width);

	if (ndiv_int != vco->ndiv_int)
		return false;

	val = readl(pll->control_base + ctrl->pdiv.offset);
	pdiv = (val >> ctrl->pdiv.shift) & bit_mask(ctrl->pdiv.width);

	if (pdiv != vco->pdiv)
		return false;

	return true;
}

static int pll_set_rate(struct iproc_clk *clk, struct iproc_pll_vco_param *vco,
			unsigned long parent_rate)
{
	struct iproc_pll *pll = clk->pll;
=======
static int pll_set_rate(struct iproc_clk *clk, unsigned int rate_index,
			unsigned long parent_rate)
{
	struct iproc_pll *pll = clk->pll;
	const struct iproc_pll_vco_param *vco = &pll->vco_param[rate_index];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	int ka = 0, ki, kp, ret;
	unsigned long rate = vco->rate;
	u32 val;
	enum kp_band kp_index;
	unsigned long ref_freq;
<<<<<<< HEAD
	const char *clk_name = clk_hw_get_name(&clk->hw);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * reference frequency = parent frequency / PDIV
	 * If PDIV = 0, then it becomes a multiplier (x2)
	 */
	if (vco->pdiv == 0)
		ref_freq = parent_rate * 2;
	else
		ref_freq = parent_rate / vco->pdiv;

	/* determine Ki and Kp index based on target VCO frequency */
	if (rate >= VCO_LOW && rate < VCO_HIGH) {
		ki = 4;
		kp_index = KP_BAND_MID;
	} else if (rate >= VCO_HIGH && rate < VCO_HIGH_HIGH) {
		ki = 3;
		kp_index = KP_BAND_HIGH;
	} else if (rate >= VCO_HIGH_HIGH && rate < VCO_MAX) {
		ki = 3;
		kp_index = KP_BAND_HIGH_HIGH;
	} else {
		pr_err("%s: pll: %s has invalid rate: %lu\n", __func__,
<<<<<<< HEAD
				clk_name, rate);
=======
				clk->name, rate);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;
	}

	kp = get_kp(ref_freq, kp_index);
	if (kp < 0) {
<<<<<<< HEAD
		pr_err("%s: pll: %s has invalid kp\n", __func__, clk_name);
=======
		pr_err("%s: pll: %s has invalid kp\n", __func__, clk->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return kp;
	}

	ret = __pll_enable(pll);
	if (ret) {
<<<<<<< HEAD
		pr_err("%s: pll: %s fails to enable\n", __func__, clk_name);
		return ret;
	}

	if (pll_fractional_change_only(clk->pll, vco)) {
		/* program fractional part of NDIV */
		if (ctrl->flags & IPROC_CLK_PLL_HAS_NDIV_FRAC) {
			val = readl(pll->control_base + ctrl->ndiv_frac.offset);
			val &= ~(bit_mask(ctrl->ndiv_frac.width) <<
				 ctrl->ndiv_frac.shift);
			val |= vco->ndiv_frac << ctrl->ndiv_frac.shift;
			iproc_pll_write(pll, pll->control_base,
					ctrl->ndiv_frac.offset, val);
			return 0;
		}
	}

=======
		pr_err("%s: pll: %s fails to enable\n", __func__, clk->name);
		return ret;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* put PLL in reset */
	__pll_put_in_reset(pll);

	/* set PLL in user mode before modifying PLL controls */
	if (ctrl->flags & IPROC_CLK_PLL_USER_MODE_ON) {
		val = readl(pll->control_base + ctrl->macro_mode.offset);
		val &= ~(bit_mask(ctrl->macro_mode.width) <<
			ctrl->macro_mode.shift);
		val |= PLL_USER_MODE << ctrl->macro_mode.shift;
		iproc_pll_write(pll, pll->control_base,
			ctrl->macro_mode.offset, val);
	}

	iproc_pll_write(pll, pll->control_base, ctrl->vco_ctrl.u_offset, 0);

	val = readl(pll->control_base + ctrl->vco_ctrl.l_offset);

	if (rate >= VCO_LOW && rate < VCO_MID)
		val |= (1 << PLL_VCO_LOW_SHIFT);

	if (rate < VCO_HIGH)
		val &= ~(1 << PLL_VCO_HIGH_SHIFT);
	else
		val |= (1 << PLL_VCO_HIGH_SHIFT);

	iproc_pll_write(pll, pll->control_base, ctrl->vco_ctrl.l_offset, val);

	/* program integer part of NDIV */
	val = readl(pll->control_base + ctrl->ndiv_int.offset);
	val &= ~(bit_mask(ctrl->ndiv_int.width) << ctrl->ndiv_int.shift);
	val |= vco->ndiv_int << ctrl->ndiv_int.shift;
	iproc_pll_write(pll, pll->control_base, ctrl->ndiv_int.offset, val);

	/* program fractional part of NDIV */
	if (ctrl->flags & IPROC_CLK_PLL_HAS_NDIV_FRAC) {
		val = readl(pll->control_base + ctrl->ndiv_frac.offset);
		val &= ~(bit_mask(ctrl->ndiv_frac.width) <<
			 ctrl->ndiv_frac.shift);
		val |= vco->ndiv_frac << ctrl->ndiv_frac.shift;
		iproc_pll_write(pll, pll->control_base, ctrl->ndiv_frac.offset,
				val);
	}

	/* program PDIV */
	val = readl(pll->control_base + ctrl->pdiv.offset);
	val &= ~(bit_mask(ctrl->pdiv.width) << ctrl->pdiv.shift);
	val |= vco->pdiv << ctrl->pdiv.shift;
	iproc_pll_write(pll, pll->control_base, ctrl->pdiv.offset, val);

	__pll_bring_out_reset(pll, kp, ka, ki);

	ret = pll_wait_for_lock(pll);
	if (ret < 0) {
<<<<<<< HEAD
		pr_err("%s: pll: %s failed to lock\n", __func__, clk_name);
=======
		pr_err("%s: pll: %s failed to lock\n", __func__, clk->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return ret;
	}

	return 0;
}

static int iproc_pll_enable(struct clk_hw *hw)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;

	return __pll_enable(pll);
}

static void iproc_pll_disable(struct clk_hw *hw)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;

	if (ctrl->flags & IPROC_CLK_AON)
		return;

	__pll_disable(pll);
}

static unsigned long iproc_pll_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;
	u64 ndiv, ndiv_int, ndiv_frac;
	unsigned int pdiv;
<<<<<<< HEAD
	unsigned long rate;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (parent_rate == 0)
		return 0;

	/* PLL needs to be locked */
	val = readl(pll->status_base + ctrl->status.offset);
<<<<<<< HEAD
	if ((val & (1 << ctrl->status.shift)) == 0)
		return 0;
=======
	if ((val & (1 << ctrl->status.shift)) == 0) {
		clk->rate = 0;
		return 0;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * PLL output frequency =
	 *
	 * ((ndiv_int + ndiv_frac / 2^20) * (parent clock rate / pdiv)
	 */
	val = readl(pll->control_base + ctrl->ndiv_int.offset);
	ndiv_int = (val >> ctrl->ndiv_int.shift) &
		bit_mask(ctrl->ndiv_int.width);
	ndiv = ndiv_int << 20;

	if (ctrl->flags & IPROC_CLK_PLL_HAS_NDIV_FRAC) {
		val = readl(pll->control_base + ctrl->ndiv_frac.offset);
		ndiv_frac = (val >> ctrl->ndiv_frac.shift) &
			bit_mask(ctrl->ndiv_frac.width);
		ndiv += ndiv_frac;
	}

	val = readl(pll->control_base + ctrl->pdiv.offset);
	pdiv = (val >> ctrl->pdiv.shift) & bit_mask(ctrl->pdiv.width);

<<<<<<< HEAD
	rate = (ndiv * parent_rate) >> 20;

	if (pdiv == 0)
		rate *= 2;
	else
		rate /= pdiv;

	return rate;
}

static int iproc_pll_determine_rate(struct clk_hw *hw,
		struct clk_rate_request *req)
{
	unsigned int  i;
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	unsigned long  diff, best_diff;
	unsigned int  best_idx = 0;
	int ret;

	if (req->rate == 0 || req->best_parent_rate == 0)
		return -EINVAL;

	if (ctrl->flags & IPROC_CLK_PLL_CALC_PARAM) {
		struct iproc_pll_vco_param vco_param;

		ret = pll_calc_param(req->rate, req->best_parent_rate,
					&vco_param);
		if (ret)
			return ret;

		req->rate = vco_param.rate;
		return 0;
	}

	if (!pll->vco_param)
		return -EINVAL;

	best_diff = ULONG_MAX;
	for (i = 0; i < pll->num_vco_entries; i++) {
		diff = abs(req->rate - pll->vco_param[i].rate);
		if (diff <= best_diff) {
			best_diff = diff;
			best_idx = i;
		}
		/* break now if perfect match */
		if (diff == 0)
			break;
	}

	req->rate = pll->vco_param[best_idx].rate;

	return 0;
=======
	clk->rate = (ndiv * parent_rate) >> 20;

	if (pdiv == 0)
		clk->rate *= 2;
	else
		clk->rate /= pdiv;

	return clk->rate;
}

static long iproc_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *parent_rate)
{
	unsigned i;
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;

	if (rate == 0 || *parent_rate == 0 || !pll->vco_param)
		return -EINVAL;

	for (i = 0; i < pll->num_vco_entries; i++) {
		if (rate <= pll->vco_param[i].rate)
			break;
	}

	if (i == pll->num_vco_entries)
		i--;

	return pll->vco_param[i].rate;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int iproc_pll_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;
<<<<<<< HEAD
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	struct iproc_pll_vco_param vco_param;
	int rate_index, ret;

	if (ctrl->flags & IPROC_CLK_PLL_CALC_PARAM) {
		ret = pll_calc_param(rate, parent_rate, &vco_param);
		if (ret)
			return ret;
	} else {
		rate_index = pll_get_rate_index(pll, rate);
		if (rate_index < 0)
			return rate_index;

		vco_param = pll->vco_param[rate_index];
	}

	ret = pll_set_rate(clk, &vco_param, parent_rate);
=======
	int rate_index, ret;

	rate_index = pll_get_rate_index(pll, rate);
	if (rate_index < 0)
		return rate_index;

	ret = pll_set_rate(clk, rate_index, parent_rate);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static const struct clk_ops iproc_pll_ops = {
	.enable = iproc_pll_enable,
	.disable = iproc_pll_disable,
	.recalc_rate = iproc_pll_recalc_rate,
<<<<<<< HEAD
	.determine_rate = iproc_pll_determine_rate,
=======
	.round_rate = iproc_pll_round_rate,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.set_rate = iproc_pll_set_rate,
};

static int iproc_clk_enable(struct clk_hw *hw)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	const struct iproc_clk_ctrl *ctrl = clk->ctrl;
	struct iproc_pll *pll = clk->pll;
	u32 val;

	/* channel enable is active low */
	val = readl(pll->control_base + ctrl->enable.offset);
	val &= ~(1 << ctrl->enable.enable_shift);
	iproc_pll_write(pll, pll->control_base, ctrl->enable.offset, val);

	/* also make sure channel is not held */
	val = readl(pll->control_base + ctrl->enable.offset);
	val &= ~(1 << ctrl->enable.hold_shift);
	iproc_pll_write(pll, pll->control_base, ctrl->enable.offset, val);

	return 0;
}

static void iproc_clk_disable(struct clk_hw *hw)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	const struct iproc_clk_ctrl *ctrl = clk->ctrl;
	struct iproc_pll *pll = clk->pll;
	u32 val;

	if (ctrl->flags & IPROC_CLK_AON)
		return;

	val = readl(pll->control_base + ctrl->enable.offset);
	val |= 1 << ctrl->enable.enable_shift;
	iproc_pll_write(pll, pll->control_base, ctrl->enable.offset, val);
}

static unsigned long iproc_clk_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	const struct iproc_clk_ctrl *ctrl = clk->ctrl;
	struct iproc_pll *pll = clk->pll;
	u32 val;
	unsigned int mdiv;
<<<<<<< HEAD
	unsigned long rate;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (parent_rate == 0)
		return 0;

	val = readl(pll->control_base + ctrl->mdiv.offset);
	mdiv = (val >> ctrl->mdiv.shift) & bit_mask(ctrl->mdiv.width);
	if (mdiv == 0)
		mdiv = 256;

	if (ctrl->flags & IPROC_CLK_MCLK_DIV_BY_2)
<<<<<<< HEAD
		rate = parent_rate / (mdiv * 2);
	else
		rate = parent_rate / mdiv;

	return rate;
}

static int iproc_clk_determine_rate(struct clk_hw *hw,
		struct clk_rate_request *req)
{
	unsigned int bestdiv;

	if (req->rate == 0)
		return -EINVAL;
	if (req->rate == req->best_parent_rate)
		return 0;

	bestdiv = DIV_ROUND_CLOSEST(req->best_parent_rate, req->rate);
	if (bestdiv < 2)
		req->rate = req->best_parent_rate;

	if (bestdiv > 256)
		bestdiv = 256;

	req->rate = req->best_parent_rate / bestdiv;

	return 0;
=======
		clk->rate = parent_rate / (mdiv * 2);
	else
		clk->rate = parent_rate / mdiv;

	return clk->rate;
}

static long iproc_clk_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *parent_rate)
{
	unsigned int div;

	if (rate == 0 || *parent_rate == 0)
		return -EINVAL;

	if (rate == *parent_rate)
		return *parent_rate;

	div = DIV_ROUND_UP(*parent_rate, rate);
	if (div < 2)
		return *parent_rate;

	if (div > 256)
		div = 256;

	return *parent_rate / div;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int iproc_clk_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	const struct iproc_clk_ctrl *ctrl = clk->ctrl;
	struct iproc_pll *pll = clk->pll;
	u32 val;
	unsigned int div;

	if (rate == 0 || parent_rate == 0)
		return -EINVAL;

<<<<<<< HEAD
	div = DIV_ROUND_CLOSEST(parent_rate, rate);
	if (ctrl->flags & IPROC_CLK_MCLK_DIV_BY_2)
		div /=  2;

=======
	if (ctrl->flags & IPROC_CLK_MCLK_DIV_BY_2)
		div = DIV_ROUND_UP(parent_rate, rate * 2);
	else
		div = DIV_ROUND_UP(parent_rate, rate);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (div > 256)
		return -EINVAL;

	val = readl(pll->control_base + ctrl->mdiv.offset);
	if (div == 256) {
		val &= ~(bit_mask(ctrl->mdiv.width) << ctrl->mdiv.shift);
	} else {
		val &= ~(bit_mask(ctrl->mdiv.width) << ctrl->mdiv.shift);
		val |= div << ctrl->mdiv.shift;
	}
	iproc_pll_write(pll, pll->control_base, ctrl->mdiv.offset, val);
<<<<<<< HEAD
=======
	if (ctrl->flags & IPROC_CLK_MCLK_DIV_BY_2)
		clk->rate = parent_rate / (div * 2);
	else
		clk->rate = parent_rate / div;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

static const struct clk_ops iproc_clk_ops = {
	.enable = iproc_clk_enable,
	.disable = iproc_clk_disable,
	.recalc_rate = iproc_clk_recalc_rate,
<<<<<<< HEAD
	.determine_rate = iproc_clk_determine_rate,
=======
	.round_rate = iproc_clk_round_rate,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.set_rate = iproc_clk_set_rate,
};

/**
 * Some PLLs require the PLL SW override bit to be set before changes can be
 * applied to the PLL
 */
static void iproc_pll_sw_cfg(struct iproc_pll *pll)
{
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;

	if (ctrl->flags & IPROC_CLK_PLL_NEEDS_SW_CFG) {
		u32 val;

		val = readl(pll->control_base + ctrl->sw_ctrl.offset);
		val |= BIT(ctrl->sw_ctrl.shift);
		iproc_pll_write(pll, pll->control_base, ctrl->sw_ctrl.offset,
				val);
	}
}

void iproc_pll_clk_setup(struct device_node *node,
			 const struct iproc_pll_ctrl *pll_ctrl,
			 const struct iproc_pll_vco_param *vco,
			 unsigned int num_vco_entries,
			 const struct iproc_clk_ctrl *clk_ctrl,
			 unsigned int num_clks)
{
	int i, ret;
	struct iproc_pll *pll;
	struct iproc_clk *iclk;
	struct clk_init_data init;
	const char *parent_name;
<<<<<<< HEAD
	struct iproc_clk *iclk_array;
	struct clk_hw_onecell_data *clk_data;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (WARN_ON(!pll_ctrl) || WARN_ON(!clk_ctrl))
		return;

	pll = kzalloc(sizeof(*pll), GFP_KERNEL);
	if (WARN_ON(!pll))
		return;

<<<<<<< HEAD
	clk_data = kzalloc(struct_size(clk_data, hws, num_clks), GFP_KERNEL);
	if (WARN_ON(!clk_data))
		goto err_clk_data;
	clk_data->num = num_clks;

	iclk_array = kcalloc(num_clks, sizeof(struct iproc_clk), GFP_KERNEL);
	if (WARN_ON(!iclk_array))
=======
	pll->clk_data = kzalloc(sizeof(*pll->clk_data->hws) * num_clks +
				sizeof(*pll->clk_data), GFP_KERNEL);
	if (WARN_ON(!pll->clk_data))
		goto err_clk_data;
	pll->clk_data->num = num_clks;

	pll->clks = kcalloc(num_clks, sizeof(*pll->clks), GFP_KERNEL);
	if (WARN_ON(!pll->clks))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		goto err_clks;

	pll->control_base = of_iomap(node, 0);
	if (WARN_ON(!pll->control_base))
		goto err_pll_iomap;

	/* Some SoCs do not require the pwr_base, thus failing is not fatal */
	pll->pwr_base = of_iomap(node, 1);

	/* some PLLs require gating control at the top ASIU level */
	if (pll_ctrl->flags & IPROC_CLK_PLL_ASIU) {
		pll->asiu_base = of_iomap(node, 2);
		if (WARN_ON(!pll->asiu_base))
			goto err_asiu_iomap;
	}

	if (pll_ctrl->flags & IPROC_CLK_PLL_SPLIT_STAT_CTRL) {
		/* Some SoCs have a split status/control.  If this does not
		 * exist, assume they are unified.
		 */
		pll->status_base = of_iomap(node, 2);
		if (!pll->status_base)
			goto err_status_iomap;
	} else
		pll->status_base = pll->control_base;

	/* initialize and register the PLL itself */
	pll->ctrl = pll_ctrl;

<<<<<<< HEAD
	iclk = &iclk_array[0];
	iclk->pll = pll;
=======
	iclk = &pll->clks[0];
	iclk->pll = pll;
	iclk->name = node->name;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	init.name = node->name;
	init.ops = &iproc_pll_ops;
	init.flags = 0;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = (parent_name ? &parent_name : NULL);
	init.num_parents = (parent_name ? 1 : 0);
	iclk->hw.init = &init;

	if (vco) {
		pll->num_vco_entries = num_vco_entries;
		pll->vco_param = vco;
	}

	iproc_pll_sw_cfg(pll);

	ret = clk_hw_register(NULL, &iclk->hw);
	if (WARN_ON(ret))
		goto err_pll_register;

<<<<<<< HEAD
	clk_data->hws[0] = &iclk->hw;
=======
	pll->clk_data->hws[0] = &iclk->hw;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* now initialize and register all leaf clocks */
	for (i = 1; i < num_clks; i++) {
		const char *clk_name;

		memset(&init, 0, sizeof(init));
		parent_name = node->name;

		ret = of_property_read_string_index(node, "clock-output-names",
						    i, &clk_name);
		if (WARN_ON(ret))
			goto err_clk_register;

<<<<<<< HEAD
		iclk = &iclk_array[i];
=======
		iclk = &pll->clks[i];
		iclk->name = clk_name;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		iclk->pll = pll;
		iclk->ctrl = &clk_ctrl[i];

		init.name = clk_name;
		init.ops = &iproc_clk_ops;
		init.flags = 0;
		init.parent_names = (parent_name ? &parent_name : NULL);
		init.num_parents = (parent_name ? 1 : 0);
		iclk->hw.init = &init;

		ret = clk_hw_register(NULL, &iclk->hw);
		if (WARN_ON(ret))
			goto err_clk_register;

<<<<<<< HEAD
		clk_data->hws[i] = &iclk->hw;
	}

	ret = of_clk_add_hw_provider(node, of_clk_hw_onecell_get, clk_data);
=======
		pll->clk_data->hws[i] = &iclk->hw;
	}

	ret = of_clk_add_hw_provider(node, of_clk_hw_onecell_get,
				     pll->clk_data);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (WARN_ON(ret))
		goto err_clk_register;

	return;

err_clk_register:
	while (--i >= 0)
<<<<<<< HEAD
		clk_hw_unregister(clk_data->hws[i]);
=======
		clk_hw_unregister(pll->clk_data->hws[i]);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

err_pll_register:
	if (pll->status_base != pll->control_base)
		iounmap(pll->status_base);

err_status_iomap:
	if (pll->asiu_base)
		iounmap(pll->asiu_base);

err_asiu_iomap:
	if (pll->pwr_base)
		iounmap(pll->pwr_base);

	iounmap(pll->control_base);

err_pll_iomap:
<<<<<<< HEAD
	kfree(iclk_array);

err_clks:
	kfree(clk_data);
=======
	kfree(pll->clks);

err_clks:
	kfree(pll->clk_data);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

err_clk_data:
	kfree(pll);
}
