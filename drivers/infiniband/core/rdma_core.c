/*
 * Copyright (c) 2016, Mellanox Technologies inc.  All rights reserved.
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

#include <linux/file.h>
#include <linux/anon_inodes.h>
<<<<<<< HEAD
#include <linux/sched/mm.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <rdma/ib_verbs.h>
#include <rdma/uverbs_types.h>
#include <linux/rcupdate.h>
#include <rdma/uverbs_ioctl.h>
#include <rdma/rdma_user_ioctl.h>
#include "uverbs.h"
#include "core_priv.h"
#include "rdma_core.h"

<<<<<<< HEAD
=======
int uverbs_ns_idx(u16 *id, unsigned int ns_count)
{
	int ret = (*id & UVERBS_ID_NS_MASK) >> UVERBS_ID_NS_SHIFT;

	if (ret >= ns_count)
		return -EINVAL;

	*id &= ~UVERBS_ID_NS_MASK;
	return ret;
}

const struct uverbs_object_spec *uverbs_get_object(const struct ib_device *ibdev,
						   uint16_t object)
{
	const struct uverbs_root_spec *object_hash = ibdev->specs_root;
	const struct uverbs_object_spec_hash *objects;
	int ret = uverbs_ns_idx(&object, object_hash->num_buckets);

	if (ret < 0)
		return NULL;

	objects = object_hash->object_buckets[ret];

	if (object >= objects->num_objects)
		return NULL;

	return objects->objects[object];
}

const struct uverbs_method_spec *uverbs_get_method(const struct uverbs_object_spec *object,
						   uint16_t method)
{
	const struct uverbs_method_spec_hash *methods;
	int ret = uverbs_ns_idx(&method, object->num_buckets);

	if (ret < 0)
		return NULL;

	methods = object->method_buckets[ret];
	if (method >= methods->num_methods)
		return NULL;

	return methods->methods[method];
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void uverbs_uobject_get(struct ib_uobject *uobject)
{
	kref_get(&uobject->ref);
}

static void uverbs_uobject_free(struct kref *ref)
{
	struct ib_uobject *uobj =
		container_of(ref, struct ib_uobject, ref);

<<<<<<< HEAD
	if (uobj->uapi_object->type_class->needs_kfree_rcu)
=======
	if (uobj->type->type_class->needs_kfree_rcu)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		kfree_rcu(uobj, rcu);
	else
		kfree(uobj);
}

void uverbs_uobject_put(struct ib_uobject *uobject)
{
	kref_put(&uobject->ref, uverbs_uobject_free);
}

<<<<<<< HEAD
static int uverbs_try_lock_object(struct ib_uobject *uobj,
				  enum rdma_lookup_mode mode)
=======
static int uverbs_try_lock_object(struct ib_uobject *uobj, bool exclusive)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	/*
	 * When a shared access is required, we use a positive counter. Each
	 * shared access request checks that the value != -1 and increment it.
	 * Exclusive access is required for operations like write or destroy.
	 * In exclusive access mode, we check that the counter is zero (nobody
	 * claimed this object) and we set it to -1. Releasing a shared access
	 * lock is done simply by decreasing the counter. As for exclusive
	 * access locks, since only a single one of them is is allowed
	 * concurrently, setting the counter to zero is enough for releasing
	 * this lock.
	 */
<<<<<<< HEAD
	switch (mode) {
	case UVERBS_LOOKUP_READ:
		return atomic_fetch_add_unless(&uobj->usecnt, 1, -1) == -1 ?
			-EBUSY : 0;
	case UVERBS_LOOKUP_WRITE:
		/* lock is exclusive */
		return atomic_cmpxchg(&uobj->usecnt, 0, -1) == 0 ? 0 : -EBUSY;
	case UVERBS_LOOKUP_DESTROY:
		return 0;
	}
	return 0;
}

static void assert_uverbs_usecnt(struct ib_uobject *uobj,
				 enum rdma_lookup_mode mode)
{
#ifdef CONFIG_LOCKDEP
	switch (mode) {
	case UVERBS_LOOKUP_READ:
		WARN_ON(atomic_read(&uobj->usecnt) <= 0);
		break;
	case UVERBS_LOOKUP_WRITE:
		WARN_ON(atomic_read(&uobj->usecnt) != -1);
		break;
	case UVERBS_LOOKUP_DESTROY:
		break;
	}
#endif
}

/*
 * This must be called with the hw_destroy_rwsem locked for read or write,
 * also the uobject itself must be locked for write.
 *
 * Upon return the HW object is guaranteed to be destroyed.
 *
 * For RDMA_REMOVE_ABORT, the hw_destroy_rwsem is not required to be held,
 * however the type's allocat_commit function cannot have been called and the
 * uobject cannot be on the uobjects_lists
 *
 * For RDMA_REMOVE_DESTROY the caller shold be holding a kref (eg via
 * rdma_lookup_get_uobject) and the object is left in a state where the caller
 * needs to call rdma_lookup_put_uobject.
 *
 * For all other destroy modes this function internally unlocks the uobject
 * and consumes the kref on the uobj.
 */
static int uverbs_destroy_uobject(struct ib_uobject *uobj,
				  enum rdma_remove_reason reason)
{
	struct ib_uverbs_file *ufile = uobj->ufile;
	unsigned long flags;
	int ret;

	lockdep_assert_held(&ufile->hw_destroy_rwsem);
	assert_uverbs_usecnt(uobj, UVERBS_LOOKUP_WRITE);

	if (uobj->object) {
		ret = uobj->uapi_object->type_class->destroy_hw(uobj, reason);
		if (ret) {
			if (ib_is_destroy_retryable(ret, reason, uobj))
				return ret;

			/* Nothing to be done, dangle the memory and move on */
			WARN(true,
			     "ib_uverbs: failed to remove uobject id %d, driver err=%d",
			     uobj->id, ret);
		}

		uobj->object = NULL;
	}

	if (reason == RDMA_REMOVE_ABORT) {
		WARN_ON(!list_empty(&uobj->list));
		WARN_ON(!uobj->context);
		uobj->uapi_object->type_class->alloc_abort(uobj);
	}

	uobj->context = NULL;

	/*
	 * For DESTROY the usecnt is held write locked, the caller is expected
	 * to put it unlock and put the object when done with it. Only DESTROY
	 * can remove the IDR handle.
	 */
	if (reason != RDMA_REMOVE_DESTROY)
		atomic_set(&uobj->usecnt, 0);
	else
		uobj->uapi_object->type_class->remove_handle(uobj);

	if (!list_empty(&uobj->list)) {
		spin_lock_irqsave(&ufile->uobjects_lock, flags);
		list_del_init(&uobj->list);
		spin_unlock_irqrestore(&ufile->uobjects_lock, flags);

		/*
		 * Pairs with the get in rdma_alloc_commit_uobject(), could
		 * destroy uobj.
		 */
		uverbs_uobject_put(uobj);
	}

