/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Yakir Yang <ykk@rock-chips.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>

#include "rockchip_drm_drv.h"
#include "rockchip_drm_psr.h"

<<<<<<< HEAD
#define PSR_FLUSH_TIMEOUT_MS	100
=======
#define PSR_FLUSH_TIMEOUT	msecs_to_jiffies(100)

enum psr_state {
	PSR_FLUSH,
	PSR_ENABLE,
	PSR_DISABLE,
};
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct psr_drv {
	struct list_head	list;
	struct drm_encoder	*encoder;

<<<<<<< HEAD
	struct mutex		lock;
	int			inhibit_count;
	bool			enabled;

	struct delayed_work	flush_work;

	int (*set)(struct drm_encoder *encoder, bool enable);
};

static struct psr_drv *find_psr_by_encoder(struct drm_encoder *encoder)
{
	struct rockchip_drm_private *drm_drv = encoder->dev->dev_private;
	struct psr_drv *psr;

	mutex_lock(&drm_drv->psr_list_lock);
	list_for_each_entry(psr, &drm_drv->psr_list, list) {
		if (psr->encoder == encoder)
=======
	spinlock_t		lock;
	bool			active;
	enum psr_state		state;

	struct timer_list	flush_timer;

	void (*set)(struct drm_encoder *encoder, bool enable);
};

static struct psr_drv *find_psr_by_crtc(struct drm_crtc *crtc)
{
	struct rockchip_drm_private *drm_drv = crtc->dev->dev_private;
	struct psr_drv *psr;
	unsigned long flags;

	spin_lock_irqsave(&drm_drv->psr_list_lock, flags);
	list_for_each_entry(psr, &drm_drv->psr_list, list) {
		if (psr->encoder->crtc == crtc)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			goto out;
	}
	psr = ERR_PTR(-ENODEV);

out:
<<<<<<< HEAD
	mutex_unlock(&drm_drv->psr_list_lock);
	return psr;
}

static int psr_set_state_locked(struct psr_drv *psr, bool enable)
{
	int ret;

	if (psr->inhibit_count > 0)
		return -EINVAL;

	if (enable == psr->enabled)
		return 0;

	ret = psr->set(psr->encoder, enable);
	if (ret)
		return ret;

	psr->enabled = enable;
	return 0;
}

static void psr_flush_handler(struct work_struct *work)
{
	struct psr_drv *psr = container_of(to_delayed_work(work),
					   struct psr_drv, flush_work);

	mutex_lock(&psr->lock);
	psr_set_state_locked(psr, true);
	mutex_unlock(&psr->lock);
}

/**
 * rockchip_drm_psr_inhibit_put - release PSR inhibit on given encoder
 * @encoder: encoder to obtain the PSR encoder
 *
 * Decrements PSR inhibit count on given encoder. Should be called only
 * for a PSR inhibit count increment done before. If PSR inhibit counter
 * reaches zero, PSR flush work is scheduled to make the hardware enter
 * PSR mode in PSR_FLUSH_TIMEOUT_MS.
=======
	spin_unlock_irqrestore(&drm_drv->psr_list_lock, flags);
	return psr;
}

static void psr_set_state_locked(struct psr_drv *psr, enum psr_state state)
{
	/*
	 * Allowed finite state machine:
	 *
	 *   PSR_ENABLE  < = = = = = >  PSR_FLUSH
	 *       | ^                        |
	 *       | |                        |
	 *       v |                        |
	 *   PSR_DISABLE < - - - - - - - - -
	 */
	if (state == psr->state || !psr->active)
		return;

	/* Already disabled in flush, change the state, but not the hardware */
	if (state == PSR_DISABLE && psr->state == PSR_FLUSH) {
		psr->state = state;
		return;
	}

	psr->state = state;

	/* Actually commit the state change to hardware */
	switch (psr->state) {
	case PSR_ENABLE:
		psr->set(psr->encoder, true);
		break;

	case PSR_DISABLE:
	case PSR_FLUSH:
		psr->set(psr->encoder, false);
		break;
	}
}

static void psr_set_state(struct psr_drv *psr, enum psr_state state)
{
	unsigned long flags;

	spin_lock_irqsave(&psr->lock, flags);
	psr_set_state_locked(psr, state);
	spin_unlock_irqrestore(&psr->lock, flags);
}

static void psr_flush_handler(unsigned long data)
{
	struct psr_drv *psr = (struct psr_drv *)data;
	unsigned long flags;

	/* If the state has changed since we initiated the flush, do nothing */
	spin_lock_irqsave(&psr->lock, flags);
	if (psr->state == PSR_FLUSH)
		psr_set_state_locked(psr, PSR_ENABLE);
	spin_unlock_irqrestore(&psr->lock, flags);
}

