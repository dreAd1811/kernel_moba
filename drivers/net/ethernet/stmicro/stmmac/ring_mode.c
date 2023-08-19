/*******************************************************************************
  Specialised functions for managing Ring mode

  Copyright(C) 2011  STMicroelectronics Ltd

  It defines all the functions used to handle the normal/enhanced
  descriptors in case of the DMA is configured to work in chained or
  in ring mode.

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#include "stmmac.h"

<<<<<<< HEAD
static int jumbo_frm(void *p, struct sk_buff *skb, int csum)
=======
static int stmmac_jumbo_frm(void *p, struct sk_buff *skb, int csum)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct stmmac_tx_queue *tx_q = (struct stmmac_tx_queue *)p;
	unsigned int nopaged_len = skb_headlen(skb);
	struct stmmac_priv *priv = tx_q->priv_data;
	unsigned int entry = tx_q->cur_tx;
	unsigned int bmax, len, des2;
	struct dma_desc *desc;

	if (priv->extend_desc)
		desc = (struct dma_desc *)(tx_q->dma_etx + entry);
	else
		desc = tx_q->dma_tx + entry;

	if (priv->plat->enh_desc)
		bmax = BUF_SIZE_8KiB;
	else
		bmax = BUF_SIZE_2KiB;

	len = nopaged_len - bmax;

	if (nopaged_len > BUF_SIZE_8KiB) {

<<<<<<< HEAD
		des2 = dma_map_single(priv->device, skb->data, bmax,
				      DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(priv->device, des2))
=======
		des2 = dma_map_single(GET_MEM_PDEV_DEV, skb->data, bmax,
				      DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(GET_MEM_PDEV_DEV, des2))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			return -1;

		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = bmax;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;

		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
<<<<<<< HEAD
		stmmac_prepare_tx_desc(priv, desc, 1, bmax, csum,
				STMMAC_RING_MODE, 1, false, skb->len);
=======
		priv->hw->desc->prepare_tx_desc(desc, 1, bmax, csum,
						STMMAC_RING_MODE, 0,
						false, skb->len);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		tx_q->tx_skbuff[entry] = NULL;
		entry = STMMAC_GET_ENTRY(entry, DMA_TX_SIZE);

		if (priv->extend_desc)
			desc = (struct dma_desc *)(tx_q->dma_etx + entry);
		else
			desc = tx_q->dma_tx + entry;

<<<<<<< HEAD
		des2 = dma_map_single(priv->device, skb->data + bmax, len,
				      DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(priv->device, des2))
=======
		des2 = dma_map_single(GET_MEM_PDEV_DEV, skb->data + bmax, len,
				      DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(GET_MEM_PDEV_DEV, des2))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			return -1;
		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = len;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;

		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
<<<<<<< HEAD
		stmmac_prepare_tx_desc(priv, desc, 0, len, csum,
				STMMAC_RING_MODE, 1, true, skb->len);
	} else {
		des2 = dma_map_single(priv->device, skb->data,
				      nopaged_len, DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(priv->device, des2))
=======
		priv->hw->desc->prepare_tx_desc(desc, 0, len, csum,
						STMMAC_RING_MODE, 1,
						true, skb->len);
	} else {
		des2 = dma_map_single(GET_MEM_PDEV_DEV, skb->data,
				      nopaged_len, DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(GET_MEM_PDEV_DEV, des2))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			return -1;
		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = nopaged_len;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;
		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
<<<<<<< HEAD
		stmmac_prepare_tx_desc(priv, desc, 1, nopaged_len, csum,
				STMMAC_RING_MODE, 1, true, skb->len);
=======
		priv->hw->desc->prepare_tx_desc(desc, 1, nopaged_len, csum,
						STMMAC_RING_MODE, 0,
						true, skb->len);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	tx_q->cur_tx = entry;

	return entry;
}

<<<<<<< HEAD
static unsigned int is_jumbo_frm(int len, int enh_desc)
=======
static unsigned int stmmac_is_jumbo_frm(int len, int enh_desc)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	unsigned int ret = 0;

	if (len >= BUF_SIZE_4KiB)
		ret = 1;

	return ret;
}

<<<<<<< HEAD
static void refill_desc3(void *priv_ptr, struct dma_desc *p)
=======
static void stmmac_refill_desc3(void *priv_ptr, struct dma_desc *p)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct stmmac_rx_queue *rx_q = priv_ptr;
	struct stmmac_priv *priv = rx_q->priv_data;

	/* Fill DES3 in case of RING mode */
	if (priv->dma_buf_sz == BUF_SIZE_16KiB)
		p->des3 = cpu_to_le32(le32_to_cpu(p->des2) + BUF_SIZE_8KiB);
}

/* In ring mode we need to fill the desc3 because it is used as buffer */
<<<<<<< HEAD
static void init_desc3(struct dma_desc *p)
=======
static void stmmac_init_desc3(struct dma_desc *p)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	p->des3 = cpu_to_le32(le32_to_cpu(p->des2) + BUF_SIZE_8KiB);
}

<<<<<<< HEAD
static void clean_desc3(void *priv_ptr, struct dma_desc *p)
=======
static void stmmac_clean_desc3(void *priv_ptr, struct dma_desc *p)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct stmmac_tx_queue *tx_q = (struct stmmac_tx_queue *)priv_ptr;
	struct stmmac_priv *priv = tx_q->priv_data;
	unsigned int entry = tx_q->dirty_tx;

	/* des3 is only used for jumbo frames tx or time stamping */
	if (unlikely(tx_q->tx_skbuff_dma[entry].is_jumbo ||
		     (tx_q->tx_skbuff_dma[entry].last_segment &&
		      !priv->extend_desc && priv->hwts_tx_en)))
		p->des3 = 0;
}

<<<<<<< HEAD
static int set_16kib_bfsize(int mtu)
=======
static int stmmac_set_16kib_bfsize(int mtu)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	int ret = 0;
	if (unlikely(mtu > BUF_SIZE_8KiB))
		ret = BUF_SIZE_16KiB;
	return ret;
}

const struct stmmac_mode_ops ring_mode_ops = {
<<<<<<< HEAD
	.is_jumbo_frm = is_jumbo_frm,
	.jumbo_frm = jumbo_frm,
	.refill_desc3 = refill_desc3,
	.init_desc3 = init_desc3,
	.clean_desc3 = clean_desc3,
	.set_16kib_bfsize = set_16kib_bfsize,
=======
	.is_jumbo_frm = stmmac_is_jumbo_frm,
	.jumbo_frm = stmmac_jumbo_frm,
	.refill_desc3 = stmmac_refill_desc3,
	.init_desc3 = stmmac_init_desc3,
	.clean_desc3 = stmmac_clean_desc3,
	.set_16kib_bfsize = stmmac_set_16kib_bfsize,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};
