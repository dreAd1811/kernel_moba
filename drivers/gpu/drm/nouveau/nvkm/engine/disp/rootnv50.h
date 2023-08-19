/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __NV50_DISP_ROOT_H__
#define __NV50_DISP_ROOT_H__
#define nv50_disp_root(p) container_of((p), struct nv50_disp_root, object)
<<<<<<< HEAD
#include <core/object.h>
#include "nv50.h"
=======
#include "nv50.h"
#include "channv50.h"
#include "dmacnv50.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct nv50_disp_root {
	const struct nv50_disp_root_func *func;
	struct nv50_disp *disp;
	struct nvkm_object object;
<<<<<<< HEAD
};

struct nv50_disp_root_func {
	int blah;
	struct nv50_disp_user {
		struct nvkm_sclass base;
		int (*ctor)(const struct nvkm_oclass *, void *argv, u32 argc,
			    struct nv50_disp *, struct nvkm_object **);
	} user[];
=======

	struct nvkm_gpuobj *instmem;
	struct nvkm_ramht *ramht;
};

struct nv50_disp_root_func {
	int (*init)(struct nv50_disp_root *);
	void (*fini)(struct nv50_disp_root *);
	const struct nv50_disp_dmac_oclass *dmac[3];
	const struct nv50_disp_pioc_oclass *pioc[2];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

int  nv50_disp_root_new_(const struct nv50_disp_root_func *, struct nvkm_disp *,
			 const struct nvkm_oclass *, void *data, u32 size,
			 struct nvkm_object **);
<<<<<<< HEAD
=======
int  nv50_disp_root_init(struct nv50_disp_root *);
void nv50_disp_root_fini(struct nv50_disp_root *);

int  gf119_disp_root_init(struct nv50_disp_root *);
void gf119_disp_root_fini(struct nv50_disp_root *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

extern const struct nvkm_disp_oclass nv50_disp_root_oclass;
extern const struct nvkm_disp_oclass g84_disp_root_oclass;
extern const struct nvkm_disp_oclass g94_disp_root_oclass;
extern const struct nvkm_disp_oclass gt200_disp_root_oclass;
extern const struct nvkm_disp_oclass gt215_disp_root_oclass;
extern const struct nvkm_disp_oclass gf119_disp_root_oclass;
extern const struct nvkm_disp_oclass gk104_disp_root_oclass;
extern const struct nvkm_disp_oclass gk110_disp_root_oclass;
extern const struct nvkm_disp_oclass gm107_disp_root_oclass;
extern const struct nvkm_disp_oclass gm200_disp_root_oclass;
extern const struct nvkm_disp_oclass gp100_disp_root_oclass;
extern const struct nvkm_disp_oclass gp102_disp_root_oclass;
<<<<<<< HEAD
extern const struct nvkm_disp_oclass gv100_disp_root_oclass;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
