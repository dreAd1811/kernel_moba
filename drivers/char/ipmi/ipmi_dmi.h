<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0+ */
=======
/* SPDX-License-Identifier: GPL-2.0 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * DMI defines for use by IPMI
 */

<<<<<<< HEAD
#ifdef CONFIG_IPMI_DMI_DECODE
int ipmi_dmi_get_slave_addr(enum si_type si_type, u32 flags,
			    unsigned long base_addr);
=======
#define IPMI_DMI_TYPE_KCS	0x01
#define IPMI_DMI_TYPE_SMIC	0x02
#define IPMI_DMI_TYPE_BT	0x03
#define IPMI_DMI_TYPE_SSIF	0x04

#ifdef CONFIG_IPMI_DMI_DECODE
int ipmi_dmi_get_slave_addr(int type, u32 flags, unsigned long base_addr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
