<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2015 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
=======
/*
 * Copyright (c) 2015 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 *
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

#ifndef __CLKC_H
#define __CLKC_H

<<<<<<< HEAD
#include <linux/clk-provider.h>
#include "clk-regmap.h"

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define PMASK(width)			GENMASK(width - 1, 0)
#define SETPMASK(width, shift)		GENMASK(shift + width - 1, shift)
#define CLRPMASK(width, shift)		(~SETPMASK(width, shift))

#define PARM_GET(width, shift, reg)					\
	(((reg) & SETPMASK(width, shift)) >> (shift))
#define PARM_SET(width, shift, reg, val)				\
	(((reg) & CLRPMASK(width, shift)) | ((val) << (shift)))

#define MESON_PARM_APPLICABLE(p)		(!!((p)->width))

struct parm {
	u16	reg_off;
	u8	shift;
	u8	width;
};

<<<<<<< HEAD
static inline unsigned int meson_parm_read(struct regmap *map, struct parm *p)
{
	unsigned int val;

	regmap_read(map, p->reg_off, &val);
	return PARM_GET(p->width, p->shift, val);
}

static inline void meson_parm_write(struct regmap *map, struct parm *p,
				    unsigned int val)
{
	regmap_update_bits(map, p->reg_off, SETPMASK(p->width, p->shift),
			   val << p->shift);
}


=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct pll_rate_table {
	unsigned long	rate;
	u16		m;
	u16		n;
	u16		od;
	u16		od2;
<<<<<<< HEAD
	u16		od3;
=======
	u16		frac;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

#define PLL_RATE(_r, _m, _n, _od)					\
	{								\
		.rate		= (_r),					\
		.m		= (_m),					\
		.n		= (_n),					\
		.od		= (_od),				\
<<<<<<< HEAD
	}

#define CLK_MESON_PLL_ROUND_CLOSEST	BIT(0)

struct meson_clk_pll_data {
=======
	}								\

#define PLL_FRAC_RATE(_r, _m, _n, _od, _od2, _frac)			\
	{								\
		.rate		= (_r),					\
		.m		= (_m),					\
		.n		= (_n),					\
		.od		= (_od),				\
		.od2		= (_od2),				\
		.frac		= (_frac),				\
	}								\

struct pll_params_table {
	unsigned int reg_off;
	unsigned int value;
};

#define PLL_PARAM(_reg, _val)						\
	{								\
		.reg_off	= (_reg),				\
		.value		= (_val),				\
	}

struct pll_setup_params {
	struct pll_params_table *params_table;
	unsigned int params_count;
	/* Workaround for GP0, do not reset before configuring */
	bool no_init_reset;
	/* Workaround for GP0, unreset right before checking for lock */
	bool clear_reset_for_lock;
	/* Workaround for GXL GP0, reset in the lock checking loop */
	bool reset_lock_loop;
};

struct meson_clk_pll {
	struct clk_hw hw;
	void __iomem *base;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct parm m;
	struct parm n;
	struct parm frac;
	struct parm od;
	struct parm od2;
<<<<<<< HEAD
	struct parm od3;
	struct parm l;
	struct parm rst;
	const struct reg_sequence *init_regs;
	unsigned int init_count;
	const struct pll_rate_table *table;
	u8 flags;
=======
	const struct pll_setup_params params;
	const struct pll_rate_table *rate_table;
	unsigned int rate_count;
	spinlock_t *lock;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

#define to_meson_clk_pll(_hw) container_of(_hw, struct meson_clk_pll, hw)

<<<<<<< HEAD
struct meson_clk_mpll_data {
	struct parm sdm;
	struct parm sdm_en;
	struct parm n2;
	struct parm ssen;
	struct parm misc;
	spinlock_t *lock;
	u8 flags;
};

#define CLK_MESON_MPLL_ROUND_CLOSEST	BIT(0)

struct meson_clk_phase_data {
	struct parm ph;
};

int meson_clk_degrees_from_val(unsigned int val, unsigned int width);
unsigned int meson_clk_degrees_to_val(int degrees, unsigned int width);

#define MESON_GATE(_name, _reg, _bit)					\
struct clk_regmap _name = {						\
	.data = &(struct clk_regmap_gate_data){				\
		.offset = (_reg),					\
		.bit_idx = (_bit),					\
	},								\
	.hw.init = &(struct clk_init_data) {				\
		.name = #_name,						\
		.ops = &clk_regmap_gate_ops,				\
		.parent_names = (const char *[]){ "clk81" },		\
		.num_parents = 1,					\
		.flags = (CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED),	\
=======
struct meson_clk_cpu {
	struct clk_hw hw;
	void __iomem *base;
	u16 reg_off;
	struct notifier_block clk_nb;
	const struct clk_div_table *div_table;
};

int meson_clk_cpu_notifier_cb(struct notifier_block *nb, unsigned long event,
		void *data);

struct meson_clk_mpll {
	struct clk_hw hw;
	void __iomem *base;
	struct parm sdm;
	struct parm sdm_en;
	struct parm n2;
	struct parm en;
	struct parm ssen;
	spinlock_t *lock;
};

struct meson_clk_audio_divider {
	struct clk_hw hw;
	void __iomem *base;
	struct parm div;
	u8 flags;
	spinlock_t *lock;
};

#define MESON_GATE(_name, _reg, _bit)					\
struct clk_gate _name = { 						\
	.reg = (void __iomem *) _reg, 					\
	.bit_idx = (_bit), 						\
	.lock = &clk_lock,						\
	.hw.init = &(struct clk_init_data) { 				\
		.name = #_name,					\
		.ops = &clk_gate_ops,					\
		.parent_names = (const char *[]){ "clk81" },		\
		.num_parents = 1,					\
		.flags = (CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED), 	\
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},								\
};

/* clk_ops */
extern const struct clk_ops meson_clk_pll_ro_ops;
extern const struct clk_ops meson_clk_pll_ops;
extern const struct clk_ops meson_clk_cpu_ops;
extern const struct clk_ops meson_clk_mpll_ro_ops;
extern const struct clk_ops meson_clk_mpll_ops;
<<<<<<< HEAD
extern const struct clk_ops meson_clk_phase_ops;
=======
extern const struct clk_ops meson_clk_audio_divider_ro_ops;
extern const struct clk_ops meson_clk_audio_divider_ops;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* __CLKC_H */
