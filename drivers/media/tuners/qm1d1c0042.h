<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Sharp QM1D1C0042 8PSK tuner driver
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
<<<<<<< HEAD
=======
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef QM1D1C0042_H
#define QM1D1C0042_H

<<<<<<< HEAD
#include <media/dvb_frontend.h>
=======
#include "dvb_frontend.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')


struct qm1d1c0042_config {
	struct dvb_frontend *fe;

	u32  xtal_freq;    /* [kHz] */ /* currently ignored */
	bool lpf;          /* enable LPF */
	bool fast_srch;    /* enable fast search mode, no LPF */
	u32  lpf_wait;         /* wait in tuning with LPF enabled. [ms] */
	u32  fast_srch_wait;   /* with fast-search mode, no LPF. [ms] */
	u32  normal_srch_wait; /* with no LPF/fast-search mode. [ms] */
};
/* special values indicating to use the default in qm1d1c0042_config */
#define QM1D1C0042_CFG_XTAL_DFLT 0
#define QM1D1C0042_CFG_WAIT_DFLT 0

#endif /* QM1D1C0042_H */
