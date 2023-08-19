/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __NOUVEAU_TTM_H__
#define __NOUVEAU_TTM_H__

static inline struct nouveau_drm *
nouveau_bdev(struct ttm_bo_device *bd)
{
	return container_of(bd, struct nouveau_drm, ttm.bdev);
}

extern const struct ttm_mem_type_manager_func nouveau_vram_manager;
extern const struct ttm_mem_type_manager_func nouveau_gart_manager;
extern const struct ttm_mem_type_manager_func nv04_gart_manager;

<<<<<<< HEAD
struct ttm_tt *nouveau_sgdma_create_ttm(struct ttm_buffer_object *bo,
					u32 page_flags);
=======
struct ttm_tt *nouveau_sgdma_create_ttm(struct ttm_bo_device *,
					unsigned long size, u32 page_flags,
					struct page *dummy_read_page);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

int  nouveau_ttm_init(struct nouveau_drm *drm);
void nouveau_ttm_fini(struct nouveau_drm *drm);
int  nouveau_ttm_mmap(struct file *, struct vm_area_struct *);

int  nouveau_ttm_global_init(struct nouveau_drm *);
void nouveau_ttm_global_release(struct nouveau_drm *);

#endif
