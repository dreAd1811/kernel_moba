/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __NVKM_SW_CHAN_H__
#define __NVKM_SW_CHAN_H__
#define nvkm_sw_chan(p) container_of((p), struct nvkm_sw_chan, object)
<<<<<<< HEAD
#include <core/object.h>
#include <core/event.h>

#include "priv.h"
=======
#include "priv.h"
#include <core/event.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct nvkm_sw_chan {
	const struct nvkm_sw_chan_func *func;
	struct nvkm_object object;
	struct nvkm_sw *sw;
	struct nvkm_fifo_chan *fifo;
	struct list_head head;

	struct nvkm_event event;
};

struct nvkm_sw_chan_func {
	void *(*dtor)(struct nvkm_sw_chan *);
	bool (*mthd)(struct nvkm_sw_chan *, int subc, u32 mthd, u32 data);
};

int nvkm_sw_chan_ctor(const struct nvkm_sw_chan_func *, struct nvkm_sw *,
		      struct nvkm_fifo_chan *, const struct nvkm_oclass *,
		      struct nvkm_sw_chan *);
bool nvkm_sw_chan_mthd(struct nvkm_sw_chan *, int subc, u32 mthd, u32 data);
#endif
