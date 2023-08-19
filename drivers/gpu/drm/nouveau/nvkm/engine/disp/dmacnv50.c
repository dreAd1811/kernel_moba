/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
<<<<<<< HEAD
#include "channv50.h"

#include <core/client.h>
#include <core/ramht.h>
#include <subdev/fb.h>
#include <subdev/mmu.h>
#include <subdev/timer.h>
#include <engine/dma.h>

int
nv50_disp_dmac_new_(const struct nv50_disp_chan_func *func,
		    const struct nv50_disp_chan_mthd *mthd,
		    struct nv50_disp *disp, int chid, int head, u64 push,
=======
#include "dmacnv50.h"
#include "rootnv50.h"

#include <core/client.h>
#include <core/oproxy.h>
#include <core/ramht.h>
#include <subdev/fb.h>
#include <subdev/timer.h>
#include <engine/dma.h>

struct nv50_disp_dmac_object {
	struct nvkm_oproxy oproxy;
	struct nv50_disp_root *root;
	int hash;
};

static void
nv50_disp_dmac_child_del_(struct nvkm_oproxy *base)
{
	struct nv50_disp_dmac_object *object =
		container_of(base, typeof(*object), oproxy);
	nvkm_ramht_remove(object->root->ramht, object->hash);
}

static const struct nvkm_oproxy_func
nv50_disp_dmac_child_func_ = {
	.dtor[0] = nv50_disp_dmac_child_del_,
};

static int
nv50_disp_dmac_child_new_(struct nv50_disp_chan *base,
			  const struct nvkm_oclass *oclass,
			  void *data, u32 size, struct nvkm_object **pobject)
{
	struct nv50_disp_dmac *chan = nv50_disp_dmac(base);
	struct nv50_disp_root *root = chan->base.root;
	struct nvkm_device *device = root->disp->base.engine.subdev.device;
	const struct nvkm_device_oclass *sclass = oclass->priv;
	struct nv50_disp_dmac_object *object;
	int ret;

	if (!(object = kzalloc(sizeof(*object), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_oproxy_ctor(&nv50_disp_dmac_child_func_, oclass, &object->oproxy);
	object->root = root;
	*pobject = &object->oproxy.base;

	ret = sclass->ctor(device, oclass, data, size, &object->oproxy.object);
	if (ret)
		return ret;

	object->hash = chan->func->bind(chan, object->oproxy.object,
					      oclass->handle);
	if (object->hash < 0)
		return object->hash;

	return 0;
}

static int
nv50_disp_dmac_child_get_(struct nv50_disp_chan *base, int index,
			  struct nvkm_oclass *sclass)
{
	struct nv50_disp_dmac *chan = nv50_disp_dmac(base);
	struct nv50_disp *disp = chan->base.root->disp;
	struct nvkm_device *device = disp->base.engine.subdev.device;
	const struct nvkm_device_oclass *oclass = NULL;

	sclass->engine = nvkm_device_engine(device, NVKM_ENGINE_DMAOBJ);
	if (sclass->engine && sclass->engine->func->base.sclass) {
		sclass->engine->func->base.sclass(sclass, index, &oclass);
		if (oclass) {
			sclass->priv = oclass;
			return 0;
		}
	}

	return -EINVAL;
}

static void
nv50_disp_dmac_fini_(struct nv50_disp_chan *base)
{
	struct nv50_disp_dmac *chan = nv50_disp_dmac(base);
	chan->func->fini(chan);
}

static int
nv50_disp_dmac_init_(struct nv50_disp_chan *base)
{
	struct nv50_disp_dmac *chan = nv50_disp_dmac(base);
	return chan->func->init(chan);
}

static void *
nv50_disp_dmac_dtor_(struct nv50_disp_chan *base)
{
	return nv50_disp_dmac(base);
}

static const struct nv50_disp_chan_func
nv50_disp_dmac_func_ = {
	.dtor = nv50_disp_dmac_dtor_,
	.init = nv50_disp_dmac_init_,
	.fini = nv50_disp_dmac_fini_,
	.child_get = nv50_disp_dmac_child_get_,
	.child_new = nv50_disp_dmac_child_new_,
};

int
nv50_disp_dmac_new_(const struct nv50_disp_dmac_func *func,
		    const struct nv50_disp_chan_mthd *mthd,
		    struct nv50_disp_root *root, int chid, int head, u64 push,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		    const struct nvkm_oclass *oclass,
		    struct nvkm_object **pobject)
{
	struct nvkm_client *client = oclass->client;
<<<<<<< HEAD
	struct nv50_disp_chan *chan;
	int ret;

	ret = nv50_disp_chan_new_(func, mthd, disp, chid, chid, head, oclass,
				  pobject);
	chan = nv50_disp_chan(*pobject);
	if (ret)
		return ret;

	chan->memory = nvkm_umem_search(client, push);
	if (IS_ERR(chan->memory))
		return PTR_ERR(chan->memory);

	if (nvkm_memory_size(chan->memory) < 0x1000)
		return -EINVAL;

	switch (nvkm_memory_target(chan->memory)) {
	case NVKM_MEM_TARGET_VRAM: chan->push = 0x00000001; break;
	case NVKM_MEM_TARGET_NCOH: chan->push = 0x00000002; break;
	case NVKM_MEM_TARGET_HOST: chan->push = 0x00000003; break;
=======
	struct nvkm_dmaobj *dmaobj;
	struct nv50_disp_dmac *chan;
	int ret;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	*pobject = &chan->base.object;
	chan->func = func;

	ret = nv50_disp_chan_ctor(&nv50_disp_dmac_func_, mthd, root,
				  chid, chid, head, oclass, &chan->base);
	if (ret)
		return ret;

	dmaobj = nvkm_dmaobj_search(client, push);
	if (IS_ERR(dmaobj))
		return PTR_ERR(dmaobj);

	if (dmaobj->limit - dmaobj->start != 0xfff)
		return -EINVAL;

	switch (dmaobj->target) {
	case NV_MEM_TARGET_VRAM:
		chan->push = 0x00000001 | dmaobj->start >> 8;
		break;
	case NV_MEM_TARGET_PCI_NOSNOOP:
		chan->push = 0x00000003 | dmaobj->start >> 8;
		break;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	default:
		return -EINVAL;
	}

<<<<<<< HEAD
	chan->push |= nvkm_memory_addr(chan->memory) >> 8;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

int
<<<<<<< HEAD
nv50_disp_dmac_bind(struct nv50_disp_chan *chan,
		    struct nvkm_object *object, u32 handle)
{
	return nvkm_ramht_insert(chan->disp->ramht, object,
				 chan->chid.user, -10, handle,
				 chan->chid.user << 28 |
				 chan->chid.user);
}

static void
nv50_disp_dmac_fini(struct nv50_disp_chan *chan)
{
	struct nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	int ctrl = chan->chid.ctrl;
	int user = chan->chid.user;
=======
nv50_disp_dmac_bind(struct nv50_disp_dmac *chan,
		    struct nvkm_object *object, u32 handle)
{
	return nvkm_ramht_insert(chan->base.root->ramht, object,
				 chan->base.chid.user, -10, handle,
				 chan->base.chid.user << 28 |
				 chan->base.chid.user);
}

static void
nv50_disp_dmac_fini(struct nv50_disp_dmac *chan)
{
	struct nv50_disp *disp = chan->base.root->disp;
	struct nvkm_subdev *subdev = &disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	int ctrl = chan->base.chid.ctrl;
	int user = chan->base.chid.user;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* deactivate channel */
	nvkm_mask(device, 0x610200 + (ctrl * 0x0010), 0x00001010, 0x00001000);
	nvkm_mask(device, 0x610200 + (ctrl * 0x0010), 0x00000003, 0x00000000);
	if (nvkm_msec(device, 2000,
		if (!(nvkm_rd32(device, 0x610200 + (ctrl * 0x10)) & 0x001e0000))
			break;
	) < 0) {
		nvkm_error(subdev, "ch %d fini timeout, %08x\n", user,
			   nvkm_rd32(device, 0x610200 + (ctrl * 0x10)));
	}
<<<<<<< HEAD
}

static int
nv50_disp_dmac_init(struct nv50_disp_chan *chan)
{
	struct nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	int ctrl = chan->chid.ctrl;
	int user = chan->chid.user;
=======

	/* disable error reporting and completion notifications */
	nvkm_mask(device, 0x610028, 0x00010001 << user, 0x00000000 << user);
}

static int
nv50_disp_dmac_init(struct nv50_disp_dmac *chan)
{
	struct nv50_disp *disp = chan->base.root->disp;
	struct nvkm_subdev *subdev = &disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	int ctrl = chan->base.chid.ctrl;
	int user = chan->base.chid.user;

	/* enable error reporting */
	nvkm_mask(device, 0x610028, 0x00010000 << user, 0x00010000 << user);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* initialise channel for dma command submission */
	nvkm_wr32(device, 0x610204 + (ctrl * 0x0010), chan->push);
	nvkm_wr32(device, 0x610208 + (ctrl * 0x0010), 0x00010000);
	nvkm_wr32(device, 0x61020c + (ctrl * 0x0010), ctrl);
	nvkm_mask(device, 0x610200 + (ctrl * 0x0010), 0x00000010, 0x00000010);
	nvkm_wr32(device, 0x640000 + (ctrl * 0x1000), 0x00000000);
	nvkm_wr32(device, 0x610200 + (ctrl * 0x0010), 0x00000013);

	/* wait for it to go inactive */
	if (nvkm_msec(device, 2000,
		if (!(nvkm_rd32(device, 0x610200 + (ctrl * 0x10)) & 0x80000000))
			break;
	) < 0) {
		nvkm_error(subdev, "ch %d init timeout, %08x\n", user,
			   nvkm_rd32(device, 0x610200 + (ctrl * 0x10)));
		return -EBUSY;
	}

	return 0;
}

<<<<<<< HEAD
const struct nv50_disp_chan_func
nv50_disp_dmac_func = {
	.init = nv50_disp_dmac_init,
	.fini = nv50_disp_dmac_fini,
	.intr = nv50_disp_chan_intr,
	.user = nv50_disp_chan_user,
=======
const struct nv50_disp_dmac_func
nv50_disp_dmac_func = {
	.init = nv50_disp_dmac_init,
	.fini = nv50_disp_dmac_fini,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.bind = nv50_disp_dmac_bind,
};
