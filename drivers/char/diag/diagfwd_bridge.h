<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (c) 2012-2014, 2017-2019, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2012-2014, 2017-2019, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef DIAGFWD_BRIDGE_H
#define DIAGFWD_BRIDGE_H

/*
 * Add Data channels at the top half and the DCI channels at the
 * bottom half of this list.
 */
#define DIAGFWD_MDM		0
<<<<<<< HEAD
#define DIAGFWD_MDM2		1
#define NUM_REMOTE_DATA_DEV	2
#define DIAGFWD_MDM_DCI		NUM_REMOTE_DATA_DEV
#define DIAGFWD_MDM_DCI_2	(NUM_REMOTE_DATA_DEV + 1)
#define NUM_REMOTE_DCI_DEV	(DIAGFWD_MDM_DCI_2 - NUM_REMOTE_DATA_DEV + 1)
=======
#define NUM_REMOTE_DATA_DEV	1
#define DIAGFWD_MDM_DCI		NUM_REMOTE_DATA_DEV
#define NUM_REMOTE_DCI_DEV	(DIAGFWD_MDM_DCI - NUM_REMOTE_DATA_DEV + 1)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define NUM_REMOTE_DEV		(NUM_REMOTE_DATA_DEV + NUM_REMOTE_DCI_DEV)

#define DIAG_BRIDGE_NAME_SZ	24
#define DIAG_BRIDGE_GET_NAME(x)	(bridge_info[x].name)

struct diag_remote_dev_ops {
<<<<<<< HEAD
	int (*open)(int id, int  ch);
	int (*close)(int id, int ch);
	int (*queue_read)(int id, int ch);
	int (*write)(int id, int ch, unsigned char *buf,
			int len, int ctxt);
	int (*fwd_complete)(int id, int ch, unsigned char *buf,
				int len, int ctxt);
	int (*remote_proc_check)(int id);
=======
	int (*open)(int id);
	int (*close)(int id);
	int (*queue_read)(int id);
	int (*write)(int id, unsigned char *buf, int len, int ctxt);
	int (*fwd_complete)(int id, unsigned char *buf, int len, int ctxt);
	int (*remote_proc_check)(void);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct diagfwd_bridge_info {
	int id;
	int type;
	int inited;
	int ctxt;
	char name[DIAG_BRIDGE_NAME_SZ];
	struct diag_remote_dev_ops *dev_ops;
	/* DCI related variables. These would be NULL for data channels */
	void *dci_read_ptr;
	unsigned char *dci_read_buf;
	int dci_read_len;
	struct workqueue_struct *dci_wq;
	struct work_struct dci_read_work;
};

extern struct diagfwd_bridge_info bridge_info[NUM_REMOTE_DEV];
<<<<<<< HEAD
int diagfwd_bridge_init(void);
void diagfwd_bridge_exit(void);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int diagfwd_bridge_close(int id);
int diagfwd_bridge_write(int id, unsigned char *buf, int len);
uint16_t diag_get_remote_device_mask(void);

/* The following functions must be called by Diag remote devices only. */
int diagfwd_bridge_register(int id, int ctxt, struct diag_remote_dev_ops *ops);
int diag_remote_dev_open(int id);
void diag_remote_dev_close(int id);
int diag_remote_dev_read_done(int id, unsigned char *buf, int len);
int diag_remote_dev_write_done(int id, unsigned char *buf, int len, int ctxt);
int diag_remote_init(void);
void diag_remote_exit(void);
<<<<<<< HEAD
=======
void diag_register_with_bridge(void);
void diag_unregister_bridge(void);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
