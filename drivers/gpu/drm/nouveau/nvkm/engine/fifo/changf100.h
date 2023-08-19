/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __GF100_FIFO_CHAN_H__
#define __GF100_FIFO_CHAN_H__
#define gf100_fifo_chan(p) container_of((p), struct gf100_fifo_chan, base)
#include "chan.h"
#include "gf100.h"

struct gf100_fifo_chan {
	struct nvkm_fifo_chan base;
	struct gf100_fifo *fifo;

	struct list_head head;
	bool killed;

<<<<<<< HEAD
	struct {
		struct nvkm_gpuobj *inst;
		struct nvkm_vma *vma;
=======
	struct nvkm_gpuobj *pgd;
	struct nvkm_vm *vm;

	struct {
		struct nvkm_gpuobj *inst;
		struct nvkm_vma vma;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	} engn[NVKM_SUBDEV_NR];
};

extern const struct nvkm_fifo_chan_oclass gf100_fifo_gpfifo_oclass;
#endif
