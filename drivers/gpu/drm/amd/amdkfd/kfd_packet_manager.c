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
 *
 */

#include <linux/slab.h>
#include <linux/mutex.h>
#include "kfd_device_queue_manager.h"
#include "kfd_kernel_queue.h"
#include "kfd_priv.h"
<<<<<<< HEAD
=======
#include "kfd_pm4_headers_vi.h"
#include "kfd_pm4_opcodes.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static inline void inc_wptr(unsigned int *wptr, unsigned int increment_bytes,
				unsigned int buffer_size_bytes)
{
	unsigned int temp = *wptr + increment_bytes / sizeof(uint32_t);

	WARN((temp * sizeof(uint32_t)) > buffer_size_bytes,
	     "Runlist IB overflow");
	*wptr = temp;
}

<<<<<<< HEAD
=======
static unsigned int build_pm4_header(unsigned int opcode, size_t packet_size)
{
	union PM4_MES_TYPE_3_HEADER header;

	header.u32All = 0;
	header.opcode = opcode;
	header.count = packet_size/sizeof(uint32_t) - 2;
	header.type = PM4_TYPE_3;

	return header.u32All;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static void pm_calc_rlib_size(struct packet_manager *pm,
				unsigned int *rlib_size,
				bool *over_subscription)
{
<<<<<<< HEAD
	unsigned int process_count, queue_count, compute_queue_count;
	unsigned int map_queue_size;
	unsigned int max_proc_per_quantum = 1;
	struct kfd_dev *dev = pm->dqm->dev;

	process_count = pm->dqm->processes_count;
	queue_count = pm->dqm->queue_count;
	compute_queue_count = queue_count - pm->dqm->sdma_queue_count;

	/* check if there is over subscription
	 * Note: the arbitration between the number of VMIDs and
	 * hws_max_conc_proc has been done in
	 * kgd2kfd_device_init().
	 */
	*over_subscription = false;

	if (dev->max_proc_per_quantum > 1)
		max_proc_per_quantum = dev->max_proc_per_quantum;

	if ((process_count > max_proc_per_quantum) ||
	    compute_queue_count > get_queues_num(pm->dqm)) {
=======
	unsigned int process_count, queue_count;
	unsigned int map_queue_size;

	process_count = pm->dqm->processes_count;
	queue_count = pm->dqm->queue_count;

	/* check if there is over subscription*/
	*over_subscription = false;
	if ((process_count > 1) || queue_count > get_queues_num(pm->dqm)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		*over_subscription = true;
		pr_debug("Over subscribed runlist\n");
	}

<<<<<<< HEAD
	map_queue_size = pm->pmf->map_queues_size;
	/* calculate run list ib allocation size */
	*rlib_size = process_count * pm->pmf->map_process_size +
=======
	map_queue_size = sizeof(struct pm4_mes_map_queues);
	/* calculate run list ib allocation size */
	*rlib_size = process_count * sizeof(struct pm4_mes_map_process) +
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		     queue_count * map_queue_size;

	/*
	 * Increase the allocation size in case we need a chained run list
	 * when over subscription
	 */
	if (*over_subscription)
<<<<<<< HEAD
		*rlib_size += pm->pmf->runlist_size;
=======
		*rlib_size += sizeof(struct pm4_mes_runlist);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	pr_debug("runlist ib size %d\n", *rlib_size);
}

static int pm_allocate_runlist_ib(struct packet_manager *pm,
				unsigned int **rl_buffer,
				uint64_t *rl_gpu_buffer,
				unsigned int *rl_buffer_size,
				bool *is_over_subscription)
{
	int retval;

	if (WARN_ON(pm->allocated))
		return -EINVAL;

	pm_calc_rlib_size(pm, rl_buffer_size, is_over_subscription);

<<<<<<< HEAD
	mutex_lock(&pm->lock);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	retval = kfd_gtt_sa_allocate(pm->dqm->dev, *rl_buffer_size,
					&pm->ib_buffer_obj);

	if (retval) {
		pr_err("Failed to allocate runlist IB\n");
<<<<<<< HEAD
		goto out;
=======
		return retval;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	*(void **)rl_buffer = pm->ib_buffer_obj->cpu_ptr;
	*rl_gpu_buffer = pm->ib_buffer_obj->gpu_addr;

	memset(*rl_buffer, 0, *rl_buffer_size);
	pm->allocated = true;
<<<<<<< HEAD

out:
	mutex_unlock(&pm->lock);
	return retval;
}

=======
	return retval;
}

static int pm_create_runlist(struct packet_manager *pm, uint32_t *buffer,
			uint64_t ib, size_t ib_size_in_dwords, bool chain)
{
	struct pm4_mes_runlist *packet;

	if (WARN_ON(!ib))
		return -EFAULT;

	packet = (struct pm4_mes_runlist *)buffer;

	memset(buffer, 0, sizeof(struct pm4_mes_runlist));
	packet->header.u32All = build_pm4_header(IT_RUN_LIST,
						sizeof(struct pm4_mes_runlist));

	packet->bitfields4.ib_size = ib_size_in_dwords;
	packet->bitfields4.chain = chain ? 1 : 0;
	packet->bitfields4.offload_polling = 0;
	packet->bitfields4.valid = 1;
	packet->ordinal2 = lower_32_bits(ib);
	packet->bitfields3.ib_base_hi = upper_32_bits(ib);

	return 0;
}

static int pm_create_map_process(struct packet_manager *pm, uint32_t *buffer,
				struct qcm_process_device *qpd)
{
	struct pm4_mes_map_process *packet;
	struct queue *cur;
	uint32_t num_queues;

	packet = (struct pm4_mes_map_process *)buffer;

	memset(buffer, 0, sizeof(struct pm4_mes_map_process));

	packet->header.u32All = build_pm4_header(IT_MAP_PROCESS,
					sizeof(struct pm4_mes_map_process));
	packet->bitfields2.diq_enable = (qpd->is_debug) ? 1 : 0;
	packet->bitfields2.process_quantum = 1;
	packet->bitfields2.pasid = qpd->pqm->process->pasid;
	packet->bitfields3.page_table_base = qpd->page_table_base;
	packet->bitfields10.gds_size = qpd->gds_size;
	packet->bitfields10.num_gws = qpd->num_gws;
	packet->bitfields10.num_oac = qpd->num_oac;
	num_queues = 0;
	list_for_each_entry(cur, &qpd->queues_list, list)
		num_queues++;
	packet->bitfields10.num_queues = (qpd->is_debug) ? 0 : num_queues;

	packet->sh_mem_config = qpd->sh_mem_config;
	packet->sh_mem_bases = qpd->sh_mem_bases;
	packet->sh_mem_ape1_base = qpd->sh_mem_ape1_base;
	packet->sh_mem_ape1_limit = qpd->sh_mem_ape1_limit;

	packet->sh_hidden_private_base_vmid = qpd->sh_hidden_private_base;

	packet->gds_addr_lo = lower_32_bits(qpd->gds_context_area);
	packet->gds_addr_hi = upper_32_bits(qpd->gds_context_area);

	return 0;
}

static int pm_create_map_queue(struct packet_manager *pm, uint32_t *buffer,
		struct queue *q, bool is_static)
{
	struct pm4_mes_map_queues *packet;
	bool use_static = is_static;

	packet = (struct pm4_mes_map_queues *)buffer;
	memset(buffer, 0, sizeof(struct pm4_mes_map_queues));

	packet->header.u32All = build_pm4_header(IT_MAP_QUEUES,
						sizeof(struct pm4_mes_map_queues));
	packet->bitfields2.alloc_format =
		alloc_format__mes_map_queues__one_per_pipe_vi;
	packet->bitfields2.num_queues = 1;
	packet->bitfields2.queue_sel =
		queue_sel__mes_map_queues__map_to_hws_determined_queue_slots_vi;

	packet->bitfields2.engine_sel =
		engine_sel__mes_map_queues__compute_vi;
	packet->bitfields2.queue_type =
		queue_type__mes_map_queues__normal_compute_vi;

	switch (q->properties.type) {
	case KFD_QUEUE_TYPE_COMPUTE:
		if (use_static)
			packet->bitfields2.queue_type =
		queue_type__mes_map_queues__normal_latency_static_queue_vi;
		break;
	case KFD_QUEUE_TYPE_DIQ:
		packet->bitfields2.queue_type =
			queue_type__mes_map_queues__debug_interface_queue_vi;
		break;
	case KFD_QUEUE_TYPE_SDMA:
		packet->bitfields2.engine_sel =
				engine_sel__mes_map_queues__sdma0_vi;
		use_static = false; /* no static queues under SDMA */
		break;
	default:
		WARN(1, "queue type %d", q->properties.type);
		return -EINVAL;
	}
	packet->bitfields3.doorbell_offset =
			q->properties.doorbell_off;

	packet->mqd_addr_lo =
			lower_32_bits(q->gart_mqd_addr);

	packet->mqd_addr_hi =
			upper_32_bits(q->gart_mqd_addr);

	packet->wptr_addr_lo =
			lower_32_bits((uint64_t)q->properties.write_ptr);

	packet->wptr_addr_hi =
			upper_32_bits((uint64_t)q->properties.write_ptr);

	return 0;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int pm_create_runlist_ib(struct packet_manager *pm,
				struct list_head *queues,
				uint64_t *rl_gpu_addr,
				size_t *rl_size_bytes)
{
	unsigned int alloc_size_bytes;
	unsigned int *rl_buffer, rl_wptr, i;
	int retval, proccesses_mapped;
	struct device_process_node *cur;
	struct qcm_process_device *qpd;
	struct queue *q;
	struct kernel_queue *kq;
	bool is_over_subscription;

	rl_wptr = retval = proccesses_mapped = 0;

	retval = pm_allocate_runlist_ib(pm, &rl_buffer, rl_gpu_addr,
				&alloc_size_bytes, &is_over_subscription);
	if (retval)
		return retval;

	*rl_size_bytes = alloc_size_bytes;
<<<<<<< HEAD
	pm->ib_size_bytes = alloc_size_bytes;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	pr_debug("Building runlist ib process count: %d queues count %d\n",
		pm->dqm->processes_count, pm->dqm->queue_count);

	/* build the run list ib packet */
	list_for_each_entry(cur, queues, list) {
		qpd = cur->qpd;
		/* build map process packet */
		if (proccesses_mapped >= pm->dqm->processes_count) {
			pr_debug("Not enough space left in runlist IB\n");
			pm_release_ib(pm);
			return -ENOMEM;
		}

<<<<<<< HEAD
		retval = pm->pmf->map_process(pm, &rl_buffer[rl_wptr], qpd);
=======
		retval = pm_create_map_process(pm, &rl_buffer[rl_wptr], qpd);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (retval)
			return retval;

		proccesses_mapped++;
<<<<<<< HEAD
		inc_wptr(&rl_wptr, pm->pmf->map_process_size,
=======
		inc_wptr(&rl_wptr, sizeof(struct pm4_mes_map_process),
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				alloc_size_bytes);

		list_for_each_entry(kq, &qpd->priv_queue_list, list) {
			if (!kq->queue->properties.is_active)
				continue;

			pr_debug("static_queue, mapping kernel q %d, is debug status %d\n",
				kq->queue->queue, qpd->is_debug);

<<<<<<< HEAD
			retval = pm->pmf->map_queues(pm,
=======
			retval = pm_create_map_queue(pm,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
						&rl_buffer[rl_wptr],
						kq->queue,
						qpd->is_debug);
			if (retval)
				return retval;

			inc_wptr(&rl_wptr,
<<<<<<< HEAD
				pm->pmf->map_queues_size,
=======
				sizeof(struct pm4_mes_map_queues),
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				alloc_size_bytes);
		}

		list_for_each_entry(q, &qpd->queues_list, list) {
			if (!q->properties.is_active)
				continue;

			pr_debug("static_queue, mapping user queue %d, is debug status %d\n",
				q->queue, qpd->is_debug);

<<<<<<< HEAD
			retval = pm->pmf->map_queues(pm,
=======
			retval = pm_create_map_queue(pm,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
						&rl_buffer[rl_wptr],
						q,
						qpd->is_debug);

			if (retval)
				return retval;

			inc_wptr(&rl_wptr,
<<<<<<< HEAD
				pm->pmf->map_queues_size,
=======
				sizeof(struct pm4_mes_map_queues),
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				alloc_size_bytes);
		}
	}

	pr_debug("Finished map process and queues to runlist\n");

	if (is_over_subscription)
<<<<<<< HEAD
		retval = pm->pmf->runlist(pm, &rl_buffer[rl_wptr],
=======
		retval = pm_create_runlist(pm, &rl_buffer[rl_wptr],
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					*rl_gpu_addr,
					alloc_size_bytes / sizeof(uint32_t),
					true);

	for (i = 0; i < alloc_size_bytes / sizeof(uint32_t); i++)
		pr_debug("0x%2X ", rl_buffer[i]);
	pr_debug("\n");

	return retval;
}

int pm_init(struct packet_manager *pm, struct device_queue_manager *dqm)
{
<<<<<<< HEAD
	switch (dqm->dev->device_info->asic_family) {
	case CHIP_KAVERI:
	case CHIP_HAWAII:
		/* PM4 packet structures on CIK are the same as on VI */
	case CHIP_CARRIZO:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
		pm->pmf = &kfd_vi_pm_funcs;
		break;
	case CHIP_VEGA10:
	case CHIP_RAVEN:
		pm->pmf = &kfd_v9_pm_funcs;
		break;
	default:
		WARN(1, "Unexpected ASIC family %u",
		     dqm->dev->device_info->asic_family);
		return -EINVAL;
	}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	pm->dqm = dqm;
	mutex_init(&pm->lock);
	pm->priv_queue = kernel_queue_init(dqm->dev, KFD_QUEUE_TYPE_HIQ);
	if (!pm->priv_queue) {
		mutex_destroy(&pm->lock);
		return -ENOMEM;
	}
	pm->allocated = false;

	return 0;
}

void pm_uninit(struct packet_manager *pm)
{
	mutex_destroy(&pm->lock);
	kernel_queue_uninit(pm->priv_queue);
}

int pm_send_set_resources(struct packet_manager *pm,
				struct scheduling_resources *res)
{
<<<<<<< HEAD
	uint32_t *buffer, size;
	int retval = 0;

	size = pm->pmf->set_resources_size;
	mutex_lock(&pm->lock);
	pm->priv_queue->ops.acquire_packet_buffer(pm->priv_queue,
					size / sizeof(uint32_t),
					(unsigned int **)&buffer);
	if (!buffer) {
=======
	struct pm4_mes_set_resources *packet;
	int retval = 0;

	mutex_lock(&pm->lock);
	pm->priv_queue->ops.acquire_packet_buffer(pm->priv_queue,
					sizeof(*packet) / sizeof(uint32_t),
					(unsigned int **)&packet);
	if (!packet) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		pr_err("Failed to allocate buffer on kernel queue\n");
		retval = -ENOMEM;
		goto out;
	}

<<<<<<< HEAD
	retval = pm->pmf->set_resources(pm, buffer, res);
	if (!retval)
		pm->priv_queue->ops.submit_packet(pm->priv_queue);
	else
		pm->priv_queue->ops.rollback_packet(pm->priv_queue);
=======
	memset(packet, 0, sizeof(struct pm4_mes_set_resources));
	packet->header.u32All = build_pm4_header(IT_SET_RESOURCES,
					sizeof(struct pm4_mes_set_resources));

	packet->bitfields2.queue_type =
			queue_type__mes_set_resources__hsa_interface_queue_hiq;
	packet->bitfields2.vmid_mask = res->vmid_mask;
	packet->bitfields2.unmap_latency = KFD_UNMAP_LATENCY;
	packet->bitfields7.oac_mask = res->oac_mask;
	packet->bitfields8.gds_heap_base = res->gds_heap_base;
	packet->bitfields8.gds_heap_size = res->gds_heap_size;

	packet->gws_mask_lo = lower_32_bits(res->gws_mask);
	packet->gws_mask_hi = upper_32_bits(res->gws_mask);

	packet->queue_mask_lo = lower_32_bits(res->queue_mask);
	packet->queue_mask_hi = upper_32_bits(res->queue_mask);

	pm->priv_queue->ops.submit_packet(pm->priv_queue);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

out:
	mutex_unlock(&pm->lock);

	return retval;
}

int pm_send_runlist(struct packet_manager *pm, struct list_head *dqm_queues)
{
	uint64_t rl_gpu_ib_addr;
	uint32_t *rl_buffer;
	size_t rl_ib_size, packet_size_dwords;
	int retval;

	retval = pm_create_runlist_ib(pm, dqm_queues, &rl_gpu_ib_addr,
					&rl_ib_size);
	if (retval)
		goto fail_create_runlist_ib;

	pr_debug("runlist IB address: 0x%llX\n", rl_gpu_ib_addr);

<<<<<<< HEAD
	packet_size_dwords = pm->pmf->runlist_size / sizeof(uint32_t);
=======
	packet_size_dwords = sizeof(struct pm4_mes_runlist) / sizeof(uint32_t);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mutex_lock(&pm->lock);

	retval = pm->priv_queue->ops.acquire_packet_buffer(pm->priv_queue,
					packet_size_dwords, &rl_buffer);
	if (retval)
		goto fail_acquire_packet_buffer;

<<<<<<< HEAD
	retval = pm->pmf->runlist(pm, rl_buffer, rl_gpu_ib_addr,
=======
	retval = pm_create_runlist(pm, rl_buffer, rl_gpu_ib_addr,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					rl_ib_size / sizeof(uint32_t), false);
	if (retval)
		goto fail_create_runlist;

	pm->priv_queue->ops.submit_packet(pm->priv_queue);

	mutex_unlock(&pm->lock);

	return retval;

fail_create_runlist:
	pm->priv_queue->ops.rollback_packet(pm->priv_queue);
fail_acquire_packet_buffer:
	mutex_unlock(&pm->lock);
fail_create_runlist_ib:
	pm_release_ib(pm);
	return retval;
}

int pm_send_query_status(struct packet_manager *pm, uint64_t fence_address,
			uint32_t fence_value)
{
<<<<<<< HEAD
	uint32_t *buffer, size;
	int retval = 0;
=======
	int retval;
	struct pm4_mes_query_status *packet;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (WARN_ON(!fence_address))
		return -EFAULT;

<<<<<<< HEAD
	size = pm->pmf->query_status_size;
	mutex_lock(&pm->lock);
	pm->priv_queue->ops.acquire_packet_buffer(pm->priv_queue,
			size / sizeof(uint32_t), (unsigned int **)&buffer);
	if (!buffer) {
		pr_err("Failed to allocate buffer on kernel queue\n");
		retval = -ENOMEM;
		goto out;
	}

	retval = pm->pmf->query_status(pm, buffer, fence_address, fence_value);
	if (!retval)
		pm->priv_queue->ops.submit_packet(pm->priv_queue);
	else
		pm->priv_queue->ops.rollback_packet(pm->priv_queue);

out:
=======
	mutex_lock(&pm->lock);
	retval = pm->priv_queue->ops.acquire_packet_buffer(
			pm->priv_queue,
			sizeof(struct pm4_mes_query_status) / sizeof(uint32_t),
			(unsigned int **)&packet);
	if (retval)
		goto fail_acquire_packet_buffer;

	packet->header.u32All = build_pm4_header(IT_QUERY_STATUS,
					sizeof(struct pm4_mes_query_status));

	packet->bitfields2.context_id = 0;
	packet->bitfields2.interrupt_sel =
			interrupt_sel__mes_query_status__completion_status;
	packet->bitfields2.command =
			command__mes_query_status__fence_only_after_write_ack;

	packet->addr_hi = upper_32_bits((uint64_t)fence_address);
	packet->addr_lo = lower_32_bits((uint64_t)fence_address);
	packet->data_hi = upper_32_bits((uint64_t)fence_value);
	packet->data_lo = lower_32_bits((uint64_t)fence_value);

	pm->priv_queue->ops.submit_packet(pm->priv_queue);

fail_acquire_packet_buffer:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mutex_unlock(&pm->lock);
	return retval;
}

int pm_send_unmap_queue(struct packet_manager *pm, enum kfd_queue_type type,
<<<<<<< HEAD
			enum kfd_unmap_queues_filter filter,
			uint32_t filter_param, bool reset,
			unsigned int sdma_engine)
{
	uint32_t *buffer, size;
	int retval = 0;

	size = pm->pmf->unmap_queues_size;
	mutex_lock(&pm->lock);
	pm->priv_queue->ops.acquire_packet_buffer(pm->priv_queue,
			size / sizeof(uint32_t), (unsigned int **)&buffer);
	if (!buffer) {
		pr_err("Failed to allocate buffer on kernel queue\n");
		retval = -ENOMEM;
		goto out;
	}

	retval = pm->pmf->unmap_queues(pm, buffer, type, filter, filter_param,
				       reset, sdma_engine);
	if (!retval)
		pm->priv_queue->ops.submit_packet(pm->priv_queue);
	else
		pm->priv_queue->ops.rollback_packet(pm->priv_queue);

out:
=======
			enum kfd_preempt_type_filter mode,
			uint32_t filter_param, bool reset,
			unsigned int sdma_engine)
{
	int retval;
	uint32_t *buffer;
	struct pm4_mes_unmap_queues *packet;

	mutex_lock(&pm->lock);
	retval = pm->priv_queue->ops.acquire_packet_buffer(
			pm->priv_queue,
			sizeof(struct pm4_mes_unmap_queues) / sizeof(uint32_t),
			&buffer);
	if (retval)
		goto err_acquire_packet_buffer;

	packet = (struct pm4_mes_unmap_queues *)buffer;
	memset(buffer, 0, sizeof(struct pm4_mes_unmap_queues));
	pr_debug("static_queue: unmapping queues: mode is %d , reset is %d , type is %d\n",
		mode, reset, type);
	packet->header.u32All = build_pm4_header(IT_UNMAP_QUEUES,
					sizeof(struct pm4_mes_unmap_queues));
	switch (type) {
	case KFD_QUEUE_TYPE_COMPUTE:
	case KFD_QUEUE_TYPE_DIQ:
		packet->bitfields2.engine_sel =
			engine_sel__mes_unmap_queues__compute;
		break;
	case KFD_QUEUE_TYPE_SDMA:
		packet->bitfields2.engine_sel =
			engine_sel__mes_unmap_queues__sdma0 + sdma_engine;
		break;
	default:
		WARN(1, "queue type %d", type);
		retval = -EINVAL;
		goto err_invalid;
	}

	if (reset)
		packet->bitfields2.action =
				action__mes_unmap_queues__reset_queues;
	else
		packet->bitfields2.action =
				action__mes_unmap_queues__preempt_queues;

	switch (mode) {
	case KFD_PREEMPT_TYPE_FILTER_SINGLE_QUEUE:
		packet->bitfields2.queue_sel =
				queue_sel__mes_unmap_queues__perform_request_on_specified_queues;
		packet->bitfields2.num_queues = 1;
		packet->bitfields3b.doorbell_offset0 = filter_param;
		break;
	case KFD_PREEMPT_TYPE_FILTER_BY_PASID:
		packet->bitfields2.queue_sel =
				queue_sel__mes_unmap_queues__perform_request_on_pasid_queues;
		packet->bitfields3a.pasid = filter_param;
		break;
	case KFD_PREEMPT_TYPE_FILTER_ALL_QUEUES:
		packet->bitfields2.queue_sel =
				queue_sel__mes_unmap_queues__unmap_all_queues;
		break;
	case KFD_PREEMPT_TYPE_FILTER_DYNAMIC_QUEUES:
		/* in this case, we do not preempt static queues */
		packet->bitfields2.queue_sel =
				queue_sel__mes_unmap_queues__unmap_all_non_static_queues;
		break;
	default:
		WARN(1, "filter %d", mode);
		retval = -EINVAL;
		goto err_invalid;
	}

	pm->priv_queue->ops.submit_packet(pm->priv_queue);

	mutex_unlock(&pm->lock);
	return 0;

err_invalid:
	pm->priv_queue->ops.rollback_packet(pm->priv_queue);
err_acquire_packet_buffer:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mutex_unlock(&pm->lock);
	return retval;
}

void pm_release_ib(struct packet_manager *pm)
{
	mutex_lock(&pm->lock);
	if (pm->allocated) {
		kfd_gtt_sa_free(pm->dqm->dev, pm->ib_buffer_obj);
		pm->allocated = false;
	}
	mutex_unlock(&pm->lock);
}
<<<<<<< HEAD

#if defined(CONFIG_DEBUG_FS)

int pm_debugfs_runlist(struct seq_file *m, void *data)
{
	struct packet_manager *pm = data;

	mutex_lock(&pm->lock);

	if (!pm->allocated) {
		seq_puts(m, "  No active runlist\n");
		goto out;
	}

	seq_hex_dump(m, "  ", DUMP_PREFIX_OFFSET, 32, 4,
		     pm->ib_buffer_obj->cpu_ptr, pm->ib_size_bytes, false);

out:
	mutex_unlock(&pm->lock);
	return 0;
}

int pm_debugfs_hang_hws(struct packet_manager *pm)
{
	uint32_t *buffer, size;
	int r = 0;

	size = pm->pmf->query_status_size;
	mutex_lock(&pm->lock);
	pm->priv_queue->ops.acquire_packet_buffer(pm->priv_queue,
			size / sizeof(uint32_t), (unsigned int **)&buffer);
	if (!buffer) {
		pr_err("Failed to allocate buffer on kernel queue\n");
		r = -ENOMEM;
		goto out;
	}
	memset(buffer, 0x55, size);
	pm->priv_queue->ops.submit_packet(pm->priv_queue);

	pr_info("Submitting %x %x %x %x %x %x %x to HIQ to hang the HWS.",
		buffer[0], buffer[1], buffer[2], buffer[3],
		buffer[4], buffer[5], buffer[6]);
out:
	mutex_unlock(&pm->lock);
	return r;
}


#endif
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
