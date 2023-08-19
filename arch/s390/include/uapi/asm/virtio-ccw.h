/* SPDX-License-Identifier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * Definitions for virtio-ccw devices.
 *
 * Copyright IBM Corp. 2013
 *
<<<<<<< HEAD
=======
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (version 2 only)
 * as published by the Free Software Foundation.
 *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *  Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 */
#ifndef __KVM_VIRTIO_CCW_H
#define __KVM_VIRTIO_CCW_H

/* Alignment of vring buffers. */
#define KVM_VIRTIO_CCW_RING_ALIGN 4096

/* Subcode for diagnose 500 (virtio hypercall). */
#define KVM_S390_VIRTIO_CCW_NOTIFY 3

#endif