/**
 * rockchip_drm_psr_activate - activate PSR on the given pipe
 * @crtc: CRTC to obtain the PSR encoder
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * Returns:
 * Zero on success, negative errno on failure.
 */
<<<<<<< HEAD
int rockchip_drm_psr_inhibit_put(struct drm_encoder *encoder)
{
	struct psr_drv *psr = find_psr_by_encoder(encoder);
=======
int rockchip_drm_psr_activate(struct drm_crtc *crtc)
{
	struct psr_drv *psr = find_psr_by_crtc(crtc);
	unsigned long flags;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (IS_ERR(psr))
		return PTR_ERR(psr);

<<<<<<< HEAD
	mutex_lock(&psr->lock);
	--psr->inhibit_count;
	WARN_ON(psr->inhibit_count < 0);
	if (!psr->inhibit_count)
		mod_delayed_work(system_wq, &psr->flush_work,
				 PSR_FLUSH_TIMEOUT_MS);
	mutex_unlock(&psr->lock);

	return 0;
}
EXPORT_SYMBOL(rockchip_drm_psr_inhibit_put);

/**
 * rockchip_drm_psr_inhibit_get - acquire PSR inhibit on given encoder
 * @encoder: encoder to obtain the PSR encoder
 *
 * Increments PSR inhibit count on given encoder. This function guarantees
 * that after it returns PSR is turned off on given encoder and no PSR-related
 * hardware state change occurs at least until a matching call to
 * rockchip_drm_psr_inhibit_put() is done.
=======
	spin_lock_irqsave(&psr->lock, flags);
	psr->active = true;
	spin_unlock_irqrestore(&psr->lock, flags);

	return 0;
}
EXPORT_SYMBOL(rockchip_drm_psr_activate);

/**
 * rockchip_drm_psr_deactivate - deactivate PSR on the given pipe
 * @crtc: CRTC to obtain the PSR encoder
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * Returns:
 * Zero on success, negative errno on failure.
 */
<<<<<<< HEAD
int rockchip_drm_psr_inhibit_get(struct drm_encoder *encoder)
{
	struct psr_drv *psr = find_psr_by_encoder(encoder);
=======
int rockchip_drm_psr_deactivate(struct drm_crtc *crtc)
{
	struct psr_drv *psr = find_psr_by_crtc(crtc);
	unsigned long flags;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (IS_ERR(psr))
		return PTR_ERR(psr);

<<<<<<< HEAD
	mutex_lock(&psr->lock);
	psr_set_state_locked(psr, false);
	++psr->inhibit_count;
	mutex_unlock(&psr->lock);
	cancel_delayed_work_sync(&psr->flush_work);

	return 0;
}
EXPORT_SYMBOL(rockchip_drm_psr_inhibit_get);

static void rockchip_drm_do_flush(struct psr_drv *psr)
{
	cancel_delayed_work_sync(&psr->flush_work);

	mutex_lock(&psr->lock);
	if (!psr_set_state_locked(psr, false))
		mod_delayed_work(system_wq, &psr->flush_work,
				 PSR_FLUSH_TIMEOUT_MS);
	mutex_unlock(&psr->lock);
}

/**
=======
	spin_lock_irqsave(&psr->lock, flags);
	psr->active = false;
	spin_unlock_irqrestore(&psr->lock, flags);
	del_timer_sync(&psr->flush_timer);

	return 0;
}
EXPORT_SYMBOL(rockchip_drm_psr_deactivate);

static void rockchip_drm_do_flush(struct psr_drv *psr)
{
	mod_timer(&psr->flush_timer,
		  round_jiffies_up(jiffies + PSR_FLUSH_TIMEOUT));
	psr_set_state(psr, PSR_FLUSH);
}

/**
 * rockchip_drm_psr_flush - flush a single pipe
 * @crtc: CRTC of the pipe to flush
 *
 * Returns:
 * 0 on success, -errno on fail
 */
int rockchip_drm_psr_flush(struct drm_crtc *crtc)
{
	struct psr_drv *psr = find_psr_by_crtc(crtc);
	if (IS_ERR(psr))
		return PTR_ERR(psr);

	rockchip_drm_do_flush(psr);
	return 0;
}
EXPORT_SYMBOL(rockchip_drm_psr_flush);

/**
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * rockchip_drm_psr_flush_all - force to flush all registered PSR encoders
 * @dev: drm device
 *
 * Disable the PSR function for all registered encoders, and then enable the
 * PSR function back after PSR_FLUSH_TIMEOUT. If encoder PSR state have been
 * changed during flush time, then keep the state no change after flush
 * timeout.
 *
 * Returns:
 * Zero on success, negative errno on failure.
 */
void rockchip_drm_psr_flush_all(struct drm_device *dev)
{
	struct rockchip_drm_private *drm_drv = dev->dev_private;
	struct psr_drv *psr;
<<<<<<< HEAD

	mutex_lock(&drm_drv->psr_list_lock);
	list_for_each_entry(psr, &drm_drv->psr_list, list)
		rockchip_drm_do_flush(psr);
	mutex_unlock(&drm_drv->psr_list_lock);
=======
	unsigned long flags;

	spin_lock_irqsave(&drm_drv->psr_list_lock, flags);
	list_for_each_entry(psr, &drm_drv->psr_list, list)
		rockchip_drm_do_flush(psr);
	spin_unlock_irqrestore(&drm_drv->psr_list_lock, flags);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
EXPORT_SYMBOL(rockchip_drm_psr_flush_all);

/**
 * rockchip_drm_psr_register - register encoder to psr driver
 * @encoder: encoder that obtain the PSR function
 * @psr_set: call back to set PSR state
 *
<<<<<<< HEAD
 * The function returns with PSR inhibit counter initialized with one
 * and the caller (typically encoder driver) needs to call
 * rockchip_drm_psr_inhibit_put() when it becomes ready to accept PSR
 * enable request.
 *
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * Returns:
 * Zero on success, negative errno on failure.
 */
int rockchip_drm_psr_register(struct drm_encoder *encoder,
<<<<<<< HEAD
			int (*psr_set)(struct drm_encoder *, bool enable))
{
	struct rockchip_drm_private *drm_drv;
	struct psr_drv *psr;
=======
			void (*psr_set)(struct drm_encoder *, bool enable))
{
	struct rockchip_drm_private *drm_drv;
	struct psr_drv *psr;
	unsigned long flags;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!encoder || !psr_set)
		return -EINVAL;

	drm_drv = encoder->dev->dev_private;

	psr = kzalloc(sizeof(struct psr_drv), GFP_KERNEL);
	if (!psr)
		return -ENOMEM;

<<<<<<< HEAD
	INIT_DELAYED_WORK(&psr->flush_work, psr_flush_handler);
	mutex_init(&psr->lock);

	psr->inhibit_count = 1;
	psr->enabled = false;
	psr->encoder = encoder;
	psr->set = psr_set;

	mutex_lock(&drm_drv->psr_list_lock);
	list_add_tail(&psr->list, &drm_drv->psr_list);
	mutex_unlock(&drm_drv->psr_list_lock);
=======
	setup_timer(&psr->flush_timer, psr_flush_handler, (unsigned long)psr);
	spin_lock_init(&psr->lock);

	psr->active = true;
	psr->state = PSR_DISABLE;
	psr->encoder = encoder;
	psr->set = psr_set;

	spin_lock_irqsave(&drm_drv->psr_list_lock, flags);
	list_add_tail(&psr->list, &drm_drv->psr_list);
	spin_unlock_irqrestore(&drm_drv->psr_list_lock, flags);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}
EXPORT_SYMBOL(rockchip_drm_psr_register);

/**
 * rockchip_drm_psr_unregister - unregister encoder to psr driver
 * @encoder: encoder that obtain the PSR function
 * @psr_set: call back to set PSR state
 *
<<<<<<< HEAD
 * It is expected that the PSR inhibit counter is 1 when this function is
 * called, which corresponds to a state when related encoder has been
 * disconnected from any CRTCs and its driver called
 * rockchip_drm_psr_inhibit_get() to stop the PSR logic.
 *
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * Returns:
 * Zero on success, negative errno on failure.
 */
void rockchip_drm_psr_unregister(struct drm_encoder *encoder)
{
	struct rockchip_drm_private *drm_drv = encoder->dev->dev_private;
	struct psr_drv *psr, *n;
<<<<<<< HEAD

	mutex_lock(&drm_drv->psr_list_lock);
	list_for_each_entry_safe(psr, n, &drm_drv->psr_list, list) {
		if (psr->encoder == encoder) {
			/*
			 * Any other value would mean that the encoder
			 * is still in use.
			 */
			WARN_ON(psr->inhibit_count != 1);

=======
	unsigned long flags;

	spin_lock_irqsave(&drm_drv->psr_list_lock, flags);
	list_for_each_entry_safe(psr, n, &drm_drv->psr_list, list) {
		if (psr->encoder == encoder) {
			del_timer(&psr->flush_timer);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			list_del(&psr->list);
			kfree(psr);
		}
	}
<<<<<<< HEAD
	mutex_unlock(&drm_drv->psr_list_lock);
=======
	spin_unlock_irqrestore(&drm_drv->psr_list_lock, flags);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
EXPORT_SYMBOL(rockchip_drm_psr_unregister);
