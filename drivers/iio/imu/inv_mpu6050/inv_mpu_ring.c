/*
* Copyright (C) 2012 Invensense, Inc.
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/sysfs.h>
#include <linux/jiffies.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
<<<<<<< HEAD
#include <linux/poll.h>
#include <linux/math64.h>
#include <asm/unaligned.h>
#include "inv_mpu_iio.h"

/**
 *  inv_mpu6050_update_period() - Update chip internal period estimation
 *
 *  @st:		driver state
 *  @timestamp:		the interrupt timestamp
 *  @nb:		number of data set in the fifo
 *
 *  This function uses interrupt timestamps to estimate the chip period and
 *  to choose the data timestamp to come.
 */
static void inv_mpu6050_update_period(struct inv_mpu6050_state *st,
				      s64 timestamp, size_t nb)
{
	/* Period boundaries for accepting timestamp */
	const s64 period_min =
		(NSEC_PER_MSEC * (100 - INV_MPU6050_TS_PERIOD_JITTER)) / 100;
	const s64 period_max =
		(NSEC_PER_MSEC * (100 + INV_MPU6050_TS_PERIOD_JITTER)) / 100;
	const s32 divider = INV_MPU6050_FREQ_DIVIDER(st);
	s64 delta, interval;
	bool use_it_timestamp = false;

	if (st->it_timestamp == 0) {
		/* not initialized, forced to use it_timestamp */
		use_it_timestamp = true;
	} else if (nb == 1) {
		/*
		 * Validate the use of it timestamp by checking if interrupt
		 * has been delayed.
		 * nb > 1 means interrupt was delayed for more than 1 sample,
		 * so it's obviously not good.
		 * Compute the chip period between 2 interrupts for validating.
		 */
		delta = div_s64(timestamp - st->it_timestamp, divider);
		if (delta > period_min && delta < period_max) {
			/* update chip period and use it timestamp */
			st->chip_period = (st->chip_period + delta) / 2;
			use_it_timestamp = true;
		}
	}

	if (use_it_timestamp) {
		/*
		 * Manage case of multiple samples in the fifo (nb > 1):
		 * compute timestamp corresponding to the first sample using
		 * estimated chip period.
		 */
		interval = (nb - 1) * st->chip_period * divider;
		st->data_timestamp = timestamp - interval;
	}

	/* save it timestamp */
	st->it_timestamp = timestamp;
}

/**
 *  inv_mpu6050_get_timestamp() - Return the current data timestamp
 *
 *  @st:		driver state
 *  @return:		current data timestamp
 *
 *  This function returns the current data timestamp and prepares for next one.
 */
