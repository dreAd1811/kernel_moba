/*
<<<<<<< HEAD
 * vcnl4000.c - Support for Vishay VCNL4000/4010/4020/4200 combined ambient
=======
 * vcnl4000.c - Support for Vishay VCNL4000/4010/4020 combined ambient
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * light and proximity sensor
 *
 * Copyright 2012 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * This file is subject to the terms and conditions of version 2 of
 * the GNU General Public License.  See the file COPYING in the main
 * directory of this archive for more details.
 *
<<<<<<< HEAD
 * IIO driver for:
 *   VCNL4000/10/20 (7-bit I2C slave address 0x13)
 *   VCNL4200 (7-bit I2C slave address 0x51)
=======
 * IIO driver for VCNL4000 (7-bit I2C slave address 0x13)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * TODO:
 *   allow to adjust IR current
 *   proximity threshold and event handling
 *   periodic ALS/proximity measurement (VCNL4010/20)
<<<<<<< HEAD
 *   interrupts (VCNL4010/20, VCNL4200)
=======
 *   interrupts (VCNL4010/20)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/delay.h>

#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>

#define VCNL4000_DRV_NAME "vcnl4000"
<<<<<<< HEAD
#define VCNL4000_PROD_ID	0x01
#define VCNL4010_PROD_ID	0x02 /* for VCNL4020, VCNL4010 */
#define VCNL4200_PROD_ID	0x58
=======
#define VCNL4000_ID		0x01
#define VCNL4010_ID		0x02 /* for VCNL4020, VCNL4010 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define VCNL4000_COMMAND	0x80 /* Command register */
#define VCNL4000_PROD_REV	0x81 /* Product ID and Revision ID */
#define VCNL4000_LED_CURRENT	0x83 /* IR LED current for proximity mode */
#define VCNL4000_AL_PARAM	0x84 /* Ambient light parameter register */
#define VCNL4000_AL_RESULT_HI	0x85 /* Ambient light result register, MSB */
#define VCNL4000_AL_RESULT_LO	0x86 /* Ambient light result register, LSB */
#define VCNL4000_PS_RESULT_HI	0x87 /* Proximity result register, MSB */
#define VCNL4000_PS_RESULT_LO	0x88 /* Proximity result register, LSB */
#define VCNL4000_PS_MEAS_FREQ	0x89 /* Proximity test signal frequency */
#define VCNL4000_PS_MOD_ADJ	0x8a /* Proximity modulator timing adjustment */

<<<<<<< HEAD
#define VCNL4200_AL_CONF	0x00 /* Ambient light configuration */
#define VCNL4200_PS_CONF1	0x03 /* Proximity configuration */
#define VCNL4200_PS_DATA	0x08 /* Proximity data */
#define VCNL4200_AL_DATA	0x09 /* Ambient light data */
#define VCNL4200_DEV_ID		0x0e /* Device ID, slave address and version */

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/* Bit masks for COMMAND register */
#define VCNL4000_AL_RDY		BIT(6) /* ALS data ready? */
#define VCNL4000_PS_RDY		BIT(5) /* proximity data ready? */
#define VCNL4000_AL_OD		BIT(4) /* start on-demand ALS measurement */
#define VCNL4000_PS_OD		BIT(3) /* start on-demand proximity measurement */

<<<<<<< HEAD
enum vcnl4000_device_ids {
	VCNL4000,
	VCNL4010,
	VCNL4200,
};

struct vcnl4200_channel {
	u8 reg;
	ktime_t last_measurement;
	ktime_t sampling_rate;
	struct mutex lock;
};

struct vcnl4000_data {
	struct i2c_client *client;
	enum vcnl4000_device_ids id;
	int rev;
	int al_scale;
	const struct vcnl4000_chip_spec *chip_spec;
	struct mutex vcnl4000_lock;
	struct vcnl4200_channel vcnl4200_al;
	struct vcnl4200_channel vcnl4200_ps;
};

struct vcnl4000_chip_spec {
	const char *prod;
	int (*init)(struct vcnl4000_data *data);
	int (*measure_light)(struct vcnl4000_data *data, int *val);
	int (*measure_proximity)(struct vcnl4000_data *data, int *val);
};

