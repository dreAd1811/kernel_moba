/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __PVRUSB2_DVB_H__
#define __PVRUSB2_DVB_H__

<<<<<<< HEAD
#include <media/dvb_frontend.h>
#include <media/dvb_demux.h>
#include <media/dvb_net.h>
#include <media/dmxdev.h>
=======
#include "dvb_frontend.h"
#include "dvb_demux.h"
#include "dvb_net.h"
#include "dmxdev.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "pvrusb2-context.h"

#define PVR2_DVB_BUFFER_COUNT 32
#define PVR2_DVB_BUFFER_SIZE PAGE_ALIGN(0x4000)

struct pvr2_dvb_adapter {
	struct pvr2_channel	channel;

	struct dvb_adapter	dvb_adap;
	struct dmxdev		dmxdev;
	struct dvb_demux	demux;
	struct dvb_net		dvb_net;
	struct dvb_frontend	*fe;

	int			feedcount;
	int			max_feed_count;

	struct task_struct	*thread;
	struct mutex		lock;

	unsigned int		stream_run:1;

	wait_queue_head_t	buffer_wait_data;
	char			*buffer_storage[PVR2_DVB_BUFFER_COUNT];
};

struct pvr2_dvb_props {
	int (*frontend_attach) (struct pvr2_dvb_adapter *);
	int (*tuner_attach) (struct pvr2_dvb_adapter *);
};

struct pvr2_dvb_adapter *pvr2_dvb_create(struct pvr2_context *pvr);

#endif /* __PVRUSB2_DVB_H__ */