	/*
	 * When aborting the stack kref remains owned by the core code, and is
	 * not transferred into the type. Pairs with the get in alloc_uobj
	 */
	if (reason == RDMA_REMOVE_ABORT)
		uverbs_uobject_put(uobj);

	return 0;
}

/*
 * This calls uverbs_destroy_uobject() using the RDMA_REMOVE_DESTROY
 * sequence. It should only be used from command callbacks. On success the
 * caller must pair this with rdma_lookup_put_uobject(LOOKUP_WRITE). This
 * version requires the caller to have already obtained an
 * LOOKUP_DESTROY uobject kref.
 */
int uobj_destroy(struct ib_uobject *uobj)
{
	struct ib_uverbs_file *ufile = uobj->ufile;
	int ret;

	down_read(&ufile->hw_destroy_rwsem);

	ret = uverbs_try_lock_object(uobj, UVERBS_LOOKUP_WRITE);
	if (ret)
		goto out_unlock;

	ret = uverbs_destroy_uobject(uobj, RDMA_REMOVE_DESTROY);
	if (ret) {
		atomic_set(&uobj->usecnt, 0);
		goto out_unlock;
	}

out_unlock:
	up_read(&ufile->hw_destroy_rwsem);
	return ret;
}

/*
 * uobj_get_destroy destroys the HW object and returns a handle to the uobj
 * with a NULL object pointer. The caller must pair this with
 * uverbs_put_destroy.
 */
struct ib_uobject *__uobj_get_destroy(const struct uverbs_api_object *obj,
				      u32 id, struct ib_uverbs_file *ufile)
{
	struct ib_uobject *uobj;
	int ret;

	uobj = rdma_lookup_get_uobject(obj, ufile, id, UVERBS_LOOKUP_DESTROY);
	if (IS_ERR(uobj))
		return uobj;

	ret = uobj_destroy(uobj);
	if (ret) {
		rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_DESTROY);
		return ERR_PTR(ret);
	}

	return uobj;
}

/*
 * Does both uobj_get_destroy() and uobj_put_destroy().  Returns success_res
 * on success (negative errno on failure). For use by callers that do not need
 * the uobj.
 */
int __uobj_perform_destroy(const struct uverbs_api_object *obj, u32 id,
			   struct ib_uverbs_file *ufile, int success_res)
{
	struct ib_uobject *uobj;

	uobj = __uobj_get_destroy(obj, id, ufile);
	if (IS_ERR(uobj))
		return PTR_ERR(uobj);

	rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_WRITE);
	return success_res;
}

/* alloc_uobj must be undone by uverbs_destroy_uobject() */
static struct ib_uobject *alloc_uobj(struct ib_uverbs_file *ufile,
				     const struct uverbs_api_object *obj)
{
	struct ib_uobject *uobj;
	struct ib_ucontext *ucontext;

	ucontext = ib_uverbs_get_ucontext(ufile);
	if (IS_ERR(ucontext))
		return ERR_CAST(ucontext);

	uobj = kzalloc(obj->type_attrs->obj_size, GFP_KERNEL);
=======
	if (!exclusive)
		return __atomic_add_unless(&uobj->usecnt, 1, -1) == -1 ?
			-EBUSY : 0;

	/* lock is either WRITE or DESTROY - should be exclusive */
	return atomic_cmpxchg(&uobj->usecnt, 0, -1) == 0 ? 0 : -EBUSY;
}

static struct ib_uobject *alloc_uobj(struct ib_ucontext *context,
				     const struct uverbs_obj_type *type)
{
	struct ib_uobject *uobj = kzalloc(type->obj_size, GFP_KERNEL);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!uobj)
		return ERR_PTR(-ENOMEM);
	/*
	 * user_handle should be filled by the handler,
	 * The object is added to the list in the commit stage.
	 */
<<<<<<< HEAD
	uobj->ufile = ufile;
	uobj->context = ucontext;
	INIT_LIST_HEAD(&uobj->list);
	uobj->uapi_object = obj;
	/*
	 * Allocated objects start out as write locked to deny any other
	 * syscalls from accessing them until they are committed. See
	 * rdma_alloc_commit_uobject
	 */
	atomic_set(&uobj->usecnt, -1);
=======
	uobj->context = context;
	uobj->type = type;
	atomic_set(&uobj->usecnt, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	kref_init(&uobj->ref);

	return uobj;
}