static const struct i2c_device_id vcnl4000_id[] = {
	{ "vcnl4000", VCNL4000 },
	{ "vcnl4010", VCNL4010 },
	{ "vcnl4020", VCNL4010 },
	{ "vcnl4200", VCNL4200 },
=======
struct vcnl4000_data {
	struct i2c_client *client;
	struct mutex lock;
};

static const struct i2c_device_id vcnl4000_id[] = {
	{ "vcnl4000", 0 },
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	{ }
};
MODULE_DEVICE_TABLE(i2c, vcnl4000_id);

<<<<<<< HEAD
static int vcnl4000_init(struct vcnl4000_data *data)
{
	int ret, prod_id;

	ret = i2c_smbus_read_byte_data(data->client, VCNL4000_PROD_REV);
	if (ret < 0)
		return ret;

	prod_id = ret >> 4;
	switch (prod_id) {
	case VCNL4000_PROD_ID:
		if (data->id != VCNL4000)
			dev_warn(&data->client->dev,
					"wrong device id, use vcnl4000");
		break;
	case VCNL4010_PROD_ID:
		if (data->id != VCNL4010)
			dev_warn(&data->client->dev,
					"wrong device id, use vcnl4010/4020");
		break;
	default:
		return -ENODEV;
	}

	data->rev = ret & 0xf;
	data->al_scale = 250000;
	mutex_init(&data->vcnl4000_lock);

	return 0;
};

static int vcnl4200_init(struct vcnl4000_data *data)
{
	int ret;

	ret = i2c_smbus_read_word_data(data->client, VCNL4200_DEV_ID);
	if (ret < 0)
		return ret;

	if ((ret & 0xff) != VCNL4200_PROD_ID)
		return -ENODEV;

	data->rev = (ret >> 8) & 0xf;

	/* Set defaults and enable both channels */
	ret = i2c_smbus_write_byte_data(data->client, VCNL4200_AL_CONF, 0x00);
	if (ret < 0)
		return ret;
	ret = i2c_smbus_write_byte_data(data->client, VCNL4200_PS_CONF1, 0x00);
	if (ret < 0)
		return ret;

	data->al_scale = 24000;
	data->vcnl4200_al.reg = VCNL4200_AL_DATA;
	data->vcnl4200_ps.reg = VCNL4200_PS_DATA;
	/* Integration time is 50ms, but the experiments show 54ms in total. */
	data->vcnl4200_al.sampling_rate = ktime_set(0, 54000 * 1000);
	data->vcnl4200_ps.sampling_rate = ktime_set(0, 4200 * 1000);
	data->vcnl4200_al.last_measurement = ktime_set(0, 0);
	data->vcnl4200_ps.last_measurement = ktime_set(0, 0);
	mutex_init(&data->vcnl4200_al.lock);
	mutex_init(&data->vcnl4200_ps.lock);

	return 0;
};

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int vcnl4000_measure(struct vcnl4000_data *data, u8 req_mask,
				u8 rdy_mask, u8 data_reg, int *val)
{
	int tries = 20;
<<<<<<< HEAD
	__be16 buf;
	int ret;

	mutex_lock(&data->vcnl4000_lock);
=======
	int ret;

	mutex_lock(&data->lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	ret = i2c_smbus_write_byte_data(data->client, VCNL4000_COMMAND,
					req_mask);
	if (ret < 0)
		goto fail;

	/* wait for data to become ready */
	while (tries--) {
		ret = i2c_smbus_read_byte_data(data->client, VCNL4000_COMMAND);
		if (ret < 0)
			goto fail;
		if (ret & rdy_mask)
			break;
		msleep(20); /* measurement takes up to 100 ms */
	}

	if (tries < 0) {
		dev_err(&data->client->dev,
			"vcnl4000_measure() failed, data not ready\n");
		ret = -EIO;
		goto fail;
	}

<<<<<<< HEAD
	ret = i2c_smbus_read_i2c_block_data(data->client,
		data_reg, sizeof(buf), (u8 *) &buf);
	if (ret < 0)
		goto fail;

	mutex_unlock(&data->vcnl4000_lock);
	*val = be16_to_cpu(buf);
=======
	ret = i2c_smbus_read_word_swapped(data->client, data_reg);
	if (ret < 0)
		goto fail;

	mutex_unlock(&data->lock);
	*val = ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;

fail:
<<<<<<< HEAD
	mutex_unlock(&data->vcnl4000_lock);
	return ret;
}

static int vcnl4200_measure(struct vcnl4000_data *data,
		struct vcnl4200_channel *chan, int *val)
{
	int ret;
	s64 delta;
	ktime_t next_measurement;

	mutex_lock(&chan->lock);

	next_measurement = ktime_add(chan->last_measurement,
			chan->sampling_rate);
	delta = ktime_us_delta(next_measurement, ktime_get());
	if (delta > 0)
		usleep_range(delta, delta + 500);
	chan->last_measurement = ktime_get();

	mutex_unlock(&chan->lock);

	ret = i2c_smbus_read_word_data(data->client, chan->reg);
	if (ret < 0)
		return ret;

	*val = ret;

	return 0;
}

static int vcnl4000_measure_light(struct vcnl4000_data *data, int *val)
{
	return vcnl4000_measure(data,
			VCNL4000_AL_OD, VCNL4000_AL_RDY,
			VCNL4000_AL_RESULT_HI, val);
}

static int vcnl4200_measure_light(struct vcnl4000_data *data, int *val)
{
	return vcnl4200_measure(data, &data->vcnl4200_al, val);
}

static int vcnl4000_measure_proximity(struct vcnl4000_data *data, int *val)
{
	return vcnl4000_measure(data,
			VCNL4000_PS_OD, VCNL4000_PS_RDY,
			VCNL4000_PS_RESULT_HI, val);
}

static int vcnl4200_measure_proximity(struct vcnl4000_data *data, int *val)
{
	return vcnl4200_measure(data, &data->vcnl4200_ps, val);
}

static const struct vcnl4000_chip_spec vcnl4000_chip_spec_cfg[] = {
	[VCNL4000] = {
		.prod = "VCNL4000",
		.init = vcnl4000_init,
		.measure_light = vcnl4000_measure_light,
		.measure_proximity = vcnl4000_measure_proximity,
	},
	[VCNL4010] = {
		.prod = "VCNL4010/4020",
		.init = vcnl4000_init,
		.measure_light = vcnl4000_measure_light,
		.measure_proximity = vcnl4000_measure_proximity,
	},
	[VCNL4200] = {
		.prod = "VCNL4200",
		.init = vcnl4200_init,
		.measure_light = vcnl4200_measure_light,
		.measure_proximity = vcnl4200_measure_proximity,
	},
};

=======
	mutex_unlock(&data->lock);
	return ret;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static const struct iio_chan_spec vcnl4000_channels[] = {
	{
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
	}, {
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	}
};

static int vcnl4000_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	int ret;
	struct vcnl4000_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_LIGHT:
<<<<<<< HEAD
			ret = data->chip_spec->measure_light(data, val);
=======
			ret = vcnl4000_measure(data,
				VCNL4000_AL_OD, VCNL4000_AL_RDY,
				VCNL4000_AL_RESULT_HI, val);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			if (ret < 0)
				return ret;
			return IIO_VAL_INT;
		case IIO_PROXIMITY:
<<<<<<< HEAD
			ret = data->chip_spec->measure_proximity(data, val);
=======
			ret = vcnl4000_measure(data,
				VCNL4000_PS_OD, VCNL4000_PS_RDY,
				VCNL4000_PS_RESULT_HI, val);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			if (ret < 0)
				return ret;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		if (chan->type != IIO_LIGHT)
			return -EINVAL;

		*val = 0;
<<<<<<< HEAD
		*val2 = data->al_scale;
=======
		*val2 = 250000;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}

static const struct iio_info vcnl4000_info = {
	.read_raw = vcnl4000_read_raw,
<<<<<<< HEAD
=======
	.driver_module = THIS_MODULE,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static int vcnl4000_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct vcnl4000_data *data;
	struct iio_dev *indio_dev;
<<<<<<< HEAD
	int ret;
=======
	int ret, prod_id;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
<<<<<<< HEAD
	data->id = id->driver_data;
	data->chip_spec = &vcnl4000_chip_spec_cfg[data->id];

	ret = data->chip_spec->init(data);
	if (ret < 0)
		return ret;

	dev_dbg(&client->dev, "%s Ambient light/proximity sensor, Rev: %02x\n",
		data->chip_spec->prod, data->rev);
=======
	mutex_init(&data->lock);

	ret = i2c_smbus_read_byte_data(data->client, VCNL4000_PROD_REV);
	if (ret < 0)
		return ret;

	prod_id = ret >> 4;
	if (prod_id != VCNL4010_ID && prod_id != VCNL4000_ID)
		return -ENODEV;

	dev_dbg(&client->dev, "%s Ambient light/proximity sensor, Rev: %02x\n",
		(prod_id == VCNL4010_ID) ? "VCNL4010/4020" : "VCNL4000",
		ret & 0xf);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &vcnl4000_info;
	indio_dev->channels = vcnl4000_channels;
	indio_dev->num_channels = ARRAY_SIZE(vcnl4000_channels);
	indio_dev->name = VCNL4000_DRV_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;

	return devm_iio_device_register(&client->dev, indio_dev);
}

static struct i2c_driver vcnl4000_driver = {
	.driver = {
		.name   = VCNL4000_DRV_NAME,
	},
	.probe  = vcnl4000_probe,
	.id_table = vcnl4000_id,
};

module_i2c_driver(vcnl4000_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Vishay VCNL4000 proximity/ambient light sensor driver");
MODULE_LICENSE("GPL");
