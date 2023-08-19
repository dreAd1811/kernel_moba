/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_IOMMU_H
#define _ASM_X86_IOMMU_H

<<<<<<< HEAD
=======
extern const struct dma_map_ops nommu_dma_ops;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
extern int force_iommu, no_iommu;
extern int iommu_detected;
extern int iommu_pass_through;

<<<<<<< HEAD
=======
int x86_dma_supported(struct device *dev, u64 mask);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/* 10 seconds */
#define DMAR_OPERATION_TIMEOUT ((cycles_t) tsc_khz*10*1000)

#endif /* _ASM_X86_IOMMU_H */
