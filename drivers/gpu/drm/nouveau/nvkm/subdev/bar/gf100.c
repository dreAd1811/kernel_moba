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
#include "gf100.h"

<<<<<<< HEAD
#include <core/memory.h>
=======
#include <core/gpuobj.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <core/option.h>
#include <subdev/fb.h>
#include <subdev/mmu.h>

<<<<<<< HEAD
struct nvkm_vmm *
gf100_bar_bar1_vmm(struct nvkm_bar *base)
{
	return gf100_bar(base)->bar[1].vmm;
}

void
gf100_bar_bar1_wait(struct nvkm_bar *base)
{
	/* NFI why it's twice. */
	nvkm_bar_flush(base);
	nvkm_bar_flush(base);
}

void
gf100_bar_bar1_fini(struct nvkm_bar *bar)
{
	nvkm_mask(bar->subdev.device, 0x001704, 0x80000000, 0x00000000);
}

void
gf100_bar_bar1_init(struct nvkm_bar *base)
{
	struct nvkm_device *device = base->subdev.device;
	struct gf100_bar *bar = gf100_bar(base);
	const u32 addr = nvkm_memory_addr(bar->bar[1].inst) >> 12;
	nvkm_wr32(device, 0x001704, 0x80000000 | addr);
}

struct nvkm_vmm *
gf100_bar_bar2_vmm(struct nvkm_bar *base)
{
	return gf100_bar(base)->bar[0].vmm;
}

void
gf100_bar_bar2_fini(struct nvkm_bar *bar)
{
	nvkm_mask(bar->subdev.device, 0x001714, 0x80000000, 0x00000000);
}

void
gf100_bar_bar2_init(struct nvkm_bar *base)
{
	struct nvkm_device *device = base->subdev.device;
	struct gf100_bar *bar = gf100_bar(base);
	u32 addr = nvkm_memory_addr(bar->bar[0].inst) >> 12;
	if (bar->bar2_halve)
		addr |= 0x40000000;
	nvkm_wr32(device, 0x001714, 0x80000000 | addr);
}

static int
gf100_bar_oneinit_bar(struct gf100_bar *bar, struct gf100_barN *bar_vm,
		      struct lock_class_key *key, int bar_nr)
{
	struct nvkm_device *device = bar->base.subdev.device;
=======
static struct nvkm_vm *
gf100_bar_kmap(struct nvkm_bar *base)
{
	return gf100_bar(base)->bar[0].vm;
}

int
gf100_bar_umap(struct nvkm_bar *base, u64 size, int type, struct nvkm_vma *vma)
{
	struct gf100_bar *bar = gf100_bar(base);
	return nvkm_vm_get(bar->bar[1].vm, size, type, NV_MEM_ACCESS_RW, vma);
}

static int
gf100_bar_ctor_vm(struct gf100_bar *bar, struct gf100_bar_vm *bar_vm,
		  struct lock_class_key *key, int bar_nr)
{
	struct nvkm_device *device = bar->base.subdev.device;
	struct nvkm_vm *vm;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	resource_size_t bar_len;
	int ret;

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x1000, 0, false,
<<<<<<< HEAD
			      &bar_vm->inst);
=======
			      &bar_vm->mem);
	if (ret)
		return ret;

	ret = nvkm_gpuobj_new(device, 0x8000, 0, false, NULL, &bar_vm->pgd);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret)
		return ret;

	bar_len = device->func->resource_size(device, bar_nr);
	if (bar_nr == 3 && bar->bar2_halve)
		bar_len >>= 1;

<<<<<<< HEAD
	ret = nvkm_vmm_new(device, 0, bar_len, NULL, 0, key,
			   (bar_nr == 3) ? "bar2" : "bar1", &bar_vm->vmm);
	if (ret)
		return ret;

	atomic_inc(&bar_vm->vmm->engref[NVKM_SUBDEV_BAR]);
	bar_vm->vmm->debug = bar->base.subdev.debug;
=======
	ret = nvkm_vm_new(device, 0, bar_len, 0, key, &vm);
	if (ret)
		return ret;

	atomic_inc(&vm->engref[NVKM_SUBDEV_BAR]);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * Bootstrap page table lookup.
	 */
	if (bar_nr == 3) {
<<<<<<< HEAD
		ret = nvkm_vmm_boot(bar_vm->vmm);
		if (ret)
			return ret;
	}

	return nvkm_vmm_join(bar_vm->vmm, bar_vm->inst);
=======
		ret = nvkm_vm_boot(vm, bar_len);
		if (ret) {
			nvkm_vm_ref(NULL, &vm, NULL);
			return ret;
		}
	}

	ret = nvkm_vm_ref(vm, &bar_vm->vm, bar_vm->pgd);
	nvkm_vm_ref(NULL, &vm, NULL);
	if (ret)
		return ret;

	nvkm_kmap(bar_vm->mem);
	nvkm_wo32(bar_vm->mem, 0x0200, lower_32_bits(bar_vm->pgd->addr));
	nvkm_wo32(bar_vm->mem, 0x0204, upper_32_bits(bar_vm->pgd->addr));
	nvkm_wo32(bar_vm->mem, 0x0208, lower_32_bits(bar_len - 1));
	nvkm_wo32(bar_vm->mem, 0x020c, upper_32_bits(bar_len - 1));
	nvkm_done(bar_vm->mem);
	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

