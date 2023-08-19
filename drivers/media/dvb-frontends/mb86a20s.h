/*
 *   Fujitsu mb86a20s driver
 *
 *   Copyright (C) 2010 Mauro Carvalho Chehab
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation version 2.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 */

#ifndef MB86A20S_H
#define MB86A20S_H

#include <linux/dvb/frontend.h>

/**
 * struct mb86a20s_config - Define the per-device attributes of the frontend
 *
 * @fclk:		Clock frequency. If zero, assumes the default
 *			(32.57142 Mhz)
 * @demod_address:	the demodulator's i2c address
 * @is_serial:		if true, TS is serial. Otherwise, TS is parallel
 */
<<<<<<< HEAD
=======

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct mb86a20s_config {
	u32	fclk;
	u8	demod_address;
	bool	is_serial;
};

#if IS_REACHABLE(CONFIG_DVB_MB86A20S)
<<<<<<< HEAD
/**
 * Attach a mb86a20s demod
 *
 * @config: pointer to &struct mb86a20s_config with demod configuration.
 * @i2c: i2c adapter to use.
 *
 * return: FE pointer on success, NULL on failure.
 */
extern struct dvb_frontend *mb86a20s_attach(const struct mb86a20s_config *config,
					   struct i2c_adapter *i2c);

=======
extern struct dvb_frontend *mb86a20s_attach(const struct mb86a20s_config *config,
					   struct i2c_adapter *i2c);
extern struct i2c_adapter *mb86a20s_get_tuner_i2c_adapter(struct dvb_frontend *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#else
static inline struct dvb_frontend *mb86a20s_attach(
	const struct mb86a20s_config *config, struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
<<<<<<< HEAD
=======
static inline struct i2c_adapter *
	mb86a20s_get_tuner_i2c_adapter(struct dvb_frontend *fe)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif

#endif /* MB86A20S */
