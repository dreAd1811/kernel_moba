/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __NVKM_BAR_H__
#define __NVKM_BAR_H__
#include <core/subdev.h>
struct nvkm_vma;

struct nvkm_bar {
	const struct nvkm_bar_func *func;
	struct nvkm_subdev subdev;

	spinlock_t lock;
<<<<<<< HEAD
	bool bar2;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* whether the BAR supports to be ioremapped WC or should be uncached */
	bool iomap_uncached;
};

<<<<<<< HEAD
struct nvkm_vmm *nvkm_bar_bar1_vmm(struct nvkm_device *);
void nvkm_bar_bar2_init(struct nvkm_device *);
void nvkm_bar_bar2_fini(struct nvkm_device *);
struct nvkm_vmm *nvkm_bar_bar2_vmm(struct nvkm_device *);
void nvkm_bar_flush(struct nvkm_bar *);
=======
void nvkm_bar_flush(struct nvkm_bar *);
struct nvkm_vm *nvkm_bar_kmap(struct nvkm_bar *);
int nvkm_bar_umap(struct nvkm_bar *, u64 size, int type, struct nvkm_vma *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

int nv50_bar_new(struct nvkm_device *, int, struct nvkm_bar **);
int g84_bar_new(struct nvkm_device *, int, struct nvkm_bar **);
int gf100_bar_new(struct nvkm_device *, int, struct nvkm_bar **);
int gk20a_bar_new(struct nvkm_device *, int, struct nvkm_bar **);
<<<<<<< HEAD
int gm107_bar_new(struct nvkm_device *, int, struct nvkm_bar **);
int gm20b_bar_new(struct nvkm_device *, int, struct nvkm_bar **);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
