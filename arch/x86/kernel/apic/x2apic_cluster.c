// SPDX-License-Identifier: GPL-2.0
#include <linux/threads.h>
#include <linux/cpumask.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/ctype.h>
#include <linux/dmar.h>
#include <linux/irq.h>
#include <linux/cpu.h>

#include <asm/smp.h>
<<<<<<< HEAD
#include "x2apic.h"

struct cluster_mask {
	unsigned int	clusterid;
	int		node;
	struct cpumask	mask;
};

static DEFINE_PER_CPU(u32, x86_cpu_to_logical_apicid);
static DEFINE_PER_CPU(cpumask_var_t, ipi_mask);
static DEFINE_PER_CPU(struct cluster_mask *, cluster_masks);
static struct cluster_mask *cluster_hotplug_mask;
=======
#include <asm/x2apic.h>

static DEFINE_PER_CPU(u32, x86_cpu_to_logical_apicid);
static DEFINE_PER_CPU(cpumask_var_t, cpus_in_cluster);
static DEFINE_PER_CPU(cpumask_var_t, ipi_mask);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static int x2apic_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
{
	return x2apic_enabled();
}

<<<<<<< HEAD
=======
static inline u32 x2apic_cluster(int cpu)
{
	return per_cpu(x86_cpu_to_logical_apicid, cpu) >> 16;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static void x2apic_send_IPI(int cpu, int vector)
{
	u32 dest = per_cpu(x86_cpu_to_logical_apicid, cpu);

	x2apic_wrmsr_fence();
	__x2apic_send_IPI_dest(dest, vector, APIC_DEST_LOGICAL);
}

static void
__x2apic_send_IPI_mask(const struct cpumask *mask, int vector, int apic_dest)
{
<<<<<<< HEAD
	unsigned int cpu, clustercpu;
	struct cpumask *tmpmsk;
=======
	struct cpumask *cpus_in_cluster_ptr;
	struct cpumask *ipi_mask_ptr;
	unsigned int cpu, this_cpu;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	unsigned long flags;
	u32 dest;

	x2apic_wrmsr_fence();
<<<<<<< HEAD
	local_irq_save(flags);

	tmpmsk = this_cpu_cpumask_var_ptr(ipi_mask);
	cpumask_copy(tmpmsk, mask);
	/* If IPI should not be sent to self, clear current CPU */
	if (apic_dest != APIC_DEST_ALLINC)
		cpumask_clear_cpu(smp_processor_id(), tmpmsk);

	/* Collapse cpus in a cluster so a single IPI per cluster is sent */
	for_each_cpu(cpu, tmpmsk) {
		struct cluster_mask *cmsk = per_cpu(cluster_masks, cpu);

		dest = 0;
		for_each_cpu_and(clustercpu, tmpmsk, &cmsk->mask)
			dest |= per_cpu(x86_cpu_to_logical_apicid, clustercpu);
=======

	local_irq_save(flags);

	this_cpu = smp_processor_id();

	/*
	 * We are to modify mask, so we need an own copy
	 * and be sure it's manipulated with irq off.
	 */
	ipi_mask_ptr = this_cpu_cpumask_var_ptr(ipi_mask);
	cpumask_copy(ipi_mask_ptr, mask);

	/*
	 * The idea is to send one IPI per cluster.
	 */
	for_each_cpu(cpu, ipi_mask_ptr) {
		unsigned long i;

		cpus_in_cluster_ptr = per_cpu(cpus_in_cluster, cpu);
		dest = 0;

		/* Collect cpus in cluster. */
		for_each_cpu_and(i, ipi_mask_ptr, cpus_in_cluster_ptr) {
			if (apic_dest == APIC_DEST_ALLINC || i != this_cpu)
				dest |= per_cpu(x86_cpu_to_logical_apicid, i);
		}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		if (!dest)
			continue;

		__x2apic_send_IPI_dest(dest, vector, apic->dest_logical);
<<<<<<< HEAD
		/* Remove cluster CPUs from tmpmask */
		cpumask_andnot(tmpmsk, tmpmsk, &cmsk->mask);
=======
		/*
		 * Cluster sibling cpus should be discared now so
		 * we would not send IPI them second time.
		 */
		cpumask_andnot(ipi_mask_ptr, ipi_mask_ptr, cpus_in_cluster_ptr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	local_irq_restore(flags);
}

static void x2apic_send_IPI_mask(const struct cpumask *mask, int vector)
{
	__x2apic_send_IPI_mask(mask, vector, APIC_DEST_ALLINC);
}

static void
x2apic_send_IPI_mask_allbutself(const struct cpumask *mask, int vector)
{
	__x2apic_send_IPI_mask(mask, vector, APIC_DEST_ALLBUT);
}

static void x2apic_send_IPI_allbutself(int vector)
{
	__x2apic_send_IPI_mask(cpu_online_mask, vector, APIC_DEST_ALLBUT);
}

static void x2apic_send_IPI_all(int vector)
{
	__x2apic_send_IPI_mask(cpu_online_mask, vector, APIC_DEST_ALLINC);
}

<<<<<<< HEAD
static u32 x2apic_calc_apicid(unsigned int cpu)
{
	return per_cpu(x86_cpu_to_logical_apicid, cpu);
=======
static int
x2apic_cpu_mask_to_apicid(const struct cpumask *mask, struct irq_data *irqdata,
			  unsigned int *apicid)
{
	struct cpumask *effmsk = irq_data_get_effective_affinity_mask(irqdata);
	unsigned int cpu;
	u32 dest = 0;
	u16 cluster;

	cpu = cpumask_first(mask);
	if (cpu >= nr_cpu_ids)
		return -EINVAL;

	dest = per_cpu(x86_cpu_to_logical_apicid, cpu);
	cluster = x2apic_cluster(cpu);

	cpumask_clear(effmsk);
	for_each_cpu(cpu, mask) {
		if (cluster != x2apic_cluster(cpu))
			continue;
		dest |= per_cpu(x86_cpu_to_logical_apicid, cpu);
		cpumask_set_cpu(cpu, effmsk);
	}

	*apicid = dest;
	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void init_x2apic_ldr(void)
{
<<<<<<< HEAD
	struct cluster_mask *cmsk = this_cpu_read(cluster_masks);
	u32 cluster, apicid = apic_read(APIC_LDR);
	unsigned int cpu;

	this_cpu_write(x86_cpu_to_logical_apicid, apicid);

	if (cmsk)
		goto update;

	cluster = apicid >> 16;
	for_each_online_cpu(cpu) {
		cmsk = per_cpu(cluster_masks, cpu);
		/* Matching cluster found. Link and update it. */
		if (cmsk && cmsk->clusterid == cluster)
			goto update;
	}
	cmsk = cluster_hotplug_mask;
	cmsk->clusterid = cluster;
	cluster_hotplug_mask = NULL;
update:
	this_cpu_write(cluster_masks, cmsk);
	cpumask_set_cpu(smp_processor_id(), &cmsk->mask);
}

static int alloc_clustermask(unsigned int cpu, int node)
{
	if (per_cpu(cluster_masks, cpu))
		return 0;
	/*
	 * If a hotplug spare mask exists, check whether it's on the right
	 * node. If not, free it and allocate a new one.
	 */
	if (cluster_hotplug_mask) {
		if (cluster_hotplug_mask->node == node)
			return 0;
		kfree(cluster_hotplug_mask);
	}

	cluster_hotplug_mask = kzalloc_node(sizeof(*cluster_hotplug_mask),
					    GFP_KERNEL, node);
	if (!cluster_hotplug_mask)
		return -ENOMEM;
	cluster_hotplug_mask->node = node;
	return 0;
}

static int x2apic_prepare_cpu(unsigned int cpu)
{
	if (alloc_clustermask(cpu, cpu_to_node(cpu)) < 0)
		return -ENOMEM;
	if (!zalloc_cpumask_var(&per_cpu(ipi_mask, cpu), GFP_KERNEL))
		return -ENOMEM;
	return 0;
}

static int x2apic_dead_cpu(unsigned int dead_cpu)
{
	struct cluster_mask *cmsk = per_cpu(cluster_masks, dead_cpu);

	if (cmsk)
		cpumask_clear_cpu(dead_cpu, &cmsk->mask);
	free_cpumask_var(per_cpu(ipi_mask, dead_cpu));
=======
	unsigned int this_cpu = smp_processor_id();
	unsigned int cpu;

	per_cpu(x86_cpu_to_logical_apicid, this_cpu) = apic_read(APIC_LDR);

	cpumask_set_cpu(this_cpu, per_cpu(cpus_in_cluster, this_cpu));
	for_each_online_cpu(cpu) {
		if (x2apic_cluster(this_cpu) != x2apic_cluster(cpu))
			continue;
		cpumask_set_cpu(this_cpu, per_cpu(cpus_in_cluster, cpu));
		cpumask_set_cpu(cpu, per_cpu(cpus_in_cluster, this_cpu));
	}
}

/*
 * At CPU state changes, update the x2apic cluster sibling info.
 */
static int x2apic_prepare_cpu(unsigned int cpu)
{
	if (!zalloc_cpumask_var(&per_cpu(cpus_in_cluster, cpu), GFP_KERNEL))
		return -ENOMEM;

	if (!zalloc_cpumask_var(&per_cpu(ipi_mask, cpu), GFP_KERNEL)) {
		free_cpumask_var(per_cpu(cpus_in_cluster, cpu));
		return -ENOMEM;
	}

	return 0;
}

static int x2apic_dead_cpu(unsigned int this_cpu)
{
	int cpu;

	for_each_online_cpu(cpu) {
		if (x2apic_cluster(this_cpu) != x2apic_cluster(cpu))
			continue;
		cpumask_clear_cpu(this_cpu, per_cpu(cpus_in_cluster, cpu));
		cpumask_clear_cpu(cpu, per_cpu(cpus_in_cluster, this_cpu));
	}
	free_cpumask_var(per_cpu(cpus_in_cluster, this_cpu));
	free_cpumask_var(per_cpu(ipi_mask, this_cpu));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

static int x2apic_cluster_probe(void)
{
<<<<<<< HEAD
	if (!x2apic_mode)
		return 0;

	if (cpuhp_setup_state(CPUHP_X2APIC_PREPARE, "x86/x2apic:prepare",
			      x2apic_prepare_cpu, x2apic_dead_cpu) < 0) {
		pr_err("Failed to register X2APIC_PREPARE\n");
		return 0;
	}
	init_x2apic_ldr();
	return 1;
}

=======
	int cpu = smp_processor_id();
	int ret;

	if (!x2apic_mode)
		return 0;

	ret = cpuhp_setup_state(CPUHP_X2APIC_PREPARE, "x86/x2apic:prepare",
				x2apic_prepare_cpu, x2apic_dead_cpu);
	if (ret < 0) {
		pr_err("Failed to register X2APIC_PREPARE\n");
		return 0;
	}
	cpumask_set_cpu(cpu, per_cpu(cpus_in_cluster, cpu));
	return 1;
}

static const struct cpumask *x2apic_cluster_target_cpus(void)
{
	return cpu_all_mask;
}

/*
 * Each x2apic cluster is an allocation domain.
 */
static void cluster_vector_allocation_domain(int cpu, struct cpumask *retmask,
					     const struct cpumask *mask)
{
	/*
	 * To minimize vector pressure, default case of boot, device bringup
	 * etc will use a single cpu for the interrupt destination.
	 *
	 * On explicit migration requests coming from irqbalance etc,
	 * interrupts will be routed to the x2apic cluster (cluster-id
	 * derived from the first cpu in the mask) members specified
	 * in the mask.
	 */
	if (mask == x2apic_cluster_target_cpus())
		cpumask_copy(retmask, cpumask_of(cpu));
	else
		cpumask_and(retmask, mask, per_cpu(cpus_in_cluster, cpu));
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static struct apic apic_x2apic_cluster __ro_after_init = {

	.name				= "cluster x2apic",
	.probe				= x2apic_cluster_probe,
	.acpi_madt_oem_check		= x2apic_acpi_madt_oem_check,
	.apic_id_valid			= x2apic_apic_id_valid,
	.apic_id_registered		= x2apic_apic_id_registered,

<<<<<<< HEAD
	.irq_delivery_mode		= dest_Fixed,
	.irq_dest_mode			= 1, /* logical */

=======
	.irq_delivery_mode		= dest_LowestPrio,
	.irq_dest_mode			= 1, /* logical */

	.target_cpus			= x2apic_cluster_target_cpus,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.disable_esr			= 0,
	.dest_logical			= APIC_DEST_LOGICAL,
	.check_apicid_used		= NULL,

<<<<<<< HEAD
=======
	.vector_allocation_domain	= cluster_vector_allocation_domain,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.init_apic_ldr			= init_x2apic_ldr,

	.ioapic_phys_id_map		= NULL,
	.setup_apic_routing		= NULL,
	.cpu_present_to_apicid		= default_cpu_present_to_apicid,
	.apicid_to_cpu_present		= NULL,
	.check_phys_apicid_present	= default_check_phys_apicid_present,
	.phys_pkg_id			= x2apic_phys_pkg_id,

	.get_apic_id			= x2apic_get_apic_id,
	.set_apic_id			= x2apic_set_apic_id,

<<<<<<< HEAD
	.calc_dest_apicid		= x2apic_calc_apicid,
=======
	.cpu_mask_to_apicid		= x2apic_cpu_mask_to_apicid,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	.send_IPI			= x2apic_send_IPI,
	.send_IPI_mask			= x2apic_send_IPI_mask,
	.send_IPI_mask_allbutself	= x2apic_send_IPI_mask_allbutself,
	.send_IPI_allbutself		= x2apic_send_IPI_allbutself,
	.send_IPI_all			= x2apic_send_IPI_all,
	.send_IPI_self			= x2apic_send_IPI_self,

	.inquire_remote_apic		= NULL,

	.read				= native_apic_msr_read,
	.write				= native_apic_msr_write,
	.eoi_write			= native_apic_msr_eoi_write,
	.icr_read			= native_x2apic_icr_read,
	.icr_write			= native_x2apic_icr_write,
	.wait_icr_idle			= native_x2apic_wait_icr_idle,
	.safe_wait_icr_idle		= native_safe_x2apic_wait_icr_idle,
};

apic_driver(apic_x2apic_cluster);
