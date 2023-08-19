/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _TDA18271C2DD_H_
#define _TDA18271C2DD_H_

#if IS_REACHABLE(CONFIG_DVB_TDA18271C2DD)
struct dvb_frontend *tda18271c2dd_attach(struct dvb_frontend *fe,
					 struct i2c_adapter *i2c, u8 adr);
#else
static inline struct dvb_frontend *tda18271c2dd_attach(struct dvb_frontend *fe,
					 struct i2c_adapter *i2c, u8 adr)
{
<<<<<<< HEAD
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
=======
        printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
        return NULL;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
#endif

#endif
