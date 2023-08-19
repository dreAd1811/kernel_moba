/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _POWERNV_H
#define _POWERNV_H

#ifdef CONFIG_SMP
extern void pnv_smp_init(void);
#else
static inline void pnv_smp_init(void) { }
#endif

extern void pnv_platform_error_reboot(struct pt_regs *regs, const char *msg) __noreturn;

struct pci_dev;

#ifdef CONFIG_PCI
extern void pnv_pci_init(void);
extern void pnv_pci_shutdown(void);
#else
static inline void pnv_pci_init(void) { }
static inline void pnv_pci_shutdown(void) { }
#endif

extern u32 pnv_get_supported_cpuidle_states(void);

extern void pnv_lpc_init(void);

<<<<<<< HEAD
extern void opal_handle_events(void);
extern bool opal_have_pending_events(void);
=======
extern void opal_handle_events(uint64_t events);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
extern void opal_event_shutdown(void);

bool cpu_core_split_required(void);

#endif /* _POWERNV_H */
