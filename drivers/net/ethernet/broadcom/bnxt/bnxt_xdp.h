/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2016-2017 Broadcom Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#ifndef BNXT_XDP_H
#define BNXT_XDP_H

void bnxt_xmit_xdp(struct bnxt *bp, struct bnxt_tx_ring_info *txr,
		   dma_addr_t mapping, u32 len, u16 rx_prod);
void bnxt_tx_int_xdp(struct bnxt *bp, struct bnxt_napi *bnapi, int nr_pkts);
bool bnxt_rx_xdp(struct bnxt *bp, struct bnxt_rx_ring_info *rxr, u16 cons,
		 struct page *page, u8 **data_ptr, unsigned int *len,
		 u8 *event);
<<<<<<< HEAD
int bnxt_xdp(struct net_device *dev, struct netdev_bpf *xdp);
=======
int bnxt_xdp(struct net_device *dev, struct netdev_xdp *xdp);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif
