/*
 * ZyDAS ZD1301 driver (demodulator)
 *
 * Copyright (C) 2015 Antti Palosaari <crope@iki.fi>
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
 */

#ifndef ZD1301_DEMOD_H
#define ZD1301_DEMOD_H

#include <linux/platform_device.h>
#include <linux/dvb/frontend.h>
<<<<<<< HEAD
#include <media/dvb_frontend.h>
=======
#include "dvb_frontend.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/**
 * struct zd1301_demod_platform_data - Platform data for the zd1301_demod driver
 * @reg_priv: First argument of reg_read and reg_write callbacks.
 * @reg_read: Register read callback.
 * @reg_write: Register write callback.
 */
<<<<<<< HEAD
=======

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct zd1301_demod_platform_data {
	void *reg_priv;
	int (*reg_read)(void *, u16, u8 *);
	int (*reg_write)(void *, u16, u8);
};

#if IS_REACHABLE(CONFIG_DVB_ZD1301_DEMOD)
/**
 * zd1301_demod_get_dvb_frontend() - Get pointer to DVB frontend
 * @pdev: Pointer to platform device
 *
 * Return: Pointer to DVB frontend which given platform device owns.
 */
<<<<<<< HEAD
struct dvb_frontend *zd1301_demod_get_dvb_frontend(struct platform_device *pdev);
=======

struct dvb_frontend *zd1301_demod_get_dvb_frontend(struct platform_device *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/**
 * zd1301_demod_get_i2c_adapter() - Get pointer to I2C adapter
 * @pdev: Pointer to platform device
 *
 * Return: Pointer to I2C adapter which given platform device owns.
 */
<<<<<<< HEAD
struct i2c_adapter *zd1301_demod_get_i2c_adapter(struct platform_device *pdev);

#else

/**
 * zd1301_demod_get_dvb_frontend() - Attach a zd1301 frontend
 * @dev: Pointer to platform device
 *
 * Return: Pointer to %struct dvb_frontend or NULL if attach fails.
 */
=======

struct i2c_adapter *zd1301_demod_get_i2c_adapter(struct platform_device *);

#else

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static inline struct dvb_frontend *zd1301_demod_get_dvb_frontend(struct platform_device *dev)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);

	return NULL;
}
static inline struct i2c_adapter *zd1301_demod_get_i2c_adapter(struct platform_device *dev)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);

	return NULL;
}

#endif

#endif /* ZD1301_DEMOD_H */
