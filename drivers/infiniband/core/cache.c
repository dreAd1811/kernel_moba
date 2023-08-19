/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Intel Corporation. All rights reserved.
 * Copyright (c) 2005 Sun Microsystems, Inc. All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <linux/module.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/netdevice.h>
#include <net/addrconf.h>

#include <rdma/ib_cache.h>

#include "core_priv.h"

struct ib_pkey_cache {
	int             table_len;
	u16             table[0];
};

struct ib_update_work {
	struct work_struct work;
	struct ib_device  *device;
	u8                 port_num;
	bool		   enforce_security;
};

union ib_gid zgid;
EXPORT_SYMBOL(zgid);

<<<<<<< HEAD
=======
static const struct ib_gid_attr zattr;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
enum gid_attr_find_mask {
	GID_ATTR_FIND_MASK_GID          = 1UL << 0,
	GID_ATTR_FIND_MASK_NETDEV	= 1UL << 1,
	GID_ATTR_FIND_MASK_DEFAULT	= 1UL << 2,
	GID_ATTR_FIND_MASK_GID_TYPE	= 1UL << 3,
};

<<<<<<< HEAD
enum gid_table_entry_state {
	GID_TABLE_ENTRY_INVALID		= 1,
	GID_TABLE_ENTRY_VALID		= 2,
	/*
	 * Indicates that entry is pending to be removed, there may
	 * be active users of this GID entry.
	 * When last user of the GID entry releases reference to it,
	 * GID entry is detached from the table.
	 */
	GID_TABLE_ENTRY_PENDING_DEL	= 3,
};

struct ib_gid_table_entry {
	struct kref			kref;
	struct work_struct		del_work;
	struct ib_gid_attr		attr;
	void				*context;
	enum gid_table_entry_state	state;
};

struct ib_gid_table {
	int				sz;
=======
enum gid_table_entry_props {
	GID_TABLE_ENTRY_INVALID		= 1UL << 0,
	GID_TABLE_ENTRY_DEFAULT		= 1UL << 1,
};

enum gid_table_write_action {
	GID_TABLE_WRITE_ACTION_ADD,
	GID_TABLE_WRITE_ACTION_DEL,
	/* MODIFY only updates the GID table. Currently only used by
	 * ib_cache_update.
	 */
	GID_TABLE_WRITE_ACTION_MODIFY
};

struct ib_gid_table_entry {
	unsigned long	    props;
	union ib_gid        gid;
	struct ib_gid_attr  attr;
	void		   *context;
};

struct ib_gid_table {
	int                  sz;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* In RoCE, adding a GID to the table requires:
	 * (a) Find if this GID is already exists.
	 * (b) Find a free space.
	 * (c) Write the new GID
	 *
	 * Delete requires different set of operations:
	 * (a) Find the GID
	 * (b) Delete it.
	 *
<<<<<<< HEAD
	 **/
	/* Any writer to data_vec must hold this lock and the write side of
	 * rwlock. Readers must hold only rwlock. All writers must be in a
	 * sleepable context.
	 */
	struct mutex			lock;
	/* rwlock protects data_vec[ix]->state and entry pointer.
	 */
	rwlock_t			rwlock;
	struct ib_gid_table_entry	**data_vec;
	/* bit field, each bit indicates the index of default GID */
	u32				default_gid_indices;
=======
	 * Add/delete should be carried out atomically.
	 * This is done by locking this mutex from multiple
	 * writers. We don't need this lock for IB, as the MAD
	 * layer replaces all entries. All data_vec entries
	 * are locked by this lock.
	 **/
	struct mutex         lock;
	/* This lock protects the table entries from being
	 * read and written simultaneously.
	 */
	rwlock_t	     rwlock;
	struct ib_gid_table_entry *data_vec;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static void dispatch_gid_change_event(struct ib_device *ib_dev, u8 port)
{
<<<<<<< HEAD
	struct ib_event event;

	event.device		= ib_dev;
	event.element.port_num	= port;
	event.event		= IB_EVENT_GID_CHANGE;