static s64 inv_mpu6050_get_timestamp(struct inv_mpu6050_state *st)
{
	s64 ts;

	/* return current data timestamp and increment */
	ts = st->data_timestamp;
	st->data_timestamp += st->chip_period * INV_MPU6050_FREQ_DIVIDER(st);

	return ts;
=======
#include <linux/kfifo.h>
#include <linux/poll.h>
#include "inv_mpu_iio.h"

static void inv_clear_kfifo(struct inv_mpu6050_state *st)
{
	unsigned long flags;

	/* take the spin lock sem to avoid interrupt kick in */
	spin_lock_irqsave(&st->time_stamp_lock, flags);
	kfifo_reset(&st->timestamps);
	spin_unlock_irqrestore(&st->time_stamp_lock, flags);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

int inv_reset_fifo(struct iio_dev *indio_dev)
{
	int result;
	u8 d;
	struct inv_mpu6050_state  *st = iio_priv(indio_dev);

<<<<<<< HEAD
	/* reset it timestamp validation */
	st->it_timestamp = 0;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* disable interrupt */
	result = regmap_write(st->map, st->reg->int_enable, 0);
	if (result) {
		dev_err(regmap_get_device(st->map), "int_enable failed %d\n",
			result);
		return result;
	}
	/* disable the sensor output to FIFO */
	result = regmap_write(st->map, st->reg->fifo_en, 0);
	if (result)
		goto reset_fifo_fail;
	/* disable fifo reading */
<<<<<<< HEAD
	result = regmap_write(st->map, st->reg->user_ctrl,
			      st->chip_config.user_ctrl);
=======
	result = regmap_write(st->map, st->reg->user_ctrl, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (result)
		goto reset_fifo_fail;

	/* reset FIFO*/
<<<<<<< HEAD
	d = st->chip_config.user_ctrl | INV_MPU6050_BIT_FIFO_RST;
	result = regmap_write(st->map, st->reg->user_ctrl, d);
	if (result)
		goto reset_fifo_fail;

=======
	result = regmap_write(st->map, st->reg->user_ctrl,
			      INV_MPU6050_BIT_FIFO_RST);
	if (result)
		goto reset_fifo_fail;

	/* clear timestamps fifo */
	inv_clear_kfifo(st);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* enable interrupt */
	if (st->chip_config.accl_fifo_enable ||
	    st->chip_config.gyro_fifo_enable) {
		result = regmap_write(st->map, st->reg->int_enable,
				      INV_MPU6050_BIT_DATA_RDY_EN);
		if (result)
			return result;
	}
<<<<<<< HEAD
	/* enable FIFO reading */
	d = st->chip_config.user_ctrl | INV_MPU6050_BIT_FIFO_EN;
	result = regmap_write(st->map, st->reg->user_ctrl, d);
=======
	/* enable FIFO reading and I2C master interface*/
	result = regmap_write(st->map, st->reg->user_ctrl,
			      INV_MPU6050_BIT_FIFO_EN);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (result)
		goto reset_fifo_fail;
	/* enable sensor output to FIFO */
	d = 0;
	if (st->chip_config.gyro_fifo_enable)
		d |= INV_MPU6050_BITS_GYRO_OUT;
	if (st->chip_config.accl_fifo_enable)
		d |= INV_MPU6050_BIT_ACCEL_OUT;
	result = regmap_write(st->map, st->reg->fifo_en, d);
	if (result)
		goto reset_fifo_fail;

	return 0;

reset_fifo_fail:
	dev_err(regmap_get_device(st->map), "reset fifo failed %d\n", result);
	result = regmap_write(st->map, st->reg->int_enable,
			      INV_MPU6050_BIT_DATA_RDY_EN);

	return result;
}

/**
<<<<<<< HEAD
=======
 * inv_mpu6050_irq_handler() - Cache a timestamp at each data ready interrupt.
 */
irqreturn_t inv_mpu6050_irq_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct inv_mpu6050_state *st = iio_priv(indio_dev);
	s64 timestamp;

	timestamp = iio_get_time_ns(indio_dev);
	kfifo_in_spinlocked(&st->timestamps, &timestamp, 1,
			    &st->time_stamp_lock);

	return IRQ_WAKE_THREAD;
}

/**
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * inv_mpu6050_read_fifo() - Transfer data from hardware FIFO to KFIFO.
 */
irqreturn_t inv_mpu6050_read_fifo(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct inv_mpu6050_state *st = iio_priv(indio_dev);
	size_t bytes_per_datum;
	int result;
	u8 data[INV_MPU6050_OUTPUT_DATA_SIZE];
	u16 fifo_count;
	s64 timestamp;
<<<<<<< HEAD
	int int_status;
	size_t i, nb;

	mutex_lock(&st->lock);

	/* ack interrupt and check status */
	result = regmap_read(st->map, st->reg->int_status, &int_status);
	if (result) {
		dev_err(regmap_get_device(st->map),
			"failed to ack interrupt\n");
		goto flush_fifo;
	}
	/* handle fifo overflow by reseting fifo */
	if (int_status & INV_MPU6050_BIT_FIFO_OVERFLOW_INT)
		goto flush_fifo;
	if (!(int_status & INV_MPU6050_BIT_RAW_DATA_RDY_INT)) {
		dev_warn(regmap_get_device(st->map),
			"spurious interrupt with status 0x%x\n", int_status);
		goto end_session;
	}

=======

	mutex_lock(&st->lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!(st->chip_config.accl_fifo_enable |
		st->chip_config.gyro_fifo_enable))
		goto end_session;
	bytes_per_datum = 0;
	if (st->chip_config.accl_fifo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_3AXIS_SENSOR;

	if (st->chip_config.gyro_fifo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_3AXIS_SENSOR;

	/*
<<<<<<< HEAD
	 * read fifo_count register to know how many bytes are inside the FIFO
=======
	 * read fifo_count register to know how many bytes inside FIFO
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	 * right now
	 */
	result = regmap_bulk_read(st->map, st->reg->fifo_count_h, data,
				  INV_MPU6050_FIFO_COUNT_BYTE);
	if (result)
		goto end_session;
<<<<<<< HEAD
	fifo_count = get_unaligned_be16(&data[0]);
	/* compute and process all complete datum */
	nb = fifo_count / bytes_per_datum;
	inv_mpu6050_update_period(st, pf->timestamp, nb);
	for (i = 0; i < nb; ++i) {
=======
	fifo_count = be16_to_cpup((__be16 *)(&data[0]));
	if (fifo_count < bytes_per_datum)
		goto end_session;
	/* fifo count can't be odd number, if it is odd, reset fifo*/
	if (fifo_count & 1)
		goto flush_fifo;
	if (fifo_count >  INV_MPU6050_FIFO_THRESHOLD)
		goto flush_fifo;
	/* Timestamp mismatch. */
	if (kfifo_len(&st->timestamps) >
	    fifo_count / bytes_per_datum + INV_MPU6050_TIME_STAMP_TOR)
		goto flush_fifo;
	while (fifo_count >= bytes_per_datum) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		result = regmap_bulk_read(st->map, st->reg->fifo_r_w,
					  data, bytes_per_datum);
		if (result)
			goto flush_fifo;
<<<<<<< HEAD
		/* skip first samples if needed */
		if (st->skip_samples) {
			st->skip_samples--;
			continue;
		}
		timestamp = inv_mpu6050_get_timestamp(st);
		iio_push_to_buffers_with_timestamp(indio_dev, data, timestamp);
=======

		result = kfifo_out(&st->timestamps, &timestamp, 1);
		/* when there is no timestamp, put timestamp as 0 */
		if (result == 0)
			timestamp = 0;

		result = iio_push_to_buffers_with_timestamp(indio_dev, data,
							    timestamp);
		if (result)
			goto flush_fifo;
		fifo_count -= bytes_per_datum;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

end_session:
	mutex_unlock(&st->lock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;

flush_fifo:
	/* Flush HW and SW FIFOs. */
	inv_reset_fifo(indio_dev);
	mutex_unlock(&st->lock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}
