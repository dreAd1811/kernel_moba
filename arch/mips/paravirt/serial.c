/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2013 Cavium, Inc.
 */

#include <linux/kernel.h>
#include <linux/virtio_console.h>
#include <linux/kvm_para.h>
<<<<<<< HEAD
#include <asm/setup.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/*
 * Emit one character to the boot console.
 */
<<<<<<< HEAD
void prom_putchar(char c)
{
	kvm_hypercall3(KVM_HC_MIPS_CONSOLE_OUTPUT, 0 /*  port 0 */,
		(unsigned long)&c, 1 /* len == 1 */);
=======
int prom_putchar(char c)
{
	kvm_hypercall3(KVM_HC_MIPS_CONSOLE_OUTPUT, 0 /*  port 0 */,
		(unsigned long)&c, 1 /* len == 1 */);

	return 1;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

#ifdef CONFIG_VIRTIO_CONSOLE
static int paravirt_put_chars(u32 vtermno, const char *buf, int count)
{
	kvm_hypercall3(KVM_HC_MIPS_CONSOLE_OUTPUT, vtermno,
		(unsigned long)buf, count);

	return count;
}

static int __init paravirt_cons_init(void)
{
	virtio_cons_early_init(paravirt_put_chars);
	return 0;
}
core_initcall(paravirt_cons_init);

#endif
