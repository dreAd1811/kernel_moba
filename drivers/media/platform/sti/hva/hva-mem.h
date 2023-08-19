<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
<<<<<<< HEAD
=======
 * License terms:  GNU General Public License (GPL), version 2
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef HVA_MEM_H
#define HVA_MEM_H

/**
 * struct hva_buffer - hva buffer
 *
 * @name:  name of requester
 * @paddr: physical address (for hardware)
 * @vaddr: virtual address (kernel can read/write)
 * @size:  size of buffer
 */
struct hva_buffer {
	const char		*name;
	dma_addr_t		paddr;
	void			*vaddr;
	u32			size;
};

int hva_mem_alloc(struct hva_ctx *ctx,
		  __u32 size,
		  const char *name,
		  struct hva_buffer **buf);

void hva_mem_free(struct hva_ctx *ctx,
		  struct hva_buffer *buf);

#endif /* HVA_MEM_H */
