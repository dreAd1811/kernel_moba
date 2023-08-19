/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __GK104_FIFO_H__
#define __GK104_FIFO_H__
#define gk104_fifo(p) container_of((p), struct gk104_fifo, base)
#include "priv.h"
<<<<<<< HEAD
struct nvkm_fifo_cgrp;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <core/enum.h>
#include <subdev/mmu.h>

struct gk104_fifo_chan;
struct gk104_fifo {
	const struct gk104_fifo_func *func;
	struct nvkm_fifo base;

	struct {
		struct work_struct work;
		u32 engm;
		u32 runm;
	} recover;

	int pbdma_nr;

	struct {
		struct nvkm_engine *engine;
		int runl;
		int pbid;
	} engine[16];
	int engine_nr;

	struct {
		struct nvkm_memory *mem[2];
		int next;
		wait_queue_head_t wait;
<<<<<<< HEAD
		struct list_head cgrp;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		struct list_head chan;
		u32 engm;
	} runlist[16];
	int runlist_nr;

	struct {
		struct nvkm_memory *mem;
<<<<<<< HEAD
		struct nvkm_vma *bar;
=======
		struct nvkm_vma bar;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	} user;
};

struct gk104_fifo_func {
<<<<<<< HEAD
	void (*init_pbdma_timeout)(struct gk104_fifo *);

	struct {
		const struct nvkm_enum *access;
=======
	struct {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		const struct nvkm_enum *engine;
		const struct nvkm_enum *reason;
		const struct nvkm_enum *hubclient;
		const struct nvkm_enum *gpcclient;
	} fault;

<<<<<<< HEAD
	const struct gk104_fifo_runlist_func {
		u8 size;
		void (*cgrp)(struct nvkm_fifo_cgrp *,
			     struct nvkm_memory *, u32 offset);
		void (*chan)(struct gk104_fifo_chan *,
			     struct nvkm_memory *, u32 offset);
	} *runlist;

	struct gk104_fifo_user_user {
		struct nvkm_sclass user;
		int (*ctor)(const struct nvkm_oclass *, void *, u32,
			    struct nvkm_object **);
	} user;

	struct gk104_fifo_chan_user {
		struct nvkm_sclass user;
		int (*ctor)(struct gk104_fifo *, const struct nvkm_oclass *,
			    void *, u32, struct nvkm_object **);
	} chan;
	bool cgrp_force;
=======
	const struct nvkm_fifo_chan_oclass *chan[];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

int gk104_fifo_new_(const struct gk104_fifo_func *, struct nvkm_device *,
		    int index, int nr, struct nvkm_fifo **);
void gk104_fifo_runlist_insert(struct gk104_fifo *, struct gk104_fifo_chan *);
void gk104_fifo_runlist_remove(struct gk104_fifo *, struct gk104_fifo_chan *);
void gk104_fifo_runlist_commit(struct gk104_fifo *, int runl);

<<<<<<< HEAD
extern const struct nvkm_enum gk104_fifo_fault_access[];
=======
static inline u64
gk104_fifo_engine_subdev(int engine)
{
	switch (engine) {
	case 0: return (1ULL << NVKM_ENGINE_GR) |
		       (1ULL << NVKM_ENGINE_SW) |
		       (1ULL << NVKM_ENGINE_CE2);
	case 1: return (1ULL << NVKM_ENGINE_MSPDEC);
	case 2: return (1ULL << NVKM_ENGINE_MSPPP);
	case 3: return (1ULL << NVKM_ENGINE_MSVLD);
	case 4: return (1ULL << NVKM_ENGINE_CE0);
	case 5: return (1ULL << NVKM_ENGINE_CE1);
	case 6: return (1ULL << NVKM_ENGINE_MSENC);
	default:
		WARN_ON(1);
		return 0;
	}
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
extern const struct nvkm_enum gk104_fifo_fault_engine[];
extern const struct nvkm_enum gk104_fifo_fault_reason[];
extern const struct nvkm_enum gk104_fifo_fault_hubclient[];
extern const struct nvkm_enum gk104_fifo_fault_gpcclient[];
<<<<<<< HEAD
extern const struct gk104_fifo_runlist_func gk104_fifo_runlist;
void gk104_fifo_runlist_chan(struct gk104_fifo_chan *,
			     struct nvkm_memory *, u32);

extern const struct gk104_fifo_runlist_func gk110_fifo_runlist;
void gk110_fifo_runlist_cgrp(struct nvkm_fifo_cgrp *,
			     struct nvkm_memory *, u32);

void gk208_fifo_init_pbdma_timeout(struct gk104_fifo *);

extern const struct nvkm_enum gm107_fifo_fault_engine[];
extern const struct gk104_fifo_runlist_func gm107_fifo_runlist;

=======

extern const struct nvkm_enum gm107_fifo_fault_engine[];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
extern const struct nvkm_enum gp100_fifo_fault_engine[];
#endif
