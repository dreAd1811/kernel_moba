/*
 * Realtek RTL2830 DVB-T demodulator driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 */

#ifndef RTL2830_PRIV_H
#define RTL2830_PRIV_H

<<<<<<< HEAD
#include <media/dvb_frontend.h>
#include <media/dvb_math.h>
=======
#include "dvb_frontend.h"
#include "dvb_math.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "rtl2830.h"
#include <linux/i2c-mux.h>
#include <linux/math64.h>
#include <linux/regmap.h>
#include <linux/bitops.h>

struct rtl2830_dev {
	struct rtl2830_platform_data *pdata;
	struct i2c_client *client;
	struct regmap *regmap;
	struct i2c_mux_core *muxc;
	struct dvb_frontend fe;
	bool sleeping;
	unsigned long filters;
	enum fe_status fe_status;
	u64 post_bit_error_prev; /* for old DVBv3 read_ber() calculation */
	u64 post_bit_error;
	u64 post_bit_count;
};

struct rtl2830_reg_val_mask {
	u16 reg;
	u8  val;
	u8  mask;
};

#endif /* RTL2830_PRIV_H */
