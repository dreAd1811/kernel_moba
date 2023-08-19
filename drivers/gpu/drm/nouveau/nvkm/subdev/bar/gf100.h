/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __GF100_BAR_H__
#define __GF100_BAR_H__
#define gf100_bar(p) container_of((p), struct gf100_bar, base)
#include "priv.h"

<<<<<<< HEAD
struct gf100_barN {
	struct nvkm_memory *inst;
	struct nvkm_vmm *vmm;
=======
struct gf100_bar_vm {
	struct nvkm_memory *mem;
	struct nvkm_gpuobj *pgd;
	struct nvkm_vm *vm;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct gf100_bar {
	struct nvkm_bar base;
	bool bar2_halve;
<<<<<<< HEAD
	struct gf100_barN bar[2];
=======
	struct gf100_bar_vm bar[2];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

int gf100_bar_new_(const struct nvkm_bar_func *, struct nvkm_device *,
		   int, struct nvkm_bar **);
void *gf100_bar_dtor(struct nvkm_bar *);
int gf100_bar_oneinit(struct nvkm_bar *);
<<<<<<< HEAD
void gf100_bar_bar1_init(struct nvkm_bar *);
void gf100_bar_bar1_wait(struct nvkm_bar *);
struct nvkm_vmm *gf100_bar_bar1_vmm(struct nvkm_bar *);
void gf100_bar_bar2_init(struct nvkm_bar *);
struct nvkm_vmm *gf100_bar_bar2_vmm(struct nvkm_bar *);
=======
int gf100_bar_init(struct nvkm_bar *);
int gf100_bar_umap(struct nvkm_bar *, u64, int, struct nvkm_vma *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