static int idr_add_uobj(struct ib_uobject *uobj)
{
	int ret;

	idr_preload(GFP_KERNEL);
<<<<<<< HEAD
	spin_lock(&uobj->ufile->idr_lock);
=======
	spin_lock(&uobj->context->ufile->idr_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * We start with allocating an idr pointing to NULL. This represents an
	 * object which isn't initialized yet. We'll replace it later on with
	 * the real object once we commit.
	 */
<<<<<<< HEAD
	ret = idr_alloc(&uobj->ufile->idr, NULL, 0,
=======
	ret = idr_alloc(&uobj->context->ufile->idr, NULL, 0,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			min_t(unsigned long, U32_MAX - 1, INT_MAX), GFP_NOWAIT);
	if (ret >= 0)
		uobj->id = ret;

<<<<<<< HEAD
	spin_unlock(&uobj->ufile->idr_lock);
=======
	spin_unlock(&uobj->context->ufile->idr_lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	idr_preload_end();

	return ret < 0 ? ret : 0;
}

<<<<<<< HEAD
/* Returns the ib_uobject or an error. The caller should check for IS_ERR. */
static struct ib_uobject *
lookup_get_idr_uobject(const struct uverbs_api_object *obj,
		       struct ib_uverbs_file *ufile, s64 id,
		       enum rdma_lookup_mode mode)
{
	struct ib_uobject *uobj;
	unsigned long idrno = id;

	if (id < 0 || id > ULONG_MAX)
		return ERR_PTR(-EINVAL);

	rcu_read_lock();
	/* object won't be released as we're protected in rcu */
	uobj = idr_find(&ufile->idr, idrno);
=======
/*
 * It only removes it from the uobjects list, uverbs_uobject_put() is still
 * required.
 */
static void uverbs_idr_remove_uobj(struct ib_uobject *uobj)
{
	spin_lock(&uobj->context->ufile->idr_lock);
	idr_remove(&uobj->context->ufile->idr, uobj->id);
	spin_unlock(&uobj->context->ufile->idr_lock);
}

/* Returns the ib_uobject or an error. The caller should check for IS_ERR. */
static struct ib_uobject *lookup_get_idr_uobject(const struct uverbs_obj_type *type,
						 struct ib_ucontext *ucontext,
						 int id, bool exclusive)
{
	struct ib_uobject *uobj;

	rcu_read_lock();
	/* object won't be released as we're protected in rcu */
	uobj = idr_find(&ucontext->ufile->idr, id);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!uobj) {
		uobj = ERR_PTR(-ENOENT);
		goto free;
	}

	/*
	 * The idr_find is guaranteed to return a pointer to something that
	 * isn't freed yet, or NULL, as the free after idr_remove goes through
	 * kfree_rcu(). However the object may still have been released and
	 * kfree() could be called at any time.
	 */
	if (!kref_get_unless_zero(&uobj->ref))
		uobj = ERR_PTR(-ENOENT);

free:
	rcu_read_unlock();
	return uobj;
}

<<<<<<< HEAD
static struct ib_uobject *
lookup_get_fd_uobject(const struct uverbs_api_object *obj,
		      struct ib_uverbs_file *ufile, s64 id,
		      enum rdma_lookup_mode mode)
{
	const struct uverbs_obj_fd_type *fd_type;
	struct file *f;
	struct ib_uobject *uobject;
	int fdno = id;

	if (fdno != id)
		return ERR_PTR(-EINVAL);

	if (mode != UVERBS_LOOKUP_READ)
		return ERR_PTR(-EOPNOTSUPP);

	if (!obj->type_attrs)
		return ERR_PTR(-EIO);
	fd_type =
		container_of(obj->type_attrs, struct uverbs_obj_fd_type, type);

	f = fget(fdno);
=======
static struct ib_uobject *lookup_get_fd_uobject(const struct uverbs_obj_type *type,
						struct ib_ucontext *ucontext,
						int id, bool exclusive)
{
	struct file *f;
	struct ib_uobject *uobject;
	const struct uverbs_obj_fd_type *fd_type =
		container_of(type, struct uverbs_obj_fd_type, type);

	if (exclusive)
		return ERR_PTR(-EOPNOTSUPP);

	f = fget(id);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!f)
		return ERR_PTR(-EBADF);

	uobject = f->private_data;
	/*
	 * fget(id) ensures we are not currently running uverbs_close_fd,
	 * and the caller is expected to ensure that uverbs_close_fd is never
	 * done while a call top lookup is possible.
	 */
	if (f->f_op != fd_type->fops) {
		fput(f);
		return ERR_PTR(-EBADF);
	}

	uverbs_uobject_get(uobject);
	return uobject;
}

<<<<<<< HEAD
struct ib_uobject *rdma_lookup_get_uobject(const struct uverbs_api_object *obj,
					   struct ib_uverbs_file *ufile, s64 id,
					   enum rdma_lookup_mode mode)
=======
struct ib_uobject *rdma_lookup_get_uobject(const struct uverbs_obj_type *type,
					   struct ib_ucontext *ucontext,
					   int id, bool exclusive)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct ib_uobject *uobj;
	int ret;

<<<<<<< HEAD
	if (!obj)
		return ERR_PTR(-EINVAL);

	uobj = obj->type_class->lookup_get(obj, ufile, id, mode);
	if (IS_ERR(uobj))
		return uobj;

	if (uobj->uapi_object != obj) {
=======
	uobj = type->type_class->lookup_get(type, ucontext, id, exclusive);
	if (IS_ERR(uobj))
		return uobj;

	if (uobj->type != type) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		ret = -EINVAL;
		goto free;
	}

<<<<<<< HEAD
	/*
	 * If we have been disassociated block every command except for
	 * DESTROY based commands.
	 */
	if (mode != UVERBS_LOOKUP_DESTROY &&
	    !srcu_dereference(ufile->device->ib_dev,
			      &ufile->device->disassociate_srcu)) {
		ret = -EIO;
		goto free;
	}

	ret = uverbs_try_lock_object(uobj, mode);
	if (ret)
		goto free;

	return uobj;
free:
	obj->type_class->lookup_put(uobj, mode);
=======
	ret = uverbs_try_lock_object(uobj, exclusive);
	if (ret) {
		WARN(ucontext->cleanup_reason,
		     "ib_uverbs: Trying to lookup_get while cleanup context\n");
		goto free;
	}

	return uobj;
free:
	uobj->type->type_class->lookup_put(uobj, exclusive);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	uverbs_uobject_put(uobj);
	return ERR_PTR(ret);
}

<<<<<<< HEAD
static struct ib_uobject *
alloc_begin_idr_uobject(const struct uverbs_api_object *obj,
			struct ib_uverbs_file *ufile)
=======
static struct ib_uobject *alloc_begin_idr_uobject(const struct uverbs_obj_type *type,
						  struct ib_ucontext *ucontext)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	int ret;
	struct ib_uobject *uobj;

<<<<<<< HEAD
	uobj = alloc_uobj(ufile, obj);
=======
	uobj = alloc_uobj(ucontext, type);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (IS_ERR(uobj))
		return uobj;

	ret = idr_add_uobj(uobj);
	if (ret)
		goto uobj_put;

<<<<<<< HEAD
	ret = ib_rdmacg_try_charge(&uobj->cg_obj, uobj->context->device,
=======
	ret = ib_rdmacg_try_charge(&uobj->cg_obj, ucontext->device,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				   RDMACG_RESOURCE_HCA_OBJECT);
	if (ret)
		goto idr_remove;

	return uobj;

idr_remove:
<<<<<<< HEAD
	spin_lock(&ufile->idr_lock);
	idr_remove(&ufile->idr, uobj->id);
	spin_unlock(&ufile->idr_lock);
=======
	uverbs_idr_remove_uobj(uobj);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
uobj_put:
	uverbs_uobject_put(uobj);
	return ERR_PTR(ret);
}

<<<<<<< HEAD
static struct ib_uobject *
alloc_begin_fd_uobject(const struct uverbs_api_object *obj,
		       struct ib_uverbs_file *ufile)
{
	int new_fd;
	struct ib_uobject *uobj;
=======
static struct ib_uobject *alloc_begin_fd_uobject(const struct uverbs_obj_type *type,
						 struct ib_ucontext *ucontext)
{
	const struct uverbs_obj_fd_type *fd_type =
		container_of(type, struct uverbs_obj_fd_type, type);
	int new_fd;
	struct ib_uobject *uobj;
	struct ib_uobject_file *uobj_file;
	struct file *filp;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	new_fd = get_unused_fd_flags(O_CLOEXEC);
	if (new_fd < 0)
		return ERR_PTR(new_fd);

<<<<<<< HEAD
	uobj = alloc_uobj(ufile, obj);
=======
	uobj = alloc_uobj(ucontext, type);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (IS_ERR(uobj)) {
		put_unused_fd(new_fd);
		return uobj;
	}

<<<<<<< HEAD
	uobj->id = new_fd;
	uobj->ufile = ufile;
=======
	uobj_file = container_of(uobj, struct ib_uobject_file, uobj);
	filp = anon_inode_getfile(fd_type->name,
				  fd_type->fops,
				  uobj_file,
				  fd_type->flags);
	if (IS_ERR(filp)) {
		put_unused_fd(new_fd);
		uverbs_uobject_put(uobj);
		return (void *)filp;
	}

	uobj_file->uobj.id = new_fd;
	uobj_file->uobj.object = filp;
	uobj_file->ufile = ucontext->ufile;
	INIT_LIST_HEAD(&uobj->list);
	kref_get(&uobj_file->ufile->ref);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return uobj;
}

<<<<<<< HEAD
struct ib_uobject *rdma_alloc_begin_uobject(const struct uverbs_api_object *obj,
					    struct ib_uverbs_file *ufile)
{
	struct ib_uobject *ret;

	if (!obj)
		return ERR_PTR(-EINVAL);

	/*
	 * The hw_destroy_rwsem is held across the entire object creation and
	 * released during rdma_alloc_commit_uobject or
	 * rdma_alloc_abort_uobject
	 */
	if (!down_read_trylock(&ufile->hw_destroy_rwsem))
		return ERR_PTR(-EIO);

	ret = obj->type_class->alloc_begin(obj, ufile);
	if (IS_ERR(ret)) {
		up_read(&ufile->hw_destroy_rwsem);
		return ret;
	}
	return ret;
}

static void alloc_abort_idr_uobject(struct ib_uobject *uobj)
{
	ib_rdmacg_uncharge(&uobj->cg_obj, uobj->context->device,
			   RDMACG_RESOURCE_HCA_OBJECT);

	spin_lock(&uobj->ufile->idr_lock);
	idr_remove(&uobj->ufile->idr, uobj->id);
	spin_unlock(&uobj->ufile->idr_lock);
}

static int __must_check destroy_hw_idr_uobject(struct ib_uobject *uobj,
					       enum rdma_remove_reason why)
{
	const struct uverbs_obj_idr_type *idr_type =
		container_of(uobj->uapi_object->type_attrs,
			     struct uverbs_obj_idr_type, type);
=======
struct ib_uobject *rdma_alloc_begin_uobject(const struct uverbs_obj_type *type,
					    struct ib_ucontext *ucontext)
{
	return type->type_class->alloc_begin(type, ucontext);
}

static void uverbs_uobject_add(struct ib_uobject *uobject)
{
	mutex_lock(&uobject->context->uobjects_lock);
	list_add(&uobject->list, &uobject->context->uobjects);
	mutex_unlock(&uobject->context->uobjects_lock);
}

static int __must_check remove_commit_idr_uobject(struct ib_uobject *uobj,
						  enum rdma_remove_reason why)
{
	const struct uverbs_obj_idr_type *idr_type =
		container_of(uobj->type, struct uverbs_obj_idr_type,
			     type);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int ret = idr_type->destroy_object(uobj, why);

	/*
	 * We can only fail gracefully if the user requested to destroy the
<<<<<<< HEAD
	 * object or when a retry may be called upon an error.
	 * In the rest of the cases, just remove whatever you can.
	 */
	if (ib_is_destroy_retryable(ret, why, uobj))
		return ret;

	if (why == RDMA_REMOVE_ABORT)
		return 0;

	ib_rdmacg_uncharge(&uobj->cg_obj, uobj->context->device,
			   RDMACG_RESOURCE_HCA_OBJECT);

	return 0;
}

static void remove_handle_idr_uobject(struct ib_uobject *uobj)
{
	spin_lock(&uobj->ufile->idr_lock);
	idr_remove(&uobj->ufile->idr, uobj->id);
	spin_unlock(&uobj->ufile->idr_lock);
	/* Matches the kref in alloc_commit_idr_uobject */
	uverbs_uobject_put(uobj);
=======
	 * object. In the rest of the cases, just remove whatever you can.
	 */
	if (why == RDMA_REMOVE_DESTROY && ret)
		return ret;

	ib_rdmacg_uncharge(&uobj->cg_obj, uobj->context->device,
			   RDMACG_RESOURCE_HCA_OBJECT);
	uverbs_idr_remove_uobj(uobj);

	return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void alloc_abort_fd_uobject(struct ib_uobject *uobj)
{
<<<<<<< HEAD
	put_unused_fd(uobj->id);
}

static int __must_check destroy_hw_fd_uobject(struct ib_uobject *uobj,
					      enum rdma_remove_reason why)
{
	const struct uverbs_obj_fd_type *fd_type = container_of(
		uobj->uapi_object->type_attrs, struct uverbs_obj_fd_type, type);
	int ret = fd_type->context_closed(uobj, why);

	if (ib_is_destroy_retryable(ret, why, uobj))
		return ret;

	return 0;
}

static void remove_handle_fd_uobject(struct ib_uobject *uobj)
{
}

static int alloc_commit_idr_uobject(struct ib_uobject *uobj)
{
	struct ib_uverbs_file *ufile = uobj->ufile;

	spin_lock(&ufile->idr_lock);
	/*
	 * We already allocated this IDR with a NULL object, so
	 * this shouldn't fail.
	 *
	 * NOTE: Once we set the IDR we loose ownership of our kref on uobj.
	 * It will be put by remove_commit_idr_uobject()
	 */
	WARN_ON(idr_replace(&ufile->idr, uobj, uobj->id));
	spin_unlock(&ufile->idr_lock);

	return 0;
}

static int alloc_commit_fd_uobject(struct ib_uobject *uobj)
{
	const struct uverbs_obj_fd_type *fd_type = container_of(
		uobj->uapi_object->type_attrs, struct uverbs_obj_fd_type, type);
	int fd = uobj->id;
	struct file *filp;

	/*
	 * The kref for uobj is moved into filp->private data and put in
	 * uverbs_close_fd(). Once alloc_commit() succeeds uverbs_close_fd()
	 * must be guaranteed to be called from the provided fops release
	 * callback.
	 */
	filp = anon_inode_getfile(fd_type->name,
				  fd_type->fops,
				  uobj,
				  fd_type->flags);
	if (IS_ERR(filp))
		return PTR_ERR(filp);

	uobj->object = filp;

	/* Matching put will be done in uverbs_close_fd() */
	kref_get(&uobj->ufile->ref);

	/* This shouldn't be used anymore. Use the file object instead */
	uobj->id = 0;

	/*
	 * NOTE: Once we install the file we loose ownership of our kref on
	 * uobj. It will be put by uverbs_close_fd()
	 */
	fd_install(fd, filp);

	return 0;
}

/*
 * In all cases rdma_alloc_commit_uobject() consumes the kref to uobj and the
 * caller can no longer assume uobj is valid. If this function fails it
 * destroys the uboject, including the attached HW object.
 */
int __must_check rdma_alloc_commit_uobject(struct ib_uobject *uobj)
{
	struct ib_uverbs_file *ufile = uobj->ufile;
	int ret;

	/* alloc_commit consumes the uobj kref */
	ret = uobj->uapi_object->type_class->alloc_commit(uobj);
	if (ret) {
		uverbs_destroy_uobject(uobj, RDMA_REMOVE_ABORT);
		up_read(&ufile->hw_destroy_rwsem);
		return ret;
	}

	/* kref is held so long as the uobj is on the uobj list. */
	uverbs_uobject_get(uobj);
	spin_lock_irq(&ufile->uobjects_lock);
	list_add(&uobj->list, &ufile->uobjects);
	spin_unlock_irq(&ufile->uobjects_lock);

	/* matches atomic_set(-1) in alloc_uobj */
	atomic_set(&uobj->usecnt, 0);

	/* Matches the down_read in rdma_alloc_begin_uobject */
	up_read(&ufile->hw_destroy_rwsem);
=======
	struct ib_uobject_file *uobj_file =
		container_of(uobj, struct ib_uobject_file, uobj);
	struct file *filp = uobj->object;
	int id = uobj_file->uobj.id;

	/* Unsuccessful NEW */
	fput(filp);
	put_unused_fd(id);
}

static int __must_check remove_commit_fd_uobject(struct ib_uobject *uobj,
						 enum rdma_remove_reason why)
{
	const struct uverbs_obj_fd_type *fd_type =
		container_of(uobj->type, struct uverbs_obj_fd_type, type);
	struct ib_uobject_file *uobj_file =
		container_of(uobj, struct ib_uobject_file, uobj);
	int ret = fd_type->context_closed(uobj_file, why);

	if (why == RDMA_REMOVE_DESTROY && ret)
		return ret;

	if (why == RDMA_REMOVE_DURING_CLEANUP) {
		alloc_abort_fd_uobject(uobj);
		return ret;
	}

	uobj_file->uobj.context = NULL;
	return ret;
}

static void assert_uverbs_usecnt(struct ib_uobject *uobj, bool exclusive)
{
#ifdef CONFIG_LOCKDEP
	if (exclusive)
		WARN_ON(atomic_read(&uobj->usecnt) != -1);
	else
		WARN_ON(atomic_read(&uobj->usecnt) <= 0);
#endif
}

static int __must_check _rdma_remove_commit_uobject(struct ib_uobject *uobj,
						    enum rdma_remove_reason why)
{
	int ret;
	struct ib_ucontext *ucontext = uobj->context;

	ret = uobj->type->type_class->remove_commit(uobj, why);
	if (ret && why == RDMA_REMOVE_DESTROY) {
		/* We couldn't remove the object, so just unlock the uobject */
		atomic_set(&uobj->usecnt, 0);
		uobj->type->type_class->lookup_put(uobj, true);
	} else {
		mutex_lock(&ucontext->uobjects_lock);
		list_del(&uobj->list);
		mutex_unlock(&ucontext->uobjects_lock);
		/* put the ref we took when we created the object */
		uverbs_uobject_put(uobj);
	}

	return ret;
}

/* This is called only for user requested DESTROY reasons */
int __must_check rdma_remove_commit_uobject(struct ib_uobject *uobj)
{
	int ret;
	struct ib_ucontext *ucontext = uobj->context;

	/* put the ref count we took at lookup_get */
	uverbs_uobject_put(uobj);
	/* Cleanup is running. Calling this should have been impossible */
	if (!down_read_trylock(&ucontext->cleanup_rwsem)) {
		WARN(true, "ib_uverbs: Cleanup is running while removing an uobject\n");
		return 0;
	}
	assert_uverbs_usecnt(uobj, true);
	ret = _rdma_remove_commit_uobject(uobj, RDMA_REMOVE_DESTROY);

	up_read(&ucontext->cleanup_rwsem);
	return ret;
}

static int null_obj_type_class_remove_commit(struct ib_uobject *uobj,
					     enum rdma_remove_reason why)
{
	return 0;
}

static const struct uverbs_obj_type null_obj_type = {
	.type_class = &((const struct uverbs_obj_type_class){
			.remove_commit = null_obj_type_class_remove_commit,
			/* be cautious */
			.needs_kfree_rcu = true}),
};

int rdma_explicit_destroy(struct ib_uobject *uobject)
{
	int ret;
	struct ib_ucontext *ucontext = uobject->context;

	/* Cleanup is running. Calling this should have been impossible */
	if (!down_read_trylock(&ucontext->cleanup_rwsem)) {
		WARN(true, "ib_uverbs: Cleanup is running while removing an uobject\n");
		return 0;
	}
	assert_uverbs_usecnt(uobject, true);
	ret = uobject->type->type_class->remove_commit(uobject,
						       RDMA_REMOVE_DESTROY);
	if (ret)
		goto out;

	uobject->type = &null_obj_type;

out:
	up_read(&ucontext->cleanup_rwsem);
	return ret;
}

static void alloc_commit_idr_uobject(struct ib_uobject *uobj)
{
	uverbs_uobject_add(uobj);
	spin_lock(&uobj->context->ufile->idr_lock);
	/*
	 * We already allocated this IDR with a NULL object, so
	 * this shouldn't fail.
	 */
	WARN_ON(idr_replace(&uobj->context->ufile->idr,
			    uobj, uobj->id));
	spin_unlock(&uobj->context->ufile->idr_lock);
}

static void alloc_commit_fd_uobject(struct ib_uobject *uobj)
{
	struct ib_uobject_file *uobj_file =
		container_of(uobj, struct ib_uobject_file, uobj);

	uverbs_uobject_add(&uobj_file->uobj);
	fd_install(uobj_file->uobj.id, uobj->object);
	/* This shouldn't be used anymore. Use the file object instead */
	uobj_file->uobj.id = 0;
	/* Get another reference as we export this to the fops */
	uverbs_uobject_get(&uobj_file->uobj);
}

int rdma_alloc_commit_uobject(struct ib_uobject *uobj)
{
	/* Cleanup is running. Calling this should have been impossible */
	if (!down_read_trylock(&uobj->context->cleanup_rwsem)) {
		int ret;

		WARN(true, "ib_uverbs: Cleanup is running while allocating an uobject\n");
		ret = uobj->type->type_class->remove_commit(uobj,
							    RDMA_REMOVE_DURING_CLEANUP);
		if (ret)
			pr_warn("ib_uverbs: cleanup of idr object %d failed\n",
				uobj->id);
		return ret;
	}

	uobj->type->type_class->alloc_commit(uobj);
	up_read(&uobj->context->cleanup_rwsem);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

<<<<<<< HEAD
/*
 * This consumes the kref for uobj. It is up to the caller to unwind the HW
 * object and anything else connected to uobj before calling this.
 */
void rdma_alloc_abort_uobject(struct ib_uobject *uobj)
{
	struct ib_uverbs_file *ufile = uobj->ufile;

	uobj->object = NULL;
	uverbs_destroy_uobject(uobj, RDMA_REMOVE_ABORT);

	/* Matches the down_read in rdma_alloc_begin_uobject */
	up_read(&ufile->hw_destroy_rwsem);
}

static void lookup_put_idr_uobject(struct ib_uobject *uobj,
				   enum rdma_lookup_mode mode)
{
}

static void lookup_put_fd_uobject(struct ib_uobject *uobj,
				  enum rdma_lookup_mode mode)
{
	struct file *filp = uobj->object;

	WARN_ON(mode != UVERBS_LOOKUP_READ);
=======
static void alloc_abort_idr_uobject(struct ib_uobject *uobj)
{
	uverbs_idr_remove_uobj(uobj);
	ib_rdmacg_uncharge(&uobj->cg_obj, uobj->context->device,
			   RDMACG_RESOURCE_HCA_OBJECT);
	uverbs_uobject_put(uobj);
}

void rdma_alloc_abort_uobject(struct ib_uobject *uobj)
{
	uobj->type->type_class->alloc_abort(uobj);
}

static void lookup_put_idr_uobject(struct ib_uobject *uobj, bool exclusive)
{
}

static void lookup_put_fd_uobject(struct ib_uobject *uobj, bool exclusive)
{
	struct file *filp = uobj->object;

	WARN_ON(exclusive);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* This indirectly calls uverbs_close_fd and free the object */
	fput(filp);
}

<<<<<<< HEAD
void rdma_lookup_put_uobject(struct ib_uobject *uobj,
			     enum rdma_lookup_mode mode)
{
	assert_uverbs_usecnt(uobj, mode);
	uobj->uapi_object->type_class->lookup_put(uobj, mode);
=======
void rdma_lookup_put_uobject(struct ib_uobject *uobj, bool exclusive)
{
	assert_uverbs_usecnt(uobj, exclusive);
	uobj->type->type_class->lookup_put(uobj, exclusive);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/*
	 * In order to unlock an object, either decrease its usecnt for
	 * read access or zero it in case of exclusive access. See
	 * uverbs_try_lock_object for locking schema information.
	 */
<<<<<<< HEAD
	switch (mode) {
	case UVERBS_LOOKUP_READ:
		atomic_dec(&uobj->usecnt);
		break;
	case UVERBS_LOOKUP_WRITE:
		atomic_set(&uobj->usecnt, 0);
		break;
	case UVERBS_LOOKUP_DESTROY:
		break;
	}

	/* Pairs with the kref obtained by type->lookup_get */
	uverbs_uobject_put(uobj);
}

void setup_ufile_idr_uobject(struct ib_uverbs_file *ufile)
{
	spin_lock_init(&ufile->idr_lock);
	idr_init(&ufile->idr);
}

void release_ufile_idr_uobject(struct ib_uverbs_file *ufile)
{
	struct ib_uobject *entry;
	int id;

	/*
	 * At this point uverbs_cleanup_ufile() is guaranteed to have run, and
	 * there are no HW objects left, however the IDR is still populated
	 * with anything that has not been cleaned up by userspace. Since the
	 * kref on ufile is 0, nothing is allowed to call lookup_get.
	 *
	 * This is an optimized equivalent to remove_handle_idr_uobject
	 */
	idr_for_each_entry(&ufile->idr, entry, id) {
		WARN_ON(entry->object);
		uverbs_uobject_put(entry);
	}

	idr_destroy(&ufile->idr);
}

=======
	if (!exclusive)
		atomic_dec(&uobj->usecnt);
	else
		atomic_set(&uobj->usecnt, 0);

	uverbs_uobject_put(uobj);
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
const struct uverbs_obj_type_class uverbs_idr_class = {
	.alloc_begin = alloc_begin_idr_uobject,
	.lookup_get = lookup_get_idr_uobject,
	.alloc_commit = alloc_commit_idr_uobject,
	.alloc_abort = alloc_abort_idr_uobject,
	.lookup_put = lookup_put_idr_uobject,
<<<<<<< HEAD
	.destroy_hw = destroy_hw_idr_uobject,
	.remove_handle = remove_handle_idr_uobject,
=======
	.remove_commit = remove_commit_idr_uobject,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/*
	 * When we destroy an object, we first just lock it for WRITE and
	 * actually DESTROY it in the finalize stage. So, the problematic
	 * scenario is when we just started the finalize stage of the
	 * destruction (nothing was executed yet). Now, the other thread
	 * fetched the object for READ access, but it didn't lock it yet.
	 * The DESTROY thread continues and starts destroying the object.
	 * When the other thread continue - without the RCU, it would
	 * access freed memory. However, the rcu_read_lock delays the free
	 * until the rcu_read_lock of the READ operation quits. Since the
	 * exclusive lock of the object is still taken by the DESTROY flow, the
	 * READ operation will get -EBUSY and it'll just bail out.
	 */
	.needs_kfree_rcu = true,
};
<<<<<<< HEAD
EXPORT_SYMBOL(uverbs_idr_class);

void uverbs_close_fd(struct file *f)
{
	struct ib_uobject *uobj = f->private_data;
	struct ib_uverbs_file *ufile = uobj->ufile;

	if (down_read_trylock(&ufile->hw_destroy_rwsem)) {
		/*
		 * lookup_get_fd_uobject holds the kref on the struct file any
		 * time a FD uobj is locked, which prevents this release
		 * method from being invoked. Meaning we can always get the
		 * write lock here, or we have a kernel bug.
		 */
		WARN_ON(uverbs_try_lock_object(uobj, UVERBS_LOOKUP_WRITE));
		uverbs_destroy_uobject(uobj, RDMA_REMOVE_CLOSE);
		up_read(&ufile->hw_destroy_rwsem);
	}

	/* Matches the get in alloc_begin_fd_uobject */
	kref_put(&ufile->ref, ib_uverbs_release_file);

	/* Pairs with filp->private_data in alloc_begin_fd_uobject */
	uverbs_uobject_put(uobj);
}

static void ufile_disassociate_ucontext(struct ib_ucontext *ibcontext)
{
	struct ib_device *ib_dev = ibcontext->device;
	struct task_struct *owning_process  = NULL;
	struct mm_struct   *owning_mm       = NULL;

	owning_process = get_pid_task(ibcontext->tgid, PIDTYPE_PID);
	if (!owning_process)
		return;

	owning_mm = get_task_mm(owning_process);
	if (!owning_mm) {
		pr_info("no mm, disassociate ucontext is pending task termination\n");
		while (1) {
			put_task_struct(owning_process);
			usleep_range(1000, 2000);
			owning_process = get_pid_task(ibcontext->tgid,
						      PIDTYPE_PID);
			if (!owning_process ||
			    owning_process->state == TASK_DEAD) {
				pr_info("disassociate ucontext done, task was terminated\n");
				/* in case task was dead need to release the
				 * task struct.
				 */
				if (owning_process)
					put_task_struct(owning_process);
				return;
			}
		}
	}

	down_write(&owning_mm->mmap_sem);
	ib_dev->disassociate_ucontext(ibcontext);
	up_write(&owning_mm->mmap_sem);
	mmput(owning_mm);
	put_task_struct(owning_process);
}

/*
 * Drop the ucontext off the ufile and completely disconnect it from the
 * ib_device
 */
static void ufile_destroy_ucontext(struct ib_uverbs_file *ufile,
				   enum rdma_remove_reason reason)
{
	struct ib_ucontext *ucontext = ufile->ucontext;
	int ret;

	if (reason == RDMA_REMOVE_DRIVER_REMOVE)
		ufile_disassociate_ucontext(ucontext);

	put_pid(ucontext->tgid);
	ib_rdmacg_uncharge(&ucontext->cg_obj, ucontext->device,
			   RDMACG_RESOURCE_HCA_HANDLE);

	/*
	 * FIXME: Drivers are not permitted to fail dealloc_ucontext, remove
	 * the error return.
	 */
	ret = ucontext->device->dealloc_ucontext(ucontext);
	WARN_ON(ret);

	ufile->ucontext = NULL;
}

static int __uverbs_cleanup_ufile(struct ib_uverbs_file *ufile,
				  enum rdma_remove_reason reason)
{
	struct ib_uobject *obj, *next_obj;
	int ret = -EINVAL;

	/*
	 * This shouldn't run while executing other commands on this
	 * context. Thus, the only thing we should take care of is
	 * releasing a FD while traversing this list. The FD could be
	 * closed and released from the _release fop of this FD.
	 * In order to mitigate this, we add a lock.
	 * We take and release the lock per traversal in order to let
	 * other threads (which might still use the FDs) chance to run.
	 */
	list_for_each_entry_safe(obj, next_obj, &ufile->uobjects, list) {
		/*
		 * if we hit this WARN_ON, that means we are
		 * racing with a lookup_get.
		 */
		WARN_ON(uverbs_try_lock_object(obj, UVERBS_LOOKUP_WRITE));
		if (!uverbs_destroy_uobject(obj, reason))
			ret = 0;
		else
			atomic_set(&obj->usecnt, 0);
	}
	return ret;
}

/*
 * Destroy the uncontext and every uobject associated with it. If called with
 * reason != RDMA_REMOVE_CLOSE this will not return until the destruction has
 * been completed and ufile->ucontext is NULL.
 *
 * This is internally locked and can be called in parallel from multiple
 * contexts.
 */
void uverbs_destroy_ufile_hw(struct ib_uverbs_file *ufile,
			     enum rdma_remove_reason reason)
{
	if (reason == RDMA_REMOVE_CLOSE) {
		/*
		 * During destruction we might trigger something that
		 * synchronously calls release on any file descriptor. For
		 * this reason all paths that come from file_operations
		 * release must use try_lock. They can progress knowing that
		 * there is an ongoing uverbs_destroy_ufile_hw that will clean
		 * up the driver resources.
		 */
		if (!mutex_trylock(&ufile->ucontext_lock))
			return;

	} else {
		mutex_lock(&ufile->ucontext_lock);
	}

	down_write(&ufile->hw_destroy_rwsem);

	/*
	 * If a ucontext was never created then we can't have any uobjects to
	 * cleanup, nothing to do.
	 */
	if (!ufile->ucontext)
		goto done;

	ufile->ucontext->closing = true;
	ufile->ucontext->cleanup_retryable = true;
	while (!list_empty(&ufile->uobjects))
		if (__uverbs_cleanup_ufile(ufile, reason)) {
			/*
			 * No entry was cleaned-up successfully during this
			 * iteration
			 */
			break;
		}

	ufile->ucontext->cleanup_retryable = false;
	if (!list_empty(&ufile->uobjects))
		__uverbs_cleanup_ufile(ufile, reason);

	ufile_destroy_ucontext(ufile, reason);

done:
	up_write(&ufile->hw_destroy_rwsem);
	mutex_unlock(&ufile->ucontext_lock);
=======

static void _uverbs_close_fd(struct ib_uobject_file *uobj_file)
{
	struct ib_ucontext *ucontext;
	struct ib_uverbs_file *ufile = uobj_file->ufile;
	int ret;

	mutex_lock(&uobj_file->ufile->cleanup_mutex);

	/* uobject was either already cleaned up or is cleaned up right now anyway */
	if (!uobj_file->uobj.context ||
	    !down_read_trylock(&uobj_file->uobj.context->cleanup_rwsem))
		goto unlock;

	ucontext = uobj_file->uobj.context;
	ret = _rdma_remove_commit_uobject(&uobj_file->uobj, RDMA_REMOVE_CLOSE);
	up_read(&ucontext->cleanup_rwsem);
	if (ret)
		pr_warn("uverbs: unable to clean up uobject file in uverbs_close_fd.\n");
unlock:
	mutex_unlock(&ufile->cleanup_mutex);
}

void uverbs_close_fd(struct file *f)
{
	struct ib_uobject_file *uobj_file = f->private_data;
	struct kref *uverbs_file_ref = &uobj_file->ufile->ref;

	_uverbs_close_fd(uobj_file);
	uverbs_uobject_put(&uobj_file->uobj);
	kref_put(uverbs_file_ref, ib_uverbs_release_file);
}

void uverbs_cleanup_ucontext(struct ib_ucontext *ucontext, bool device_removed)
{
	enum rdma_remove_reason reason = device_removed ?
		RDMA_REMOVE_DRIVER_REMOVE : RDMA_REMOVE_CLOSE;
	unsigned int cur_order = 0;

	ucontext->cleanup_reason = reason;
	/*
	 * Waits for all remove_commit and alloc_commit to finish. Logically, We
	 * want to hold this forever as the context is going to be destroyed,
	 * but we'll release it since it causes a "held lock freed" BUG message.
	 */
	down_write(&ucontext->cleanup_rwsem);

	while (!list_empty(&ucontext->uobjects)) {
		struct ib_uobject *obj, *next_obj;
		unsigned int next_order = UINT_MAX;

		/*
		 * This shouldn't run while executing other commands on this
		 * context. Thus, the only thing we should take care of is
		 * releasing a FD while traversing this list. The FD could be
		 * closed and released from the _release fop of this FD.
		 * In order to mitigate this, we add a lock.
		 * We take and release the lock per order traversal in order
		 * to let other threads (which might still use the FDs) chance
		 * to run.
		 */
		mutex_lock(&ucontext->uobjects_lock);
		list_for_each_entry_safe(obj, next_obj, &ucontext->uobjects,
					 list) {
			if (obj->type->destroy_order == cur_order) {
				int ret;

				/*
				 * if we hit this WARN_ON, that means we are
				 * racing with a lookup_get.
				 */
				WARN_ON(uverbs_try_lock_object(obj, true));
				ret = obj->type->type_class->remove_commit(obj,
									   reason);
				list_del(&obj->list);
				if (ret)
					pr_warn("ib_uverbs: failed to remove uobject id %d order %u\n",
						obj->id, cur_order);
				/* put the ref we took when we created the object */
				uverbs_uobject_put(obj);
			} else {
				next_order = min(next_order,
						 obj->type->destroy_order);
			}
		}
		mutex_unlock(&ucontext->uobjects_lock);
		cur_order = next_order;
	}
	up_write(&ucontext->cleanup_rwsem);
}

void uverbs_initialize_ucontext(struct ib_ucontext *ucontext)
{
	ucontext->cleanup_reason = 0;
	mutex_init(&ucontext->uobjects_lock);
	INIT_LIST_HEAD(&ucontext->uobjects);
	init_rwsem(&ucontext->cleanup_rwsem);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

const struct uverbs_obj_type_class uverbs_fd_class = {
	.alloc_begin = alloc_begin_fd_uobject,
	.lookup_get = lookup_get_fd_uobject,
	.alloc_commit = alloc_commit_fd_uobject,
	.alloc_abort = alloc_abort_fd_uobject,
	.lookup_put = lookup_put_fd_uobject,
<<<<<<< HEAD
	.destroy_hw = destroy_hw_fd_uobject,
	.remove_handle = remove_handle_fd_uobject,
	.needs_kfree_rcu = false,
};
EXPORT_SYMBOL(uverbs_fd_class);

struct ib_uobject *
uverbs_get_uobject_from_file(u16 object_id,
			     struct ib_uverbs_file *ufile,
			     enum uverbs_obj_access access, s64 id)
{
	const struct uverbs_api_object *obj =
		uapi_get_object(ufile->device->uapi, object_id);

	switch (access) {
	case UVERBS_ACCESS_READ:
		return rdma_lookup_get_uobject(obj, ufile, id,
					       UVERBS_LOOKUP_READ);
	case UVERBS_ACCESS_DESTROY:
		/* Actual destruction is done inside uverbs_handle_method */
		return rdma_lookup_get_uobject(obj, ufile, id,
					       UVERBS_LOOKUP_DESTROY);
	case UVERBS_ACCESS_WRITE:
		return rdma_lookup_get_uobject(obj, ufile, id,
					       UVERBS_LOOKUP_WRITE);
	case UVERBS_ACCESS_NEW:
		return rdma_alloc_begin_uobject(obj, ufile);
=======
	.remove_commit = remove_commit_fd_uobject,
	.needs_kfree_rcu = false,
};

struct ib_uobject *uverbs_get_uobject_from_context(const struct uverbs_obj_type *type_attrs,
						   struct ib_ucontext *ucontext,
						   enum uverbs_obj_access access,
						   int id)
{
	switch (access) {
	case UVERBS_ACCESS_READ:
		return rdma_lookup_get_uobject(type_attrs, ucontext, id, false);
	case UVERBS_ACCESS_DESTROY:
	case UVERBS_ACCESS_WRITE:
		return rdma_lookup_get_uobject(type_attrs, ucontext, id, true);
	case UVERBS_ACCESS_NEW:
		return rdma_alloc_begin_uobject(type_attrs, ucontext);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	default:
		WARN_ON(true);
		return ERR_PTR(-EOPNOTSUPP);
	}
}

int uverbs_finalize_object(struct ib_uobject *uobj,
			   enum uverbs_obj_access access,
			   bool commit)
{
	int ret = 0;

	/*
	 * refcounts should be handled at the object level and not at the
	 * uobject level. Refcounts of the objects themselves are done in
	 * handlers.
	 */

	switch (access) {
	case UVERBS_ACCESS_READ:
<<<<<<< HEAD
		rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_READ);
		break;
	case UVERBS_ACCESS_WRITE:
		rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_WRITE);
		break;
	case UVERBS_ACCESS_DESTROY:
		if (uobj)
			rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_DESTROY);
=======
		rdma_lookup_put_uobject(uobj, false);
		break;
	case UVERBS_ACCESS_WRITE:
		rdma_lookup_put_uobject(uobj, true);
		break;
	case UVERBS_ACCESS_DESTROY:
		if (commit)
			ret = rdma_remove_commit_uobject(uobj);
		else
			rdma_lookup_put_uobject(uobj, true);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		break;
	case UVERBS_ACCESS_NEW:
		if (commit)
			ret = rdma_alloc_commit_uobject(uobj);
		else
			rdma_alloc_abort_uobject(uobj);
		break;
	default:
		WARN_ON(true);
		ret = -EOPNOTSUPP;
	}

	return ret;
}
<<<<<<< HEAD
=======

int uverbs_finalize_objects(struct uverbs_attr_bundle *attrs_bundle,
			    struct uverbs_attr_spec_hash * const *spec_hash,
			    size_t num,
			    bool commit)
{
	unsigned int i;
	int ret = 0;

	for (i = 0; i < num; i++) {
		struct uverbs_attr_bundle_hash *curr_bundle =
			&attrs_bundle->hash[i];
		const struct uverbs_attr_spec_hash *curr_spec_bucket =
			spec_hash[i];
		unsigned int j;

		for (j = 0; j < curr_bundle->num_attrs; j++) {
			struct uverbs_attr *attr;
			const struct uverbs_attr_spec *spec;

			if (!uverbs_attr_is_valid_in_hash(curr_bundle, j))
				continue;

			attr = &curr_bundle->attrs[j];
			spec = &curr_spec_bucket->attrs[j];

			if (spec->type == UVERBS_ATTR_TYPE_IDR ||
			    spec->type == UVERBS_ATTR_TYPE_FD) {
				int current_ret;

				current_ret = uverbs_finalize_object(attr->obj_attr.uobject,
								     spec->obj.access,
								     commit);
				if (!ret)
					ret = current_ret;
			}
		}
	}
	return ret;
}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