int
gf100_bar_oneinit(struct nvkm_bar *base)
{
	static struct lock_class_key bar1_lock;
<<<<<<< HEAD
	static struct lock_class_key bar2_lock;
	struct gf100_bar *bar = gf100_bar(base);
	int ret;

	/* BAR2 */
	if (bar->base.func->bar2.init) {
		ret = gf100_bar_oneinit_bar(bar, &bar->bar[0], &bar2_lock, 3);
		if (ret)
			return ret;

		bar->base.subdev.oneinit = true;
		nvkm_bar_bar2_init(bar->base.subdev.device);
	}

	/* BAR1 */
	ret = gf100_bar_oneinit_bar(bar, &bar->bar[1], &bar1_lock, 1);
=======
	static struct lock_class_key bar3_lock;
	struct gf100_bar *bar = gf100_bar(base);
	int ret;

	/* BAR3 */
	if (bar->base.func->kmap) {
		ret = gf100_bar_ctor_vm(bar, &bar->bar[0], &bar3_lock, 3);
		if (ret)
			return ret;
	}

	/* BAR1 */
	ret = gf100_bar_ctor_vm(bar, &bar->bar[1], &bar1_lock, 1);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret)
		return ret;

	return 0;
}

<<<<<<< HEAD
=======
int
gf100_bar_init(struct nvkm_bar *base)
{
	struct gf100_bar *bar = gf100_bar(base);
	struct nvkm_device *device = bar->base.subdev.device;
	u32 addr;

	nvkm_mask(device, 0x000200, 0x00000100, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00000100, 0x00000100);

	addr = nvkm_memory_addr(bar->bar[1].mem) >> 12;
	nvkm_wr32(device, 0x001704, 0x80000000 | addr);

	if (bar->bar[0].mem) {
		addr = nvkm_memory_addr(bar->bar[0].mem) >> 12;
		if (bar->bar2_halve)
			addr |= 0x40000000;
		nvkm_wr32(device, 0x001714, 0x80000000 | addr);
	}

	return 0;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void *
gf100_bar_dtor(struct nvkm_bar *base)
{
	struct gf100_bar *bar = gf100_bar(base);

<<<<<<< HEAD
	nvkm_vmm_part(bar->bar[1].vmm, bar->bar[1].inst);
	nvkm_vmm_unref(&bar->bar[1].vmm);
	nvkm_memory_unref(&bar->bar[1].inst);

	nvkm_vmm_part(bar->bar[0].vmm, bar->bar[0].inst);
	nvkm_vmm_unref(&bar->bar[0].vmm);
	nvkm_memory_unref(&bar->bar[0].inst);
=======
	nvkm_vm_ref(NULL, &bar->bar[1].vm, bar->bar[1].pgd);
	nvkm_gpuobj_del(&bar->bar[1].pgd);
	nvkm_memory_del(&bar->bar[1].mem);

	if (bar->bar[0].vm) {
		nvkm_memory_del(&bar->bar[0].vm->pgt[0].mem[0]);
		nvkm_vm_ref(NULL, &bar->bar[0].vm, bar->bar[0].pgd);
	}
	nvkm_gpuobj_del(&bar->bar[0].pgd);
	nvkm_memory_del(&bar->bar[0].mem);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return bar;
}

int
gf100_bar_new_(const struct nvkm_bar_func *func, struct nvkm_device *device,
	       int index, struct nvkm_bar **pbar)
{
	struct gf100_bar *bar;
	if (!(bar = kzalloc(sizeof(*bar), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_bar_ctor(func, device, index, &bar->base);
	bar->bar2_halve = nvkm_boolopt(device->cfgopt, "NvBar2Halve", false);
	*pbar = &bar->base;
	return 0;
}

static const struct nvkm_bar_func
gf100_bar_func = {
	.dtor = gf100_bar_dtor,
	.oneinit = gf100_bar_oneinit,
<<<<<<< HEAD
	.bar1.init = gf100_bar_bar1_init,
	.bar1.fini = gf100_bar_bar1_fini,
	.bar1.wait = gf100_bar_bar1_wait,
	.bar1.vmm = gf100_bar_bar1_vmm,
	.bar2.init = gf100_bar_bar2_init,
	.bar2.fini = gf100_bar_bar2_fini,
	.bar2.wait = gf100_bar_bar1_wait,
	.bar2.vmm = gf100_bar_bar2_vmm,
=======
	.init = gf100_bar_init,
	.kmap = gf100_bar_kmap,
	.umap = gf100_bar_umap,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.flush = g84_bar_flush,
};

int
gf100_bar_new(struct nvkm_device *device, int index, struct nvkm_bar **pbar)
{
	return gf100_bar_new_(&gf100_bar_func, device, index, pbar);
}