	ib_dispatch_event(&event);
=======
	if (rdma_cap_roce_gid_table(ib_dev, port)) {
		struct ib_event event;

		event.device		= ib_dev;
		event.element.port_num	= port;
		event.event		= IB_EVENT_GID_CHANGE;

		ib_dispatch_event(&event);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static const char * const gid_type_str[] = {
	[IB_GID_TYPE_IB]	= "IB/RoCE v1",
	[IB_GID_TYPE_ROCE_UDP_ENCAP]	= "RoCE v2",
};

const char *ib_cache_gid_type_str(enum ib_gid_type gid_type)
{
	if (gid_type < ARRAY_SIZE(gid_type_str) && gid_type_str[gid_type])
		return gid_type_str[gid_type];

	return "Invalid GID type";
}
EXPORT_SYMBOL(ib_cache_gid_type_str);

<<<<<<< HEAD
/** rdma_is_zero_gid - Check if given GID is zero or not.
 * @gid:	GID to check
 * Returns true if given GID is zero, returns false otherwise.
 */
bool rdma_is_zero_gid(const union ib_gid *gid)
{
	return !memcmp(gid, &zgid, sizeof(*gid));
}
EXPORT_SYMBOL(rdma_is_zero_gid);

/** is_gid_index_default - Check if a given index belongs to
 * reserved default GIDs or not.
 * @table:	GID table pointer
 * @index:	Index to check in GID table
 * Returns true if index is one of the reserved default GID index otherwise
 * returns false.
 */
static bool is_gid_index_default(const struct ib_gid_table *table,
				 unsigned int index)
{
	return index < 32 && (BIT(index) & table->default_gid_indices);
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int ib_cache_gid_parse_type_str(const char *buf)
{
	unsigned int i;
	size_t len;
	int err = -EINVAL;

	len = strlen(buf);
	if (len == 0)
		return -EINVAL;

	if (buf[len - 1] == '\n')
		len--;

	for (i = 0; i < ARRAY_SIZE(gid_type_str); ++i)
		if (gid_type_str[i] && !strncmp(buf, gid_type_str[i], len) &&
		    len == strlen(gid_type_str[i])) {
			err = i;
			break;
		}

	return err;
}
EXPORT_SYMBOL(ib_cache_gid_parse_type_str);

<<<<<<< HEAD
static struct ib_gid_table *rdma_gid_table(struct ib_device *device, u8 port)
{
	return device->cache.ports[port - rdma_start_port(device)].gid;
}

static bool is_gid_entry_free(const struct ib_gid_table_entry *entry)
{
	return !entry;
}

static bool is_gid_entry_valid(const struct ib_gid_table_entry *entry)
{
	return entry && entry->state == GID_TABLE_ENTRY_VALID;
}

static void schedule_free_gid(struct kref *kref)
{
	struct ib_gid_table_entry *entry =
			container_of(kref, struct ib_gid_table_entry, kref);

	queue_work(ib_wq, &entry->del_work);
}

static void free_gid_entry_locked(struct ib_gid_table_entry *entry)
{
	struct ib_device *device = entry->attr.device;
	u8 port_num = entry->attr.port_num;
	struct ib_gid_table *table = rdma_gid_table(device, port_num);

	pr_debug("%s device=%s port=%d index=%d gid %pI6\n", __func__,
		 device->name, port_num, entry->attr.index,
		 entry->attr.gid.raw);

	if (rdma_cap_roce_gid_table(device, port_num) &&
	    entry->state != GID_TABLE_ENTRY_INVALID)
		device->del_gid(&entry->attr, &entry->context);

	write_lock_irq(&table->rwlock);

	/*
	 * The only way to avoid overwriting NULL in table is
	 * by comparing if it is same entry in table or not!
	 * If new entry in table is added by the time we free here,
	 * don't overwrite the table entry.
	 */
	if (entry == table->data_vec[entry->attr.index])
		table->data_vec[entry->attr.index] = NULL;
	/* Now this index is ready to be allocated */
	write_unlock_irq(&table->rwlock);

	if (entry->attr.ndev)
		dev_put(entry->attr.ndev);
	kfree(entry);
}

static void free_gid_entry(struct kref *kref)
{
	struct ib_gid_table_entry *entry =
			container_of(kref, struct ib_gid_table_entry, kref);

	free_gid_entry_locked(entry);
}

/**
 * free_gid_work - Release reference to the GID entry
 * @work: Work structure to refer to GID entry which needs to be
 * deleted.
 *
 * free_gid_work() frees the entry from the HCA's hardware table
 * if provider supports it. It releases reference to netdevice.
 */
static void free_gid_work(struct work_struct *work)
{
	struct ib_gid_table_entry *entry =
		container_of(work, struct ib_gid_table_entry, del_work);
	struct ib_device *device = entry->attr.device;
	u8 port_num = entry->attr.port_num;
	struct ib_gid_table *table = rdma_gid_table(device, port_num);

	mutex_lock(&table->lock);
	free_gid_entry_locked(entry);
	mutex_unlock(&table->lock);
}

static struct ib_gid_table_entry *
alloc_gid_entry(const struct ib_gid_attr *attr)
{
	struct ib_gid_table_entry *entry;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return NULL;
	kref_init(&entry->kref);
	memcpy(&entry->attr, attr, sizeof(*attr));
	if (entry->attr.ndev)
		dev_hold(entry->attr.ndev);
	INIT_WORK(&entry->del_work, free_gid_work);
	entry->state = GID_TABLE_ENTRY_INVALID;
	return entry;
}

static void store_gid_entry(struct ib_gid_table *table,
			    struct ib_gid_table_entry *entry)
{
	entry->state = GID_TABLE_ENTRY_VALID;

	pr_debug("%s device=%s port=%d index=%d gid %pI6\n", __func__,
		 entry->attr.device->name, entry->attr.port_num,
		 entry->attr.index, entry->attr.gid.raw);

	lockdep_assert_held(&table->lock);
	write_lock_irq(&table->rwlock);
	table->data_vec[entry->attr.index] = entry;
	write_unlock_irq(&table->rwlock);
}

static void get_gid_entry(struct ib_gid_table_entry *entry)
{
	kref_get(&entry->kref);
}

static void put_gid_entry(struct ib_gid_table_entry *entry)
{
	kref_put(&entry->kref, schedule_free_gid);
}

static void put_gid_entry_locked(struct ib_gid_table_entry *entry)
{
	kref_put(&entry->kref, free_gid_entry);
}

static int add_roce_gid(struct ib_gid_table_entry *entry)
{
	const struct ib_gid_attr *attr = &entry->attr;
	int ret;

	if (!attr->ndev) {
		pr_err("%s NULL netdev device=%s port=%d index=%d\n",
		       __func__, attr->device->name, attr->port_num,
		       attr->index);
		return -EINVAL;
	}
	if (rdma_cap_roce_gid_table(attr->device, attr->port_num)) {
		ret = attr->device->add_gid(attr, &entry->context);
		if (ret) {
			pr_err("%s GID add failed device=%s port=%d index=%d\n",
			       __func__, attr->device->name, attr->port_num,
			       attr->index);
			return ret;
		}
	}
	return 0;
}

/**
 * del_gid - Delete GID table entry
 *
 * @ib_dev:	IB device whose GID entry to be deleted
 * @port:	Port number of the IB device
 * @table:	GID table of the IB device for a port
 * @ix:		GID entry index to delete
 *
 */
static void del_gid(struct ib_device *ib_dev, u8 port,
		    struct ib_gid_table *table, int ix)
{
	struct ib_gid_table_entry *entry;

	lockdep_assert_held(&table->lock);

	pr_debug("%s device=%s port=%d index=%d gid %pI6\n", __func__,
		 ib_dev->name, port, ix,
		 table->data_vec[ix]->attr.gid.raw);

	write_lock_irq(&table->rwlock);
	entry = table->data_vec[ix];
	entry->state = GID_TABLE_ENTRY_PENDING_DEL;
	/*
	 * For non RoCE protocol, GID entry slot is ready to use.
	 */
	if (!rdma_protocol_roce(ib_dev, port))
		table->data_vec[ix] = NULL;
	write_unlock_irq(&table->rwlock);

	put_gid_entry_locked(entry);
}

/**
 * add_modify_gid - Add or modify GID table entry
 *
 * @table:	GID table in which GID to be added or modified
 * @attr:	Attributes of the GID
 *
 * Returns 0 on success or appropriate error code. It accepts zero
 * GID addition for non RoCE ports for HCA's who report them as valid
 * GID. However such zero GIDs are not added to the cache.
 */
static int add_modify_gid(struct ib_gid_table *table,
			  const struct ib_gid_attr *attr)
{
	struct ib_gid_table_entry *entry;
	int ret = 0;

	/*
	 * Invalidate any old entry in the table to make it safe to write to
	 * this index.
	 */
	if (is_gid_entry_valid(table->data_vec[attr->index]))
		del_gid(attr->device, attr->port_num, table, attr->index);

	/*
	 * Some HCA's report multiple GID entries with only one valid GID, and
	 * leave other unused entries as the zero GID. Convert zero GIDs to
	 * empty table entries instead of storing them.
	 */
	if (rdma_is_zero_gid(&attr->gid))
		return 0;

	entry = alloc_gid_entry(attr);
	if (!entry)
		return -ENOMEM;

	if (rdma_protocol_roce(attr->device, attr->port_num)) {
		ret = add_roce_gid(entry);
		if (ret)
			goto done;
	}

	store_gid_entry(table, entry);
	return 0;

done:
	put_gid_entry(entry);
	return ret;
}

/* rwlock should be read locked, or lock should be held */
=======
/* This function expects that rwlock will be write locked in all
 * scenarios and that lock will be locked in sleep-able (RoCE)
 * scenarios.
 */
static int write_gid(struct ib_device *ib_dev, u8 port,
		     struct ib_gid_table *table, int ix,
		     const union ib_gid *gid,
		     const struct ib_gid_attr *attr,
		     enum gid_table_write_action action,
		     bool  default_gid)
	__releases(&table->rwlock) __acquires(&table->rwlock)
{
	int ret = 0;
	struct net_device *old_net_dev;
	enum ib_gid_type old_gid_type;

	/* in rdma_cap_roce_gid_table, this funciton should be protected by a
	 * sleep-able lock.
	 */

	if (rdma_cap_roce_gid_table(ib_dev, port)) {
		table->data_vec[ix].props |= GID_TABLE_ENTRY_INVALID;
		write_unlock_irq(&table->rwlock);
		/* GID_TABLE_WRITE_ACTION_MODIFY currently isn't supported by
		 * RoCE providers and thus only updates the cache.
		 */
		if (action == GID_TABLE_WRITE_ACTION_ADD)
			ret = ib_dev->add_gid(ib_dev, port, ix, gid, attr,
					      &table->data_vec[ix].context);
		else if (action == GID_TABLE_WRITE_ACTION_DEL)
			ret = ib_dev->del_gid(ib_dev, port, ix,
					      &table->data_vec[ix].context);
		write_lock_irq(&table->rwlock);
	}

	old_net_dev = table->data_vec[ix].attr.ndev;
	old_gid_type = table->data_vec[ix].attr.gid_type;
	if (old_net_dev && old_net_dev != attr->ndev)
		dev_put(old_net_dev);
	/* if modify_gid failed, just delete the old gid */
	if (ret || action == GID_TABLE_WRITE_ACTION_DEL) {
		gid = &zgid;
		attr = &zattr;
		table->data_vec[ix].context = NULL;
	}

	memcpy(&table->data_vec[ix].gid, gid, sizeof(*gid));
	memcpy(&table->data_vec[ix].attr, attr, sizeof(*attr));
	if (default_gid) {
		table->data_vec[ix].props |= GID_TABLE_ENTRY_DEFAULT;
		if (action == GID_TABLE_WRITE_ACTION_DEL)
			table->data_vec[ix].attr.gid_type = old_gid_type;
	}
	if (table->data_vec[ix].attr.ndev &&
	    table->data_vec[ix].attr.ndev != old_net_dev)
		dev_hold(table->data_vec[ix].attr.ndev);

	table->data_vec[ix].props &= ~GID_TABLE_ENTRY_INVALID;

	return ret;
}

static int add_gid(struct ib_device *ib_dev, u8 port,
		   struct ib_gid_table *table, int ix,
		   const union ib_gid *gid,
		   const struct ib_gid_attr *attr,
		   bool  default_gid) {
	return write_gid(ib_dev, port, table, ix, gid, attr,
			 GID_TABLE_WRITE_ACTION_ADD, default_gid);
}

static int modify_gid(struct ib_device *ib_dev, u8 port,
		      struct ib_gid_table *table, int ix,
		      const union ib_gid *gid,
		      const struct ib_gid_attr *attr,
		      bool  default_gid) {
	return write_gid(ib_dev, port, table, ix, gid, attr,
			 GID_TABLE_WRITE_ACTION_MODIFY, default_gid);
}

static int del_gid(struct ib_device *ib_dev, u8 port,
		   struct ib_gid_table *table, int ix,
		   bool  default_gid) {
	return write_gid(ib_dev, port, table, ix, &zgid, &zattr,
			 GID_TABLE_WRITE_ACTION_DEL, default_gid);
}

/* rwlock should be read locked */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int find_gid(struct ib_gid_table *table, const union ib_gid *gid,
		    const struct ib_gid_attr *val, bool default_gid,
		    unsigned long mask, int *pempty)
{
	int i = 0;
	int found = -1;
	int empty = pempty ? -1 : 0;

	while (i < table->sz && (found < 0 || empty < 0)) {
<<<<<<< HEAD
		struct ib_gid_table_entry *data = table->data_vec[i];
		struct ib_gid_attr *attr;
=======
		struct ib_gid_table_entry *data = &table->data_vec[i];
		struct ib_gid_attr *attr = &data->attr;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		int curr_index = i;

		i++;

<<<<<<< HEAD
		/* find_gid() is used during GID addition where it is expected
		 * to return a free entry slot which is not duplicate.
		 * Free entry slot is requested and returned if pempty is set,
		 * so lookup free slot only if requested.
		 */
		if (pempty && empty < 0) {
			if (is_gid_entry_free(data) &&
			    default_gid ==
				is_gid_index_default(table, curr_index)) {
				/*
				 * Found an invalid (free) entry; allocate it.
				 * If default GID is requested, then our
				 * found slot must be one of the DEFAULT
				 * reserved slots or we fail.
				 * This ensures that only DEFAULT reserved
				 * slots are used for default property GIDs.
				 */
				empty = curr_index;
			}
		}

		/*
		 * Additionally find_gid() is used to find valid entry during
		 * lookup operation; so ignore the entries which are marked as
		 * pending for removal and the entries which are marked as
		 * invalid.
		 */
		if (!is_gid_entry_valid(data))
			continue;

		if (found >= 0)
			continue;

		attr = &data->attr;
=======
		if (data->props & GID_TABLE_ENTRY_INVALID)
			continue;

		if (empty < 0)
			if (!memcmp(&data->gid, &zgid, sizeof(*gid)) &&
			    !memcmp(attr, &zattr, sizeof(*attr)) &&
			    !data->props)
				empty = curr_index;

		if (found >= 0)
			continue;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (mask & GID_ATTR_FIND_MASK_GID_TYPE &&
		    attr->gid_type != val->gid_type)
			continue;

		if (mask & GID_ATTR_FIND_MASK_GID &&
<<<<<<< HEAD
		    memcmp(gid, &data->attr.gid, sizeof(*gid)))
=======
		    memcmp(gid, &data->gid, sizeof(*gid)))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			continue;

		if (mask & GID_ATTR_FIND_MASK_NETDEV &&
		    attr->ndev != val->ndev)
			continue;

		if (mask & GID_ATTR_FIND_MASK_DEFAULT &&
<<<<<<< HEAD
		    is_gid_index_default(table, curr_index) != default_gid)
=======
		    !!(data->props & GID_TABLE_ENTRY_DEFAULT) !=
		    default_gid)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			continue;

		found = curr_index;
	}

	if (pempty)
		*pempty = empty;

	return found;
}

static void make_default_gid(struct  net_device *dev, union ib_gid *gid)
{
	gid->global.subnet_prefix = cpu_to_be64(0xfe80000000000000LL);
	addrconf_ifid_eui48(&gid->raw[8], dev);
}

<<<<<<< HEAD
static int __ib_cache_gid_add(struct ib_device *ib_dev, u8 port,
			      union ib_gid *gid, struct ib_gid_attr *attr,
			      unsigned long mask, bool default_gid)
{
	struct ib_gid_table *table;
	int ret = 0;
	int empty;
	int ix;

	/* Do not allow adding zero GID in support of
	 * IB spec version 1.3 section 4.1.1 point (6) and
	 * section 12.7.10 and section 12.7.20
	 */
	if (rdma_is_zero_gid(gid))
		return -EINVAL;

	table = rdma_gid_table(ib_dev, port);

	mutex_lock(&table->lock);

	ix = find_gid(table, gid, attr, default_gid, mask, &empty);
	if (ix >= 0)
		goto out_unlock;

	if (empty < 0) {
		ret = -ENOSPC;
		goto out_unlock;
	}
	attr->device = ib_dev;
	attr->index = empty;
	attr->port_num = port;
	attr->gid = *gid;
	ret = add_modify_gid(table, attr);
	if (!ret)
		dispatch_gid_change_event(ib_dev, port);

out_unlock:
	mutex_unlock(&table->lock);
	if (ret)
		pr_warn("%s: unable to add gid %pI6 error=%d\n",
			__func__, gid->raw, ret);
	return ret;
}

int ib_cache_gid_add(struct ib_device *ib_dev, u8 port,
		     union ib_gid *gid, struct ib_gid_attr *attr)
{
	struct net_device *idev;
	unsigned long mask;
	int ret;
=======
int ib_cache_gid_add(struct ib_device *ib_dev, u8 port,
		     union ib_gid *gid, struct ib_gid_attr *attr)
{
	struct ib_gid_table *table;
	int ix;
	int ret = 0;
	struct net_device *idev;
	int empty;

