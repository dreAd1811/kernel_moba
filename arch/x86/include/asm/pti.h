// SPDX-License-Identifier: GPL-2.0
#ifndef _ASM_X86_PTI_H
#define _ASM_X86_PTI_H
#ifndef __ASSEMBLY__

#ifdef CONFIG_PAGE_TABLE_ISOLATION
extern void pti_init(void);
extern void pti_check_boottime_disable(void);
<<<<<<< HEAD
extern void pti_finalize(void);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#else
static inline void pti_check_boottime_disable(void) { }
#endif

#endif /* __ASSEMBLY__ */
#endif /* _ASM_X86_PTI_H */
