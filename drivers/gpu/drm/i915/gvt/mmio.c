/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Ke Yu
 *    Kevin Tian <kevin.tian@intel.com>
 *    Dexuan Cui
 *
 * Contributors:
 *    Tina Zhang <tina.zhang@intel.com>
 *    Min He <min.he@intel.com>
 *    Niu Bing <bing.niu@intel.com>
 *    Zhi Wang <zhi.a.wang@intel.com>
 *
 */

#include "i915_drv.h"
#include "gvt.h"

/**
 * intel_vgpu_gpa_to_mmio_offset - translate a GPA to MMIO offset
 * @vgpu: a vGPU
 *
 * Returns:
 * Zero on success, negative error code if failed
 */
int intel_vgpu_gpa_to_mmio_offset(struct intel_vgpu *vgpu, u64 gpa)
{
<<<<<<< HEAD
	u64 gttmmio_gpa = intel_vgpu_get_bar_gpa(vgpu, PCI_BASE_ADDRESS_0);
=======
	u64 gttmmio_gpa = *(u64 *)(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_0) &
			  ~GENMASK(3, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return gpa - gttmmio_gpa;
}

#define reg_is_mmio(gvt, reg)  \
	(reg >= 0 && reg < gvt->device_info.mmio_size)

#define reg_is_gtt(gvt, reg)   \
	(reg >= gvt->device_info.gtt_start_offset \
	 && reg < gvt->device_info.gtt_start_offset + gvt_ggtt_sz(gvt))

static void failsafe_emulate_mmio_rw(struct intel_vgpu *vgpu, uint64_t pa,
		void *p_data, unsigned int bytes, bool read)
{
	struct intel_gvt *gvt = NULL;
	void *pt = NULL;
	unsigned int offset = 0;

	if (!vgpu || !p_data)
		return;

	gvt = vgpu->gvt;
<<<<<<< HEAD
	mutex_lock(&vgpu->vgpu_lock);
=======
	mutex_lock(&gvt->lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	offset = intel_vgpu_gpa_to_mmio_offset(vgpu, pa);
	if (reg_is_mmio(gvt, offset)) {
		if (read)
			intel_vgpu_default_mmio_read(vgpu, offset, p_data,
					bytes);
		else
			intel_vgpu_default_mmio_write(vgpu, offset, p_data,
					bytes);
<<<<<<< HEAD
	} else if (reg_is_gtt(gvt, offset)) {
		offset -= gvt->device_info.gtt_start_offset;
		pt = vgpu->gtt.ggtt_mm->ggtt_mm.virtual_ggtt + offset;
=======
	} else if (reg_is_gtt(gvt, offset) &&
			vgpu->gtt.ggtt_mm->virtual_page_table) {
		offset -= gvt->device_info.gtt_start_offset;
		pt = vgpu->gtt.ggtt_mm->virtual_page_table + offset;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (read)
			memcpy(p_data, pt, bytes);
		else
			memcpy(pt, p_data, bytes);

<<<<<<< HEAD
	}
	mutex_unlock(&vgpu->vgpu_lock);
=======
	} else if (atomic_read(&vgpu->gtt.n_write_protected_guest_page)) {
		struct intel_vgpu_guest_page *gp;

		/* Since we enter the failsafe mode early during guest boot,
		 * guest may not have chance to set up its ppgtt table, so
		 * there should not be any wp pages for guest. Keep the wp
		 * related code here in case we need to handle it in furture.
		 */
		gp = intel_vgpu_find_guest_page(vgpu, pa >> PAGE_SHIFT);
		if (gp) {
			/* remove write protection to prevent furture traps */
			intel_vgpu_clean_guest_page(vgpu, gp);
			if (read)
				intel_gvt_hypervisor_read_gpa(vgpu, pa,
						p_data, bytes);
			else
				intel_gvt_hypervisor_write_gpa(vgpu, pa,
						p_data, bytes);
		}
	}
	mutex_unlock(&gvt->lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * intel_vgpu_emulate_mmio_read - emulate MMIO read
 * @vgpu: a vGPU
 * @pa: guest physical address
 * @p_data: data return buffer
 * @bytes: access data length
 *
 * Returns:
 * Zero on success, negative error code if failed
 */
int intel_vgpu_emulate_mmio_read(struct intel_vgpu *vgpu, uint64_t pa,
		void *p_data, unsigned int bytes)
{
	struct intel_gvt *gvt = vgpu->gvt;
	unsigned int offset = 0;
	int ret = -EINVAL;

<<<<<<< HEAD
=======

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (vgpu->failsafe) {
		failsafe_emulate_mmio_rw(vgpu, pa, p_data, bytes, true);
		return 0;
	}
<<<<<<< HEAD
	mutex_lock(&vgpu->vgpu_lock);
=======
	mutex_lock(&gvt->lock);

	if (atomic_read(&vgpu->gtt.n_write_protected_guest_page)) {
		struct intel_vgpu_guest_page *gp;

		gp = intel_vgpu_find_guest_page(vgpu, pa >> PAGE_SHIFT);
		if (gp) {
			ret = intel_gvt_hypervisor_read_gpa(vgpu, pa,
					p_data, bytes);
			if (ret) {
				gvt_vgpu_err("guest page read error %d, "
					"gfn 0x%lx, pa 0x%llx, var 0x%x, len %d\n",
					ret, gp->gfn, pa, *(u32 *)p_data,
					bytes);
			}
			mutex_unlock(&gvt->lock);
			return ret;
		}
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	offset = intel_vgpu_gpa_to_mmio_offset(vgpu, pa);

	if (WARN_ON(bytes > 8))
		goto err;

	if (reg_is_gtt(gvt, offset)) {
		if (WARN_ON(!IS_ALIGNED(offset, 4) && !IS_ALIGNED(offset, 8)))
			goto err;
		if (WARN_ON(bytes != 4 && bytes != 8))
			goto err;
		if (WARN_ON(!reg_is_gtt(gvt, offset + bytes - 1)))
			goto err;

<<<<<<< HEAD
		ret = intel_vgpu_emulate_ggtt_mmio_read(vgpu, offset,
				p_data, bytes);
		if (ret)
			goto err;
		goto out;
=======
		ret = intel_vgpu_emulate_gtt_mmio_read(vgpu, offset,
				p_data, bytes);
		if (ret)
			goto err;
		mutex_unlock(&gvt->lock);
		return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	if (WARN_ON_ONCE(!reg_is_mmio(gvt, offset))) {
		ret = intel_gvt_hypervisor_read_gpa(vgpu, pa, p_data, bytes);
<<<<<<< HEAD
		goto out;
=======
		mutex_unlock(&gvt->lock);
		return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	if (WARN_ON(!reg_is_mmio(gvt, offset + bytes - 1)))
		goto err;

	if (!intel_gvt_mmio_is_unalign(gvt, offset)) {
		if (WARN_ON(!IS_ALIGNED(offset, bytes)))
			goto err;
	}

	ret = intel_vgpu_mmio_reg_rw(vgpu, offset, p_data, bytes, true);
	if (ret < 0)
		goto err;

	intel_gvt_mmio_set_accessed(gvt, offset);
<<<<<<< HEAD
	ret = 0;
	goto out;

err:
	gvt_vgpu_err("fail to emulate MMIO read %08x len %d\n",
			offset, bytes);
out:
	mutex_unlock(&vgpu->vgpu_lock);
=======
	mutex_unlock(&gvt->lock);
	return 0;
err:
	gvt_vgpu_err("fail to emulate MMIO read %08x len %d\n",
			offset, bytes);
	mutex_unlock(&gvt->lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

/**
 * intel_vgpu_emulate_mmio_write - emulate MMIO write
 * @vgpu: a vGPU
 * @pa: guest physical address
 * @p_data: write data buffer
 * @bytes: access data length
 *
 * Returns:
 * Zero on success, negative error code if failed
 */
int intel_vgpu_emulate_mmio_write(struct intel_vgpu *vgpu, uint64_t pa,
		void *p_data, unsigned int bytes)
{
	struct intel_gvt *gvt = vgpu->gvt;
	unsigned int offset = 0;
	int ret = -EINVAL;

	if (vgpu->failsafe) {
		failsafe_emulate_mmio_rw(vgpu, pa, p_data, bytes, false);
		return 0;
	}

<<<<<<< HEAD
	mutex_lock(&vgpu->vgpu_lock);
=======
	mutex_lock(&gvt->lock);

	if (atomic_read(&vgpu->gtt.n_write_protected_guest_page)) {
		struct intel_vgpu_guest_page *gp;

		gp = intel_vgpu_find_guest_page(vgpu, pa >> PAGE_SHIFT);
		if (gp) {
			ret = gp->handler(gp, pa, p_data, bytes);
			if (ret) {
				gvt_err("guest page write error %d, "
					"gfn 0x%lx, pa 0x%llx, "
					"var 0x%x, len %d\n",
					ret, gp->gfn, pa,
					*(u32 *)p_data, bytes);
			}
			mutex_unlock(&gvt->lock);
			return ret;
		}
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	offset = intel_vgpu_gpa_to_mmio_offset(vgpu, pa);

	if (WARN_ON(bytes > 8))
		goto err;

	if (reg_is_gtt(gvt, offset)) {
		if (WARN_ON(!IS_ALIGNED(offset, 4) && !IS_ALIGNED(offset, 8)))
			goto err;
		if (WARN_ON(bytes != 4 && bytes != 8))
			goto err;
		if (WARN_ON(!reg_is_gtt(gvt, offset + bytes - 1)))
			goto err;

<<<<<<< HEAD
		ret = intel_vgpu_emulate_ggtt_mmio_write(vgpu, offset,
				p_data, bytes);
		if (ret)
			goto err;
		goto out;
=======
		ret = intel_vgpu_emulate_gtt_mmio_write(vgpu, offset,
				p_data, bytes);
		if (ret)
			goto err;
		mutex_unlock(&gvt->lock);
		return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	if (WARN_ON_ONCE(!reg_is_mmio(gvt, offset))) {
		ret = intel_gvt_hypervisor_write_gpa(vgpu, pa, p_data, bytes);
<<<<<<< HEAD
		goto out;
=======
		mutex_unlock(&gvt->lock);
		return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	ret = intel_vgpu_mmio_reg_rw(vgpu, offset, p_data, bytes, false);
	if (ret < 0)
		goto err;

	intel_gvt_mmio_set_accessed(gvt, offset);
<<<<<<< HEAD
	ret = 0;
	goto out;
err:
	gvt_vgpu_err("fail to emulate MMIO write %08x len %d\n", offset,
		     bytes);
out:
	mutex_unlock(&vgpu->vgpu_lock);
=======
	mutex_unlock(&gvt->lock);
	return 0;
err:
	gvt_vgpu_err("fail to emulate MMIO write %08x len %d\n", offset,
		     bytes);
	mutex_unlock(&gvt->lock);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}


/**
 * intel_vgpu_reset_mmio - reset virtual MMIO space
 * @vgpu: a vGPU
 *
 */
void intel_vgpu_reset_mmio(struct intel_vgpu *vgpu, bool dmlr)
{
	struct intel_gvt *gvt = vgpu->gvt;
	const struct intel_gvt_device_info *info = &gvt->device_info;
	void  *mmio = gvt->firmware.mmio;

	if (dmlr) {
		memcpy(vgpu->mmio.vreg, mmio, info->mmio_size);
		memcpy(vgpu->mmio.sreg, mmio, info->mmio_size);

<<<<<<< HEAD
		vgpu_vreg_t(vgpu, GEN6_GT_THREAD_STATUS_REG) = 0;

		/* set the bit 0:2(Core C-State ) to C0 */
		vgpu_vreg_t(vgpu, GEN6_GT_CORE_STATUS) = 0;

		if (IS_BROXTON(vgpu->gvt->dev_priv)) {
			vgpu_vreg_t(vgpu, BXT_P_CR_GT_DISP_PWRON) &=
				    ~(BIT(0) | BIT(1));
			vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY0)) &=
				    ~PHY_POWER_GOOD;
			vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY1)) &=
				    ~PHY_POWER_GOOD;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY0)) &=
				    ~BIT(30);
			vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY1)) &=
				    ~BIT(30);
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_A)) &=
				    ~BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_A)) |=
				    BXT_PHY_CMNLANE_POWERDOWN_ACK |
				    BXT_PHY_LANE_POWERDOWN_ACK;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_B)) &=
				    ~BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_B)) |=
				    BXT_PHY_CMNLANE_POWERDOWN_ACK |
				    BXT_PHY_LANE_POWERDOWN_ACK;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_C)) &=
				    ~BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_C)) |=
				    BXT_PHY_CMNLANE_POWERDOWN_ACK |
				    BXT_PHY_LANE_POWERDOWN_ACK;
		}