	table = ib_dev->cache.ports[port - rdma_start_port(ib_dev)].gid;

	if (!memcmp(gid, &zgid, sizeof(*gid)))
		return -EINVAL;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (ib_dev->get_netdev) {
		idev = ib_dev->get_netdev(ib_dev, port);
		if (idev && attr->ndev != idev) {
			union ib_gid default_gid;

			/* Adding default GIDs in not permitted */
			make_default_gid(idev, &default_gid);
			if (!memcmp(gid, &default_gid, sizeof(*gid))) {
				dev_put(idev);
				return -EPERM;
			}
		}
		if (idev)
			dev_put(idev);
	}

<<<<<<< HEAD
	mask = GID_ATTR_FIND_MASK_GID |
	       GID_ATTR_FIND_MASK_GID_TYPE |
	       GID_ATTR_FIND_MASK_NETDEV;

	ret = __ib_cache_gid_add(ib_dev, port, gid, attr, mask, false);
	return ret;
}

static int
_ib_cache_gid_del(struct ib_device *ib_dev, u8 port,
		  union ib_gid *gid, struct ib_gid_attr *attr,
		  unsigned long mask, bool default_gid)
{
	struct ib_gid_table *table;
	int ret = 0;
	int ix;

	table = rdma_gid_table(ib_dev, port);

	mutex_lock(&table->lock);

	ix = find_gid(table, gid, attr, default_gid, mask, NULL);
	if (ix < 0) {
		ret = -EINVAL;
		goto out_unlock;
	}

	del_gid(ib_dev, port, table, ix);
	dispatch_gid_change_event(ib_dev, port);

out_unlock:
	mutex_unlock(&table->lock);
	if (ret)
		pr_debug("%s: can't delete gid %pI6 error=%d\n",
			 __func__, gid->raw, ret);
=======
	mutex_lock(&table->lock);
	write_lock_irq(&table->rwlock);

	ix = find_gid(table, gid, attr, false, GID_ATTR_FIND_MASK_GID |
		      GID_ATTR_FIND_MASK_GID_TYPE |
		      GID_ATTR_FIND_MASK_NETDEV, &empty);
	if (ix >= 0)
		goto out_unlock;

	if (empty < 0) {
		ret = -ENOSPC;
		goto out_unlock;
	}

	ret = add_gid(ib_dev, port, table, empty, gid, attr, false);
	if (!ret)
		dispatch_gid_change_event(ib_dev, port);

out_unlock:
	write_unlock_irq(&table->rwlock);
	mutex_unlock(&table->lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

int ib_cache_gid_del(struct ib_device *ib_dev, u8 port,
		     union ib_gid *gid, struct ib_gid_attr *attr)
{
<<<<<<< HEAD
	unsigned long mask = GID_ATTR_FIND_MASK_GID	  |
			     GID_ATTR_FIND_MASK_GID_TYPE |
			     GID_ATTR_FIND_MASK_DEFAULT  |
			     GID_ATTR_FIND_MASK_NETDEV;

	return _ib_cache_gid_del(ib_dev, port, gid, attr, mask, false);
=======
	struct ib_gid_table *table;
	int ix;

	table = ib_dev->cache.ports[port - rdma_start_port(ib_dev)].gid;

	mutex_lock(&table->lock);
	write_lock_irq(&table->rwlock);

	ix = find_gid(table, gid, attr, false,
		      GID_ATTR_FIND_MASK_GID	  |
		      GID_ATTR_FIND_MASK_GID_TYPE |
		      GID_ATTR_FIND_MASK_NETDEV	  |
		      GID_ATTR_FIND_MASK_DEFAULT,
		      NULL);
	if (ix < 0)
		goto out_unlock;

	if (!del_gid(ib_dev, port, table, ix, false))
		dispatch_gid_change_event(ib_dev, port);

out_unlock:
	write_unlock_irq(&table->rwlock);
	mutex_unlock(&table->lock);
	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

int ib_cache_gid_del_all_netdev_gids(struct ib_device *ib_dev, u8 port,
				     struct net_device *ndev)
{
	struct ib_gid_table *table;
	int ix;
	bool deleted = false;

<<<<<<< HEAD
	table = rdma_gid_table(ib_dev, port);

	mutex_lock(&table->lock);

	for (ix = 0; ix < table->sz; ix++) {
		if (is_gid_entry_valid(table->data_vec[ix]) &&
		    table->data_vec[ix]->attr.ndev == ndev) {
			del_gid(ib_dev, port, table, ix);
			deleted = true;
		}
	}

=======
	table = ib_dev->cache.ports[port - rdma_start_port(ib_dev)].gid;

	mutex_lock(&table->lock);
	write_lock_irq(&table->rwlock);

	for (ix = 0; ix < table->sz; ix++)
		if (table->data_vec[ix].attr.ndev == ndev)
			if (!del_gid(ib_dev, port, table, ix,
				     !!(table->data_vec[ix].props &
					GID_TABLE_ENTRY_DEFAULT)))
				deleted = true;

	write_unlock_irq(&table->rwlock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mutex_unlock(&table->lock);

	if (deleted)
		dispatch_gid_change_event(ib_dev, port);

	return 0;
}

<<<<<<< HEAD
/**
 * rdma_find_gid_by_port - Returns the GID entry attributes when it finds
 * a valid GID entry for given search parameters. It searches for the specified
 * GID value in the local software cache.
 * @device: The device to query.
 * @gid: The GID value to search for.
 * @gid_type: The GID type to search for.
 * @port_num: The port number of the device where the GID value should be
 *   searched.
 * @ndev: In RoCE, the net device of the device. NULL means ignore.
 *
 * Returns sgid attributes if the GID is found with valid reference or
 * returns ERR_PTR for the error.
 * The caller must invoke rdma_put_gid_attr() to release the reference.
 */
const struct ib_gid_attr *
rdma_find_gid_by_port(struct ib_device *ib_dev,
		      const union ib_gid *gid,
		      enum ib_gid_type gid_type,
		      u8 port, struct net_device *ndev)
=======
static int __ib_cache_gid_get(struct ib_device *ib_dev, u8 port, int index,
			      union ib_gid *gid, struct ib_gid_attr *attr)
{
	struct ib_gid_table *table;

	table = ib_dev->cache.ports[port - rdma_start_port(ib_dev)].gid;

	if (index < 0 || index >= table->sz)
		return -EINVAL;

	if (table->data_vec[index].props & GID_TABLE_ENTRY_INVALID)
		return -EINVAL;

	memcpy(gid, &table->data_vec[index].gid, sizeof(*gid));
	if (attr) {
		memcpy(attr, &table->data_vec[index].attr, sizeof(*attr));
		if (attr->ndev)
			dev_hold(attr->ndev);
	}

	return 0;
}

static int _ib_cache_gid_table_find(struct ib_device *ib_dev,
				    const union ib_gid *gid,
				    const struct ib_gid_attr *val,
				    unsigned long mask,
				    u8 *port, u16 *index)
{
	struct ib_gid_table *table;
	u8 p;
	int local_index;
	unsigned long flags;

	for (p = 0; p < ib_dev->phys_port_cnt; p++) {
		table = ib_dev->cache.ports[p].gid;
		read_lock_irqsave(&table->rwlock, flags);
		local_index = find_gid(table, gid, val, false, mask, NULL);
		if (local_index >= 0) {
			if (index)
				*index = local_index;
			if (port)
				*port = p + rdma_start_port(ib_dev);
			read_unlock_irqrestore(&table->rwlock, flags);
			return 0;
		}
		read_unlock_irqrestore(&table->rwlock, flags);
	}

	return -ENOENT;
}

static int ib_cache_gid_find(struct ib_device *ib_dev,
			     const union ib_gid *gid,
			     enum ib_gid_type gid_type,
			     struct net_device *ndev, u8 *port,
			     u16 *index)
{
	unsigned long mask = GID_ATTR_FIND_MASK_GID |
			     GID_ATTR_FIND_MASK_GID_TYPE;
	struct ib_gid_attr gid_attr_val = {.ndev = ndev, .gid_type = gid_type};

	if (ndev)
		mask |= GID_ATTR_FIND_MASK_NETDEV;

	return _ib_cache_gid_table_find(ib_dev, gid, &gid_attr_val,
					mask, port, index);
}

int ib_find_cached_gid_by_port(struct ib_device *ib_dev,
			       const union ib_gid *gid,
			       enum ib_gid_type gid_type,
			       u8 port, struct net_device *ndev,
			       u16 *index)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	int local_index;
	struct ib_gid_table *table;
	unsigned long mask = GID_ATTR_FIND_MASK_GID |
			     GID_ATTR_FIND_MASK_GID_TYPE;
	struct ib_gid_attr val = {.ndev = ndev, .gid_type = gid_type};
<<<<<<< HEAD
	const struct ib_gid_attr *attr;
	unsigned long flags;

	if (!rdma_is_port_valid(ib_dev, port))
		return ERR_PTR(-ENOENT);

	table = rdma_gid_table(ib_dev, port);
=======
	unsigned long flags;

	if (!rdma_is_port_valid(ib_dev, port))
		return -ENOENT;

	table = ib_dev->cache.ports[port - rdma_start_port(ib_dev)].gid;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (ndev)
		mask |= GID_ATTR_FIND_MASK_NETDEV;

	read_lock_irqsave(&table->rwlock, flags);
	local_index = find_gid(table, gid, &val, false, mask, NULL);
	if (local_index >= 0) {
<<<<<<< HEAD
		get_gid_entry(table->data_vec[local_index]);
		attr = &table->data_vec[local_index]->attr;
		read_unlock_irqrestore(&table->rwlock, flags);
		return attr;
	}

	read_unlock_irqrestore(&table->rwlock, flags);
	return ERR_PTR(-ENOENT);
}
EXPORT_SYMBOL(rdma_find_gid_by_port);

/**
 * rdma_find_gid_by_filter - Returns the GID table attribute where a
 * specified GID value occurs
 * @device: The device to query.
 * @gid: The GID value to search for.
 * @port: The port number of the device where the GID value could be
=======
		if (index)
			*index = local_index;
		read_unlock_irqrestore(&table->rwlock, flags);
		return 0;
	}

	read_unlock_irqrestore(&table->rwlock, flags);
	return -ENOENT;
}
EXPORT_SYMBOL(ib_find_cached_gid_by_port);

/**
 * ib_find_gid_by_filter - Returns the GID table index where a specified
 * GID value occurs
 * @device: The device to query.
 * @gid: The GID value to search for.
 * @port_num: The port number of the device where the GID value could be
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *   searched.
 * @filter: The filter function is executed on any matching GID in the table.
 *   If the filter function returns true, the corresponding index is returned,
 *   otherwise, we continue searching the GID table. It's guaranteed that
 *   while filter is executed, ndev field is valid and the structure won't
 *   change. filter is executed in an atomic context. filter must not be NULL.
<<<<<<< HEAD
 *
 * rdma_find_gid_by_filter() searches for the specified GID value
 * of which the filter function returns true in the port's GID table.
 *
 */
const struct ib_gid_attr *rdma_find_gid_by_filter(
	struct ib_device *ib_dev, const union ib_gid *gid, u8 port,
	bool (*filter)(const union ib_gid *gid, const struct ib_gid_attr *,
		       void *),
	void *context)
{
	const struct ib_gid_attr *res = ERR_PTR(-ENOENT);
	struct ib_gid_table *table;
	unsigned long flags;
	unsigned int i;

	if (!rdma_is_port_valid(ib_dev, port))
		return ERR_PTR(-EINVAL);

	table = rdma_gid_table(ib_dev, port);

	read_lock_irqsave(&table->rwlock, flags);
	for (i = 0; i < table->sz; i++) {
		struct ib_gid_table_entry *entry = table->data_vec[i];

		if (!is_gid_entry_valid(entry))
			continue;

		if (memcmp(gid, &entry->attr.gid, sizeof(*gid)))
			continue;

		if (filter(gid, &entry->attr, context)) {
			get_gid_entry(entry);
			res = &entry->attr;
			break;
		}
	}
	read_unlock_irqrestore(&table->rwlock, flags);
	return res;
=======
 * @index: The index into the cached GID table where the GID was found.  This
 *   parameter may be NULL.
 *
 * ib_cache_gid_find_by_filter() searches for the specified GID value
 * of which the filter function returns true in the port's GID table.
 * This function is only supported on RoCE ports.
 *
 */
static int ib_cache_gid_find_by_filter(struct ib_device *ib_dev,
				       const union ib_gid *gid,
				       u8 port,
				       bool (*filter)(const union ib_gid *,
						      const struct ib_gid_attr *,
						      void *),
				       void *context,
				       u16 *index)
{
	struct ib_gid_table *table;
	unsigned int i;
	unsigned long flags;
	bool found = false;


	if (!rdma_is_port_valid(ib_dev, port) ||
	    !rdma_protocol_roce(ib_dev, port))
		return -EPROTONOSUPPORT;

	table = ib_dev->cache.ports[port - rdma_start_port(ib_dev)].gid;

	read_lock_irqsave(&table->rwlock, flags);
	for (i = 0; i < table->sz; i++) {
		struct ib_gid_attr attr;

		if (table->data_vec[i].props & GID_TABLE_ENTRY_INVALID)
			goto next;

		if (memcmp(gid, &table->data_vec[i].gid, sizeof(*gid)))
			goto next;

		memcpy(&attr, &table->data_vec[i].attr, sizeof(attr));

		if (filter(gid, &attr, context))
			found = true;

next:
		if (found)
			break;
	}
	read_unlock_irqrestore(&table->rwlock, flags);

	if (!found)
		return -ENOENT;

	if (index)
		*index = i;
	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static struct ib_gid_table *alloc_gid_table(int sz)
{
<<<<<<< HEAD
	struct ib_gid_table *table = kzalloc(sizeof(*table), GFP_KERNEL);
=======
	struct ib_gid_table *table =
		kzalloc(sizeof(struct ib_gid_table), GFP_KERNEL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!table)
		return NULL;

	table->data_vec = kcalloc(sz, sizeof(*table->data_vec), GFP_KERNEL);
	if (!table->data_vec)
		goto err_free_table;

	mutex_init(&table->lock);

	table->sz = sz;
	rwlock_init(&table->rwlock);
<<<<<<< HEAD
=======

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return table;

err_free_table:
	kfree(table);
	return NULL;
}

<<<<<<< HEAD
static void release_gid_table(struct ib_device *device, u8 port,
			      struct ib_gid_table *table)
{
	bool leak = false;
	int i;

	if (!table)
		return;

	for (i = 0; i < table->sz; i++) {
		if (is_gid_entry_free(table->data_vec[i]))
			continue;
		if (kref_read(&table->data_vec[i]->kref) > 1) {
			pr_err("GID entry ref leak for %s (index %d) ref=%d\n",
			       device->name, i,
			       kref_read(&table->data_vec[i]->kref));
			leak = true;
		}
	}
	if (leak)
		return;

	kfree(table->data_vec);
	kfree(table);
=======
static void release_gid_table(struct ib_gid_table *table)
{
	if (table) {
		kfree(table->data_vec);
		kfree(table);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void cleanup_gid_table_port(struct ib_device *ib_dev, u8 port,
				   struct ib_gid_table *table)
{
	int i;
	bool deleted = false;

	if (!table)
		return;

<<<<<<< HEAD
	mutex_lock(&table->lock);
	for (i = 0; i < table->sz; ++i) {
		if (is_gid_entry_valid(table->data_vec[i])) {
			del_gid(ib_dev, port, table, i);
			deleted = true;
		}
	}
	mutex_unlock(&table->lock);
=======
	write_lock_irq(&table->rwlock);
	for (i = 0; i < table->sz; ++i) {
		if (memcmp(&table->data_vec[i].gid, &zgid,
			   sizeof(table->data_vec[i].gid)))
			if (!del_gid(ib_dev, port, table, i,
				     table->data_vec[i].props &
				     GID_ATTR_FIND_MASK_DEFAULT))
				deleted = true;
	}
	write_unlock_irq(&table->rwlock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (deleted)
		dispatch_gid_change_event(ib_dev, port);
}

void ib_cache_gid_set_default_gid(struct ib_device *ib_dev, u8 port,
				  struct net_device *ndev,
				  unsigned long gid_type_mask,
				  enum ib_cache_gid_default_mode mode)
{
<<<<<<< HEAD
	union ib_gid gid = { };
	struct ib_gid_attr gid_attr;
	unsigned int gid_type;
	unsigned long mask;

	mask = GID_ATTR_FIND_MASK_GID_TYPE |
	       GID_ATTR_FIND_MASK_DEFAULT |
	       GID_ATTR_FIND_MASK_NETDEV;
=======
	union ib_gid gid;
	struct ib_gid_attr gid_attr;
	struct ib_gid_attr zattr_type = zattr;
	struct ib_gid_table *table;
	unsigned int gid_type;

	table = ib_dev->cache.ports[port - rdma_start_port(ib_dev)].gid;

	make_default_gid(ndev, &gid);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	memset(&gid_attr, 0, sizeof(gid_attr));
	gid_attr.ndev = ndev;

	for (gid_type = 0; gid_type < IB_GID_TYPE_SIZE; ++gid_type) {
<<<<<<< HEAD
=======
		int ix;
		union ib_gid current_gid;
		struct ib_gid_attr current_gid_attr = {};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (1UL << gid_type & ~gid_type_mask)
			continue;

		gid_attr.gid_type = gid_type;

<<<<<<< HEAD
		if (mode == IB_CACHE_GID_DEFAULT_MODE_SET) {
			make_default_gid(ndev, &gid);
			__ib_cache_gid_add(ib_dev, port, &gid,
					   &gid_attr, mask, true);
		} else if (mode == IB_CACHE_GID_DEFAULT_MODE_DELETE) {
			_ib_cache_gid_del(ib_dev, port, &gid,
					  &gid_attr, mask, true);
		}
	}
}

static void gid_table_reserve_default(struct ib_device *ib_dev, u8 port,
				      struct ib_gid_table *table)
=======
		mutex_lock(&table->lock);
		write_lock_irq(&table->rwlock);
		ix = find_gid(table, NULL, &gid_attr, true,
			      GID_ATTR_FIND_MASK_GID_TYPE |
			      GID_ATTR_FIND_MASK_DEFAULT,
			      NULL);

		/* Coudn't find default GID location */
		if (WARN_ON(ix < 0))
			goto release;

		zattr_type.gid_type = gid_type;

		if (!__ib_cache_gid_get(ib_dev, port, ix,
					&current_gid, &current_gid_attr) &&
		    mode == IB_CACHE_GID_DEFAULT_MODE_SET &&
		    !memcmp(&gid, &current_gid, sizeof(gid)) &&
		    !memcmp(&gid_attr, &current_gid_attr, sizeof(gid_attr)))
			goto release;

		if (memcmp(&current_gid, &zgid, sizeof(current_gid)) ||
		    memcmp(&current_gid_attr, &zattr_type,
			   sizeof(current_gid_attr))) {
			if (del_gid(ib_dev, port, table, ix, true)) {
				pr_warn("ib_cache_gid: can't delete index %d for default gid %pI6\n",
					ix, gid.raw);
				goto release;
			} else {
				dispatch_gid_change_event(ib_dev, port);
			}
		}

		if (mode == IB_CACHE_GID_DEFAULT_MODE_SET) {
			if (add_gid(ib_dev, port, table, ix, &gid, &gid_attr, true))
				pr_warn("ib_cache_gid: unable to add default gid %pI6\n",
					gid.raw);
			else
				dispatch_gid_change_event(ib_dev, port);
		}

release:
		if (current_gid_attr.ndev)
			dev_put(current_gid_attr.ndev);
		write_unlock_irq(&table->rwlock);
		mutex_unlock(&table->lock);
	}
}

static int gid_table_reserve_default(struct ib_device *ib_dev, u8 port,
				     struct ib_gid_table *table)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	unsigned int i;
	unsigned long roce_gid_type_mask;
	unsigned int num_default_gids;
<<<<<<< HEAD

	roce_gid_type_mask = roce_gid_type_mask_support(ib_dev, port);
	num_default_gids = hweight_long(roce_gid_type_mask);
	/* Reserve starting indices for default GIDs */
	for (i = 0; i < num_default_gids && i < table->sz; i++)
		table->default_gid_indices |= BIT(i);
}

=======
	unsigned int current_gid = 0;

	roce_gid_type_mask = roce_gid_type_mask_support(ib_dev, port);
	num_default_gids = hweight_long(roce_gid_type_mask);
	for (i = 0; i < num_default_gids && i < table->sz; i++) {
		struct ib_gid_table_entry *entry =
			&table->data_vec[i];

		entry->props |= GID_TABLE_ENTRY_DEFAULT;
		current_gid = find_next_bit(&roce_gid_type_mask,
					    BITS_PER_LONG,
					    current_gid);
		entry->attr.gid_type = current_gid++;
	}

	return 0;
}

static int _gid_table_setup_one(struct ib_device *ib_dev)
{
	u8 port;
	struct ib_gid_table *table;
	int err = 0;

	for (port = 0; port < ib_dev->phys_port_cnt; port++) {
		u8 rdma_port = port + rdma_start_port(ib_dev);

		table =
			alloc_gid_table(
				ib_dev->port_immutable[rdma_port].gid_tbl_len);
		if (!table) {
			err = -ENOMEM;
			goto rollback_table_setup;
		}

		err = gid_table_reserve_default(ib_dev,
						port + rdma_start_port(ib_dev),
						table);
		if (err)
			goto rollback_table_setup;
		ib_dev->cache.ports[port].gid = table;
	}

	return 0;

rollback_table_setup:
	for (port = 0; port < ib_dev->phys_port_cnt; port++) {
		table = ib_dev->cache.ports[port].gid;

		cleanup_gid_table_port(ib_dev, port + rdma_start_port(ib_dev),
				       table);
		release_gid_table(table);
	}

	return err;
}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static void gid_table_release_one(struct ib_device *ib_dev)
{
	struct ib_gid_table *table;
	u8 port;

	for (port = 0; port < ib_dev->phys_port_cnt; port++) {
		table = ib_dev->cache.ports[port].gid;
<<<<<<< HEAD
		release_gid_table(ib_dev, port, table);
=======
		release_gid_table(table);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		ib_dev->cache.ports[port].gid = NULL;
	}
}

<<<<<<< HEAD
static int _gid_table_setup_one(struct ib_device *ib_dev)
{
	u8 port;
	struct ib_gid_table *table;

	for (port = 0; port < ib_dev->phys_port_cnt; port++) {
		u8 rdma_port = port + rdma_start_port(ib_dev);

		table =	alloc_gid_table(
				ib_dev->port_immutable[rdma_port].gid_tbl_len);
		if (!table)
			goto rollback_table_setup;

		gid_table_reserve_default(ib_dev, rdma_port, table);
		ib_dev->cache.ports[port].gid = table;
	}
	return 0;

rollback_table_setup:
	gid_table_release_one(ib_dev);
	return -ENOMEM;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static void gid_table_cleanup_one(struct ib_device *ib_dev)
{
	struct ib_gid_table *table;
	u8 port;

	for (port = 0; port < ib_dev->phys_port_cnt; port++) {
		table = ib_dev->cache.ports[port].gid;
		cleanup_gid_table_port(ib_dev, port + rdma_start_port(ib_dev),
				       table);
	}
}

static int gid_table_setup_one(struct ib_device *ib_dev)
{
	int err;

	err = _gid_table_setup_one(ib_dev);

	if (err)
		return err;

<<<<<<< HEAD
	rdma_roce_rescan_device(ib_dev);
=======
	err = roce_rescan_device(ib_dev);

	if (err) {
		gid_table_cleanup_one(ib_dev);
		gid_table_release_one(ib_dev);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return err;
}

<<<<<<< HEAD
/**
 * rdma_query_gid - Read the GID content from the GID software cache
 * @device:		Device to query the GID
 * @port_num:		Port number of the device
 * @index:		Index of the GID table entry to read
 * @gid:		Pointer to GID where to store the entry's GID
 *
 * rdma_query_gid() only reads the GID entry content for requested device,
 * port and index. It reads for IB, RoCE and iWarp link layers.  It doesn't
 * hold any reference to the GID table entry in the HCA or software cache.
 *
 * Returns 0 on success or appropriate error code.
 *
 */
int rdma_query_gid(struct ib_device *device, u8 port_num,
		   int index, union ib_gid *gid)
{
	struct ib_gid_table *table;
	unsigned long flags;
	int res = -EINVAL;
=======
int ib_get_cached_gid(struct ib_device *device,
		      u8                port_num,
		      int               index,
		      union ib_gid     *gid,
		      struct ib_gid_attr *gid_attr)
{
	int res;
	unsigned long flags;
	struct ib_gid_table *table;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

<<<<<<< HEAD
	table = rdma_gid_table(device, port_num);
	read_lock_irqsave(&table->rwlock, flags);

	if (index < 0 || index >= table->sz ||
	    !is_gid_entry_valid(table->data_vec[index]))
		goto done;

	memcpy(gid, &table->data_vec[index]->attr.gid, sizeof(*gid));
	res = 0;

done:
	read_unlock_irqrestore(&table->rwlock, flags);
	return res;
}
EXPORT_SYMBOL(rdma_query_gid);

/**
 * rdma_find_gid - Returns SGID attributes if the matching GID is found.
 * @device: The device to query.
 * @gid: The GID value to search for.
 * @gid_type: The GID type to search for.
 * @ndev: In RoCE, the net device of the device. NULL means ignore.
 *
 * rdma_find_gid() searches for the specified GID value in the software cache.
 *
 * Returns GID attributes if a valid GID is found or returns ERR_PTR for the
 * error. The caller must invoke rdma_put_gid_attr() to release the reference.
 *
 */
const struct ib_gid_attr *rdma_find_gid(struct ib_device *device,
					const union ib_gid *gid,
					enum ib_gid_type gid_type,
					struct net_device *ndev)
{
	unsigned long mask = GID_ATTR_FIND_MASK_GID |
			     GID_ATTR_FIND_MASK_GID_TYPE;
	struct ib_gid_attr gid_attr_val = {.ndev = ndev, .gid_type = gid_type};
	u8 p;

	if (ndev)
		mask |= GID_ATTR_FIND_MASK_NETDEV;

	for (p = 0; p < device->phys_port_cnt; p++) {
		struct ib_gid_table *table;
		unsigned long flags;
		int index;

		table = device->cache.ports[p].gid;
		read_lock_irqsave(&table->rwlock, flags);
		index = find_gid(table, gid, &gid_attr_val, false, mask, NULL);
		if (index >= 0) {
			const struct ib_gid_attr *attr;

			get_gid_entry(table->data_vec[index]);
			attr = &table->data_vec[index]->attr;
			read_unlock_irqrestore(&table->rwlock, flags);
			return attr;
		}
		read_unlock_irqrestore(&table->rwlock, flags);
	}

	return ERR_PTR(-ENOENT);
}
EXPORT_SYMBOL(rdma_find_gid);
=======
	table = device->cache.ports[port_num - rdma_start_port(device)].gid;
	read_lock_irqsave(&table->rwlock, flags);
	res = __ib_cache_gid_get(device, port_num, index, gid, gid_attr);
	read_unlock_irqrestore(&table->rwlock, flags);

	return res;
}
EXPORT_SYMBOL(ib_get_cached_gid);

int ib_find_cached_gid(struct ib_device *device,
		       const union ib_gid *gid,
		       enum ib_gid_type gid_type,
		       struct net_device *ndev,
		       u8               *port_num,
		       u16              *index)
{
	return ib_cache_gid_find(device, gid, gid_type, ndev, port_num, index);
}
EXPORT_SYMBOL(ib_find_cached_gid);

int ib_find_gid_by_filter(struct ib_device *device,
			  const union ib_gid *gid,
			  u8 port_num,
			  bool (*filter)(const union ib_gid *gid,
					 const struct ib_gid_attr *,
					 void *),
			  void *context, u16 *index)
{
	/* Only RoCE GID table supports filter function */
	if (!rdma_cap_roce_gid_table(device, port_num) && filter)
		return -EPROTONOSUPPORT;

	return ib_cache_gid_find_by_filter(device, gid,
					   port_num, filter,
					   context, index);
}
EXPORT_SYMBOL(ib_find_gid_by_filter);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

int ib_get_cached_pkey(struct ib_device *device,
		       u8                port_num,
		       int               index,
		       u16              *pkey)
{
	struct ib_pkey_cache *cache;
	unsigned long flags;
	int ret = 0;

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

	read_lock_irqsave(&device->cache.lock, flags);

	cache = device->cache.ports[port_num - rdma_start_port(device)].pkey;

	if (index < 0 || index >= cache->table_len)
		ret = -EINVAL;
	else
		*pkey = cache->table[index];

	read_unlock_irqrestore(&device->cache.lock, flags);

	return ret;
}
EXPORT_SYMBOL(ib_get_cached_pkey);

int ib_get_cached_subnet_prefix(struct ib_device *device,
				u8                port_num,
				u64              *sn_pfx)
{
	unsigned long flags;
	int p;

<<<<<<< HEAD
	if (!rdma_is_port_valid(device, port_num))
=======
	if (port_num < rdma_start_port(device) ||
	    port_num > rdma_end_port(device))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;

	p = port_num - rdma_start_port(device);
	read_lock_irqsave(&device->cache.lock, flags);
	*sn_pfx = device->cache.ports[p].subnet_prefix;
	read_unlock_irqrestore(&device->cache.lock, flags);

	return 0;
}
EXPORT_SYMBOL(ib_get_cached_subnet_prefix);

int ib_find_cached_pkey(struct ib_device *device,
			u8                port_num,
			u16               pkey,
			u16              *index)
{
	struct ib_pkey_cache *cache;
	unsigned long flags;
	int i;
	int ret = -ENOENT;
	int partial_ix = -1;

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

	read_lock_irqsave(&device->cache.lock, flags);

	cache = device->cache.ports[port_num - rdma_start_port(device)].pkey;

	*index = -1;

	for (i = 0; i < cache->table_len; ++i)
		if ((cache->table[i] & 0x7fff) == (pkey & 0x7fff)) {
			if (cache->table[i] & 0x8000) {
				*index = i;
				ret = 0;
				break;
			} else
				partial_ix = i;
		}

	if (ret && partial_ix >= 0) {
		*index = partial_ix;
		ret = 0;
	}

	read_unlock_irqrestore(&device->cache.lock, flags);

	return ret;
}
EXPORT_SYMBOL(ib_find_cached_pkey);

int ib_find_exact_cached_pkey(struct ib_device *device,
			      u8                port_num,
			      u16               pkey,
			      u16              *index)
{
	struct ib_pkey_cache *cache;
	unsigned long flags;
	int i;
	int ret = -ENOENT;

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

	read_lock_irqsave(&device->cache.lock, flags);

	cache = device->cache.ports[port_num - rdma_start_port(device)].pkey;

	*index = -1;

	for (i = 0; i < cache->table_len; ++i)
		if (cache->table[i] == pkey) {
			*index = i;
			ret = 0;
			break;
		}

	read_unlock_irqrestore(&device->cache.lock, flags);

	return ret;
}
EXPORT_SYMBOL(ib_find_exact_cached_pkey);

int ib_get_cached_lmc(struct ib_device *device,
		      u8                port_num,
		      u8                *lmc)
{
	unsigned long flags;
	int ret = 0;

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

	read_lock_irqsave(&device->cache.lock, flags);
	*lmc = device->cache.ports[port_num - rdma_start_port(device)].lmc;
	read_unlock_irqrestore(&device->cache.lock, flags);

	return ret;
}
EXPORT_SYMBOL(ib_get_cached_lmc);

int ib_get_cached_port_state(struct ib_device   *device,
			     u8                  port_num,
			     enum ib_port_state *port_state)
{
	unsigned long flags;
	int ret = 0;

<<<<<<< HEAD
	if (!rdma_is_port_valid(device, port_num))
=======
	if (port_num < rdma_start_port(device) || port_num > rdma_end_port(device))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;

	read_lock_irqsave(&device->cache.lock, flags);
	*port_state = device->cache.ports[port_num
		- rdma_start_port(device)].port_state;
	read_unlock_irqrestore(&device->cache.lock, flags);

	return ret;
}
EXPORT_SYMBOL(ib_get_cached_port_state);

<<<<<<< HEAD
/**
 * rdma_get_gid_attr - Returns GID attributes for a port of a device
 * at a requested gid_index, if a valid GID entry exists.
 * @device:		The device to query.
 * @port_num:		The port number on the device where the GID value
 *			is to be queried.
 * @index:		Index of the GID table entry whose attributes are to
 *                      be queried.
 *
 * rdma_get_gid_attr() acquires reference count of gid attributes from the
 * cached GID table. Caller must invoke rdma_put_gid_attr() to release
 * reference to gid attribute regardless of link layer.
 *
 * Returns pointer to valid gid attribute or ERR_PTR for the appropriate error
 * code.
 */
const struct ib_gid_attr *
rdma_get_gid_attr(struct ib_device *device, u8 port_num, int index)
{
	const struct ib_gid_attr *attr = ERR_PTR(-EINVAL);
	struct ib_gid_table *table;
	unsigned long flags;

	if (!rdma_is_port_valid(device, port_num))
		return ERR_PTR(-EINVAL);

	table = rdma_gid_table(device, port_num);
	if (index < 0 || index >= table->sz)
		return ERR_PTR(-EINVAL);

	read_lock_irqsave(&table->rwlock, flags);
	if (!is_gid_entry_valid(table->data_vec[index]))
		goto done;

	get_gid_entry(table->data_vec[index]);
	attr = &table->data_vec[index]->attr;
done:
	read_unlock_irqrestore(&table->rwlock, flags);
	return attr;
}
EXPORT_SYMBOL(rdma_get_gid_attr);

/**
 * rdma_put_gid_attr - Release reference to the GID attribute
 * @attr:		Pointer to the GID attribute whose reference
 *			needs to be released.
 *
 * rdma_put_gid_attr() must be used to release reference whose
 * reference is acquired using rdma_get_gid_attr() or any APIs
 * which returns a pointer to the ib_gid_attr regardless of link layer
 * of IB or RoCE.
 *
 */
void rdma_put_gid_attr(const struct ib_gid_attr *attr)
{
	struct ib_gid_table_entry *entry =
		container_of(attr, struct ib_gid_table_entry, attr);

	put_gid_entry(entry);
}
EXPORT_SYMBOL(rdma_put_gid_attr);

/**
 * rdma_hold_gid_attr - Get reference to existing GID attribute
 *
 * @attr:		Pointer to the GID attribute whose reference
 *			needs to be taken.
 *
 * Increase the reference count to a GID attribute to keep it from being
 * freed. Callers are required to already be holding a reference to attribute.
 *
 */
void rdma_hold_gid_attr(const struct ib_gid_attr *attr)
{
	struct ib_gid_table_entry *entry =
		container_of(attr, struct ib_gid_table_entry, attr);

	get_gid_entry(entry);
}
EXPORT_SYMBOL(rdma_hold_gid_attr);

static int config_non_roce_gid_cache(struct ib_device *device,
				     u8 port, int gid_tbl_len)
{
	struct ib_gid_attr gid_attr = {};
	struct ib_gid_table *table;
	int ret = 0;
	int i;

	gid_attr.device = device;
	gid_attr.port_num = port;
	table = rdma_gid_table(device, port);

	mutex_lock(&table->lock);
	for (i = 0; i < gid_tbl_len; ++i) {
		if (!device->query_gid)
			continue;
		ret = device->query_gid(device, port, i, &gid_attr.gid);
		if (ret) {
			pr_warn("query_gid failed (%d) for %s (index %d)\n",
				ret, device->name, i);
			goto err;
		}
		gid_attr.index = i;
		add_modify_gid(table, &gid_attr);
	}
err:
	mutex_unlock(&table->lock);
	return ret;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static void ib_cache_update(struct ib_device *device,
			    u8                port,
			    bool	      enforce_security)
{
	struct ib_port_attr       *tprops = NULL;
	struct ib_pkey_cache      *pkey_cache = NULL, *old_pkey_cache;
<<<<<<< HEAD
	int                        i;
	int                        ret;
=======
	struct ib_gid_cache {
		int             table_len;
		union ib_gid    table[0];
	}			  *gid_cache = NULL;
	int                        i;
	int                        ret;
	struct ib_gid_table	  *table;
	bool			   use_roce_gid_table =
					rdma_cap_roce_gid_table(device, port);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!rdma_is_port_valid(device, port))
		return;

<<<<<<< HEAD
=======
	table = device->cache.ports[port - rdma_start_port(device)].gid;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	tprops = kmalloc(sizeof *tprops, GFP_KERNEL);
	if (!tprops)
		return;

	ret = ib_query_port(device, port, tprops);
	if (ret) {
		pr_warn("ib_query_port failed (%d) for %s\n",
			ret, device->name);
		goto err;
	}

<<<<<<< HEAD
	if (!rdma_protocol_roce(device, port)) {
		ret = config_non_roce_gid_cache(device, port,
						tprops->gid_tbl_len);
		if (ret)
			goto err;
	}

	pkey_cache = kmalloc(struct_size(pkey_cache, table,
					 tprops->pkey_tbl_len),
			     GFP_KERNEL);
=======
	pkey_cache = kmalloc(sizeof *pkey_cache + tprops->pkey_tbl_len *
			     sizeof *pkey_cache->table, GFP_KERNEL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!pkey_cache)
		goto err;

	pkey_cache->table_len = tprops->pkey_tbl_len;

<<<<<<< HEAD
=======
	if (!use_roce_gid_table) {
		gid_cache = kmalloc(sizeof(*gid_cache) + tprops->gid_tbl_len *
			    sizeof(*gid_cache->table), GFP_KERNEL);
		if (!gid_cache)
			goto err;

		gid_cache->table_len = tprops->gid_tbl_len;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	for (i = 0; i < pkey_cache->table_len; ++i) {
		ret = ib_query_pkey(device, port, i, pkey_cache->table + i);
		if (ret) {
			pr_warn("ib_query_pkey failed (%d) for %s (index %d)\n",
				ret, device->name, i);
			goto err;
		}
	}

<<<<<<< HEAD
=======
	if (!use_roce_gid_table) {
		for (i = 0;  i < gid_cache->table_len; ++i) {
			ret = ib_query_gid(device, port, i,
					   gid_cache->table + i, NULL);
			if (ret) {
				pr_warn("ib_query_gid failed (%d) for %s (index %d)\n",
					ret, device->name, i);
				goto err;
			}
		}
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	write_lock_irq(&device->cache.lock);

	old_pkey_cache = device->cache.ports[port -
		rdma_start_port(device)].pkey;

	device->cache.ports[port - rdma_start_port(device)].pkey = pkey_cache;
<<<<<<< HEAD
=======
	if (!use_roce_gid_table) {
		write_lock(&table->rwlock);
		for (i = 0; i < gid_cache->table_len; i++) {
			modify_gid(device, port, table, i, gid_cache->table + i,
				   &zattr, false);
		}
		write_unlock(&table->rwlock);
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	device->cache.ports[port - rdma_start_port(device)].lmc = tprops->lmc;
	device->cache.ports[port - rdma_start_port(device)].port_state =
		tprops->state;

	device->cache.ports[port - rdma_start_port(device)].subnet_prefix =
							tprops->subnet_prefix;
	write_unlock_irq(&device->cache.lock);

	if (enforce_security)
		ib_security_cache_change(device,
					 port,
					 tprops->subnet_prefix);

<<<<<<< HEAD
=======
	kfree(gid_cache);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	kfree(old_pkey_cache);
	kfree(tprops);
	return;

err:
	kfree(pkey_cache);
<<<<<<< HEAD
=======
	kfree(gid_cache);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	kfree(tprops);
}

static void ib_cache_task(struct work_struct *_work)
{
	struct ib_update_work *work =
		container_of(_work, struct ib_update_work, work);

	ib_cache_update(work->device,
			work->port_num,
			work->enforce_security);
	kfree(work);
}

static void ib_cache_event(struct ib_event_handler *handler,
			   struct ib_event *event)
{
	struct ib_update_work *work;

	if (event->event == IB_EVENT_PORT_ERR    ||
	    event->event == IB_EVENT_PORT_ACTIVE ||
	    event->event == IB_EVENT_LID_CHANGE  ||
	    event->event == IB_EVENT_PKEY_CHANGE ||
	    event->event == IB_EVENT_SM_CHANGE   ||
	    event->event == IB_EVENT_CLIENT_REREGISTER ||
	    event->event == IB_EVENT_GID_CHANGE) {
		work = kmalloc(sizeof *work, GFP_ATOMIC);
		if (work) {
			INIT_WORK(&work->work, ib_cache_task);
			work->device   = event->device;
			work->port_num = event->element.port_num;
			if (event->event == IB_EVENT_PKEY_CHANGE ||
			    event->event == IB_EVENT_GID_CHANGE)
				work->enforce_security = true;
			else
				work->enforce_security = false;

			queue_work(ib_wq, &work->work);
		}
	}
}

int ib_cache_setup_one(struct ib_device *device)
{
	int p;
	int err;

	rwlock_init(&device->cache.lock);

	device->cache.ports =
<<<<<<< HEAD
		kcalloc(rdma_end_port(device) - rdma_start_port(device) + 1,
			sizeof(*device->cache.ports),
			GFP_KERNEL);
=======
		kzalloc(sizeof(*device->cache.ports) *
			(rdma_end_port(device) - rdma_start_port(device) + 1), GFP_KERNEL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!device->cache.ports)
		return -ENOMEM;

	err = gid_table_setup_one(device);
	if (err) {
		kfree(device->cache.ports);
		device->cache.ports = NULL;
		return err;
	}

	for (p = 0; p <= rdma_end_port(device) - rdma_start_port(device); ++p)
		ib_cache_update(device, p + rdma_start_port(device), true);

	INIT_IB_EVENT_HANDLER(&device->cache.event_handler,
			      device, ib_cache_event);
	ib_register_event_handler(&device->cache.event_handler);
	return 0;
}

void ib_cache_release_one(struct ib_device *device)
{
	int p;

	/*
	 * The release function frees all the cache elements.
	 * This function should be called as part of freeing
	 * all the device's resources when the cache could no
	 * longer be accessed.
	 */
	for (p = 0; p <= rdma_end_port(device) - rdma_start_port(device); ++p)
		kfree(device->cache.ports[p].pkey);

	gid_table_release_one(device);
	kfree(device->cache.ports);
}

void ib_cache_cleanup_one(struct ib_device *device)
{
	/* The cleanup function unregisters the event handler,
	 * waits for all in-progress workqueue elements and cleans
	 * up the GID cache. This function should be called after
	 * the device was removed from the devices list and all
	 * clients were removed, so the cache exists but is
	 * non-functional and shouldn't be updated anymore.
	 */
	ib_unregister_event_handler(&device->cache.event_handler);
	flush_workqueue(ib_wq);
	gid_table_cleanup_one(device);
<<<<<<< HEAD

	/*
	 * Flush the wq second time for any pending GID delete work.
	 */
	flush_workqueue(ib_wq);
=======
}

void __init ib_cache_setup(void)
{
	roce_gid_mgmt_init();
}

void __exit ib_cache_cleanup(void)
{
	roce_gid_mgmt_cleanup();
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
