/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Definitions for perf-kvm on s390
 *
 * Copyright 2014 IBM Corp.
 * Author(s): Alexander Yarygin <yarygin@linux.vnet.ibm.com>
<<<<<<< HEAD
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (version 2 only)
 * as published by the Free Software Foundation.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef __LINUX_KVM_PERF_S390_H
#define __LINUX_KVM_PERF_S390_H

#include <asm/sie.h>

#define DECODE_STR_LEN 40

#define VCPU_ID "id"

#define KVM_ENTRY_TRACE "kvm:kvm_s390_sie_enter"
#define KVM_EXIT_TRACE "kvm:kvm_s390_sie_exit"
#define KVM_EXIT_REASON "icptcode"

#endif
