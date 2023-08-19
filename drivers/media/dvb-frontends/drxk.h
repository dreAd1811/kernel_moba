/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _DRXK_H_
#define _DRXK_H_

#include <linux/types.h>
#include <linux/i2c.h>

/**
 * struct drxk_config - Configure the initial parameters for DRX-K
 *
 * @adr:		I2C address of the DRX-K
 * @parallel_ts:	True means that the device uses parallel TS,
<<<<<<< HEAD
 *			Serial otherwise.
=======
 * 			Serial otherwise.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @dynamic_clk:	True means that the clock will be dynamically
 *			adjusted. Static clock otherwise.
 * @enable_merr_cfg:	Enable SIO_PDR_PERR_CFG/SIO_PDR_MVAL_CFG.
 * @single_master:	Device is on the single master mode
 * @no_i2c_bridge:	Don't switch the I2C bridge to talk with tuner
 * @antenna_gpio:	GPIO bit used to control the antenna
 * @antenna_dvbt:	GPIO bit for changing antenna to DVB-C. A value of 1
 *			means that 1=DVBC, 0 = DVBT. Zero means the opposite.
 * @mpeg_out_clk_strength: DRXK Mpeg output clock drive strength.
<<<<<<< HEAD
 * @chunk_size:		maximum size for I2C messages
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @microcode_name:	Name of the firmware file with the microcode
 * @qam_demod_parameter_count:	The number of parameters used for the command
 *				to set the demodulator parameters. All
 *				firmwares are using the 2-parameter commmand.
<<<<<<< HEAD
 *				An exception is the ``drxk_a3.mc`` firmware,
=======
 *				An exception is the "drxk_a3.mc" firmware,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *				which uses the 4-parameter command.
 *				A value of 0 (default) or lower indicates that
 *				the correct number of parameters will be
 *				automatically detected.
 *
<<<<<<< HEAD
 * On the ``*_gpio`` vars, bit 0 is UIO-1, bit 1 is UIO-2 and bit 2 is
=======
 * On the *_gpio vars, bit 0 is UIO-1, bit 1 is UIO-2 and bit 2 is
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * UIO-3.
 */
struct drxk_config {
	u8	adr;
	bool	single_master;
	bool	no_i2c_bridge;
	bool	parallel_ts;
	bool	dynamic_clk;
	bool	enable_merr_cfg;

	bool	antenna_dvbt;
	u16	antenna_gpio;

	u8	mpeg_out_clk_strength;
	int	chunk_size;

	const char	*microcode_name;
	int		 qam_demod_parameter_count;
};

#if IS_REACHABLE(CONFIG_DVB_DRXK)
<<<<<<< HEAD
/**
 * Attach a drxk demod
 *
 * @config: pointer to &struct drxk_config with demod configuration.
 * @i2c: i2c adapter to use.
 *
 * return: FE pointer on success, NULL on failure.
 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
extern struct dvb_frontend *drxk_attach(const struct drxk_config *config,
					struct i2c_adapter *i2c);
#else
static inline struct dvb_frontend *drxk_attach(const struct drxk_config *config,
					struct i2c_adapter *i2c)
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
