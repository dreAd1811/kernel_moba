/* SPDX-License-Identifier: GPL-2.0 */
#ifndef LINUX_FC0011_H_
#define LINUX_FC0011_H_

<<<<<<< HEAD
#include <media/dvb_frontend.h>
=======
#include "dvb_frontend.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')


/** struct fc0011_config - fc0011 hardware config
 *
 * @i2c_address: I2C bus address.
 */
struct fc0011_config {
	u8 i2c_address;
};

/** enum fc0011_fe_callback_commands - Frontend callbacks
 *
 * @FC0011_FE_CALLBACK_POWER: Power on tuner hardware.
 * @FC0011_FE_CALLBACK_RESET: Request a tuner reset.
 */
enum fc0011_fe_callback_commands {
	FC0011_FE_CALLBACK_POWER,
	FC0011_FE_CALLBACK_RESET,
};

#if IS_REACHABLE(CONFIG_MEDIA_TUNER_FC0011)
struct dvb_frontend *fc0011_attach(struct dvb_frontend *fe,
				   struct i2c_adapter *i2c,
				   const struct fc0011_config *config);
#else
static inline
struct dvb_frontend *fc0011_attach(struct dvb_frontend *fe,
				   struct i2c_adapter *i2c,
				   const struct fc0011_config *config)
{
	dev_err(&i2c->dev, "fc0011 driver disabled in Kconfig\n");
	return NULL;
}
#endif

#endif /* LINUX_FC0011_H_ */
