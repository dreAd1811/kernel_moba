/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

<<<<<<< HEAD
#include <linux/types.h>
#include "kfd_priv.h"

static unsigned int pasid_bits = 16;
static const struct kfd2kgd_calls *kfd2kgd;

bool kfd_set_pasid_limit(unsigned int new_limit)
{
	if (new_limit < 2)
		return false;

	if (new_limit < (1U << pasid_bits)) {
		if (kfd2kgd)
			/* We've already allocated user PASIDs, too late to
			 * change the limit
			 */
			return false;

		while (new_limit < (1U << pasid_bits))
			pasid_bits--;
=======
#include <linux/slab.h>
#include <linux/types.h>
#include "kfd_priv.h"

static unsigned long *pasid_bitmap;
static unsigned int pasid_limit;
static DEFINE_MUTEX(pasid_mutex);

int kfd_pasid_init(void)
{
	pasid_limit = KFD_MAX_NUM_OF_PROCESSES;

	pasid_bitmap = kcalloc(BITS_TO_LONGS(pasid_limit), sizeof(long),
				GFP_KERNEL);
	if (!pasid_bitmap)
		return -ENOMEM;

	set_bit(0, pasid_bitmap); /* PASID 0 is reserved. */

	return 0;
}

void kfd_pasid_exit(void)
{
	kfree(pasid_bitmap);
}

bool kfd_set_pasid_limit(unsigned int new_limit)
{
	if (new_limit < pasid_limit) {
		bool ok;

		mutex_lock(&pasid_mutex);

		/* ensure that no pasids >= new_limit are in-use */
		ok = (find_next_bit(pasid_bitmap, pasid_limit, new_limit) ==
								pasid_limit);
		if (ok)
			pasid_limit = new_limit;

		mutex_unlock(&pasid_mutex);

		return ok;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	return true;
}

<<<<<<< HEAD
unsigned int kfd_get_pasid_limit(void)
{
	return 1U << pasid_bits;
=======
inline unsigned int kfd_get_pasid_limit(void)
{
	return pasid_limit;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

unsigned int kfd_pasid_alloc(void)
{
<<<<<<< HEAD
	int r;

	/* Find the first best KFD device for calling KGD */
	if (!kfd2kgd) {
		struct kfd_dev *dev = NULL;
		unsigned int i = 0;

		while ((kfd_topology_enum_kfd_devices(i, &dev)) == 0) {
			if (dev && dev->kfd2kgd) {
				kfd2kgd = dev->kfd2kgd;
				break;
			}
			i++;
		}

		if (!kfd2kgd)
			return false;
	}

	r = kfd2kgd->alloc_pasid(pasid_bits);

	return r > 0 ? r : 0;
=======
	unsigned int found;

	mutex_lock(&pasid_mutex);

	found = find_first_zero_bit(pasid_bitmap, pasid_limit);
	if (found == pasid_limit)
		found = 0;
	else
		set_bit(found, pasid_bitmap);

	mutex_unlock(&pasid_mutex);

	return found;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

void kfd_pasid_free(unsigned int pasid)
{
<<<<<<< HEAD
	if (kfd2kgd)
		kfd2kgd->free_pasid(pasid);
=======
	if (!WARN_ON(pasid == 0 || pasid >= pasid_limit))
		clear_bit(pasid, pasid_bitmap);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
