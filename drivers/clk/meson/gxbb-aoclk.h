<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2017 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
=======
/*
 * Copyright (c) 2017 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef __GXBB_AOCLKC_H
#define __GXBB_AOCLKC_H

<<<<<<< HEAD
#define NR_CLKS	7

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/* AO Configuration Clock registers offsets */
#define AO_RTI_PWR_CNTL_REG1	0x0c
#define AO_RTI_PWR_CNTL_REG0	0x10
#define AO_RTI_GEN_CNTL_REG0	0x40
#define AO_OSCIN_CNTL		0x58
#define AO_CRT_CLK_CNTL1	0x68
#define AO_RTC_ALT_CLK_CNTL0	0x94
#define AO_RTC_ALT_CLK_CNTL1	0x98

<<<<<<< HEAD
struct aoclk_cec_32k {
	struct clk_hw hw;
	struct regmap *regmap;
=======
struct aoclk_gate_regmap {
	struct clk_hw hw;
	unsigned bit_idx;
	struct regmap *regmap;
	spinlock_t *lock;
};

#define to_aoclk_gate_regmap(_hw) \
	container_of(_hw, struct aoclk_gate_regmap, hw)

extern const struct clk_ops meson_aoclk_gate_regmap_ops;

struct aoclk_cec_32k {
	struct clk_hw hw;
	struct regmap *regmap;
	spinlock_t *lock;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

#define to_aoclk_cec_32k(_hw) container_of(_hw, struct aoclk_cec_32k, hw)

extern const struct clk_ops meson_aoclk_cec_32k_ops;

<<<<<<< HEAD
#include <dt-bindings/clock/gxbb-aoclkc.h>
#include <dt-bindings/reset/gxbb-aoclkc.h>

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* __GXBB_AOCLKC_H */
