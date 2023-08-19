<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Hugues Fruchet <hugues.fruchet@st.com>
 *          Fabrice Lecoultre <fabrice.lecoultre@st.com>
 *          for STMicroelectronics.
<<<<<<< HEAD
=======
 * License terms:  GNU General Public License (GPL), version 2
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef DELTA_DEBUG_H
#define DELTA_DEBUG_H

char *delta_streaminfo_str(struct delta_streaminfo *s, char *str,
			   unsigned int len);
char *delta_frameinfo_str(struct delta_frameinfo *f, char *str,
			  unsigned int len);
void delta_trace_summary(struct delta_ctx *ctx);

#endif /* DELTA_DEBUG_H */
