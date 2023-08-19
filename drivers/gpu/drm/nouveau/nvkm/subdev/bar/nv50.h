/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __NV50_BAR_H__
#define __NV50_BAR_H__
#define nv50_bar(p) container_of((p), struct nv50_bar, base)
#include "priv.h"

struct nv50_bar {
	struct nvkm_bar base;
	u32 pgd_addr;
	struct nvkm_gpuobj *mem;
	struct nvkm_gpuobj *pad;
	struct nvkm_gpuobj *pgd;
<<<<<<< HEAD
	struct nvkm_vmm *bar1_vmm;
	struct nvkm_gpuobj *bar1;
	struct nvkm_vmm *bar2_vmm;
	struct nvkm_gpuobj *bar2;
=======
	struct nvkm_vm *bar1_vm;
	struct nvkm_gpuobj *bar1;
	struct nvkm_vm *bar3_vm;
	struct nvkm_gpuobj *bar3;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

int nv50_bar_new_(const struct nvkm_bar_func *, struct nvkm_device *,
		  int, u32 pgd_addr, struct nvkm_bar **);
void *nv50_bar_dtor(struct nvkm_bar *);
int nv50_bar_oneinit(struct nvkm_bar *);
<<<<<<< HEAD
void nv50_bar_init(struct nvkm_bar *);
void nv50_bar_bar1_init(struct nvkm_bar *);
void nv50_bar_bar1_wait(struct nvkm_bar *);
struct nvkm_vmm *nv50_bar_bar1_vmm(struct nvkm_bar *);
void nv50_bar_bar2_init(struct nvkm_bar *);
struct nvkm_vmm *nv50_bar_bar2_vmm(struct nvkm_bar *);
=======
int nv50_bar_init(struct nvkm_bar *);
struct nvkm_vm *nv50_bar_kmap(struct nvkm_bar *);
int nv50_bar_umap(struct nvkm_bar *, u64, int, struct nvkm_vma *);
void nv50_bar_unmap(struct nvkm_bar *, struct nvkm_vma *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
