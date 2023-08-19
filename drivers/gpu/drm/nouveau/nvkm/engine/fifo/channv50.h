/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __NV50_FIFO_CHAN_H__
#define __NV50_FIFO_CHAN_H__
#define nv50_fifo_chan(p) container_of((p), struct nv50_fifo_chan, base)
#include "chan.h"
#include "nv50.h"

struct nv50_fifo_chan {
	struct nv50_fifo *fifo;
	struct nvkm_fifo_chan base;

	struct nvkm_gpuobj *ramfc;
	struct nvkm_gpuobj *cache;
	struct nvkm_gpuobj *eng;
	struct nvkm_gpuobj *pgd;
	struct nvkm_ramht *ramht;
<<<<<<< HEAD
=======
	struct nvkm_vm *vm;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	struct nvkm_gpuobj *engn[NVKM_SUBDEV_NR];
};

<<<<<<< HEAD
int nv50_fifo_chan_ctor(struct nv50_fifo *, u64 vmm, u64 push,
=======
int nv50_fifo_chan_ctor(struct nv50_fifo *, u64 vm, u64 push,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			const struct nvkm_oclass *, struct nv50_fifo_chan *);
void *nv50_fifo_chan_dtor(struct nvkm_fifo_chan *);
void nv50_fifo_chan_fini(struct nvkm_fifo_chan *);
void nv50_fifo_chan_engine_dtor(struct nvkm_fifo_chan *, struct nvkm_engine *);
void nv50_fifo_chan_object_dtor(struct nvkm_fifo_chan *, int);

<<<<<<< HEAD
int g84_fifo_chan_ctor(struct nv50_fifo *, u64 vmm, u64 push,
=======
int g84_fifo_chan_ctor(struct nv50_fifo *, u64 vm, u64 push,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		       const struct nvkm_oclass *, struct nv50_fifo_chan *);

extern const struct nvkm_fifo_chan_oclass nv50_fifo_dma_oclass;
extern const struct nvkm_fifo_chan_oclass nv50_fifo_gpfifo_oclass;
extern const struct nvkm_fifo_chan_oclass g84_fifo_dma_oclass;
extern const struct nvkm_fifo_chan_oclass g84_fifo_gpfifo_oclass;
#endif
