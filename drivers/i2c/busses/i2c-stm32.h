<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * i2c-stm32.h
 *
 * Copyright (C) M'boumba Cedric Madianga 2017
<<<<<<< HEAD
 * Copyright (C) STMicroelectronics 2017
 * Author: M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 *
=======
 * Author: M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 *
 * License terms:  GNU General Public License (GPL), version 2
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef _I2C_STM32_H
#define _I2C_STM32_H

<<<<<<< HEAD
#include <linux/dma-direction.h>
#include <linux/dmaengine.h>
#include <linux/dma-mapping.h>

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
enum stm32_i2c_speed {
	STM32_I2C_SPEED_STANDARD, /* 100 kHz */
	STM32_I2C_SPEED_FAST, /* 400 kHz */
	STM32_I2C_SPEED_FAST_PLUS, /* 1 MHz */
	STM32_I2C_SPEED_END,
};

<<<<<<< HEAD
/**
 * struct stm32_i2c_dma - DMA specific data
 * @chan_tx: dma channel for TX transfer
 * @chan_rx: dma channel for RX transfer
 * @chan_using: dma channel used for the current transfer (TX or RX)
 * @dma_buf: dma buffer
 * @dma_len: dma buffer len
 * @dma_transfer_dir: dma transfer direction indicator
 * @dma_data_dir: dma transfer mode indicator
 * @dma_complete: dma transfer completion
 */
struct stm32_i2c_dma {
	struct dma_chan *chan_tx;
	struct dma_chan *chan_rx;
	struct dma_chan *chan_using;
	dma_addr_t dma_buf;
	unsigned int dma_len;
	enum dma_transfer_direction dma_transfer_dir;
	enum dma_data_direction dma_data_dir;
	struct completion dma_complete;
};

struct stm32_i2c_dma *stm32_i2c_dma_request(struct device *dev,
					    dma_addr_t phy_addr,
					    u32 txdr_offset, u32 rxdr_offset);

void stm32_i2c_dma_free(struct stm32_i2c_dma *dma);

int stm32_i2c_prep_dma_xfer(struct device *dev, struct stm32_i2c_dma *dma,
			    bool rd_wr, u32 len, u8 *buf,
			    dma_async_tx_callback callback,
			    void *dma_async_param);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* _I2C_STM32_H */