=======
		vgpu_vreg(vgpu, GEN6_GT_THREAD_STATUS_REG) = 0;

		/* set the bit 0:2(Core C-State ) to C0 */
		vgpu_vreg(vgpu, GEN6_GT_CORE_STATUS) = 0;

		vgpu->mmio.disable_warn_untrack = false;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	} else {
#define GVT_GEN8_MMIO_RESET_OFFSET		(0x44200)
		/* only reset the engine related, so starting with 0x44200
		 * interrupt include DE,display mmio related will not be
		 * touched
		 */
		memcpy(vgpu->mmio.vreg, mmio, GVT_GEN8_MMIO_RESET_OFFSET);
		memcpy(vgpu->mmio.sreg, mmio, GVT_GEN8_MMIO_RESET_OFFSET);
	}

}

/**
 * intel_vgpu_init_mmio - init MMIO  space
 * @vgpu: a vGPU
 *
 * Returns:
 * Zero on success, negative error code if failed
 */
int intel_vgpu_init_mmio(struct intel_vgpu *vgpu)
{
	const struct intel_gvt_device_info *info = &vgpu->gvt->device_info;

<<<<<<< HEAD
	vgpu->mmio.vreg = vzalloc(array_size(info->mmio_size, 2));
=======
	vgpu->mmio.vreg = vzalloc(info->mmio_size * 2);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!vgpu->mmio.vreg)
		return -ENOMEM;

	vgpu->mmio.sreg = vgpu->mmio.vreg + info->mmio_size;

	intel_vgpu_reset_mmio(vgpu, true);

	return 0;
}

/**
 * intel_vgpu_clean_mmio - clean MMIO space
 * @vgpu: a vGPU
 *
 */
void intel_vgpu_clean_mmio(struct intel_vgpu *vgpu)
{
	vfree(vgpu->mmio.vreg);
	vgpu->mmio.vreg = vgpu->mmio.sreg = NULL;
}
