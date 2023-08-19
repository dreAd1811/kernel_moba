<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Author: Hugues Fruchet <hugues.fruchet@st.com> for STMicroelectronics.
=======
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Author: Hugues Fruchet <hugues.fruchet@st.com> for STMicroelectronics.
 * License terms:  GNU General Public License (GPL), version 2
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef DELTA_MEM_H
#define DELTA_MEM_H

int hw_alloc(struct delta_ctx *ctx, u32 size, const char *name,
	     struct delta_buf *buf);
void hw_free(struct delta_ctx *ctx, struct delta_buf *buf);

#endif /* DELTA_MEM_H */
