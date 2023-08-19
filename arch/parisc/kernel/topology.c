/*
<<<<<<< HEAD
 * arch/parisc/kernel/topology.c
 *
 * Copyright (C) 2017 Helge Deller <deller@gmx.de>
 *
 * based on arch/arm/kernel/topology.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <linux/percpu.h>
#include <linux/sched.h>
#include <linux/sched/topology.h>

#include <asm/topology.h>

 /*
  * cpu topology table
  */
struct cputopo_parisc cpu_topology[NR_CPUS] __read_mostly;
EXPORT_SYMBOL_GPL(cpu_topology);

const struct cpumask *cpu_coregroup_mask(int cpu)
{
	return &cpu_topology[cpu].core_sibling;
}

static void update_siblings_masks(unsigned int cpuid)
{
	struct cputopo_parisc *cpu_topo, *cpuid_topo = &cpu_topology[cpuid];
	int cpu;

	/* update core and thread sibling masks */
	for_each_possible_cpu(cpu) {
		cpu_topo = &cpu_topology[cpu];

		if (cpuid_topo->socket_id != cpu_topo->socket_id)
			continue;

		cpumask_set_cpu(cpuid, &cpu_topo->core_sibling);
		if (cpu != cpuid)
			cpumask_set_cpu(cpu, &cpuid_topo->core_sibling);

		if (cpuid_topo->core_id != cpu_topo->core_id)
			continue;

		cpumask_set_cpu(cpuid, &cpu_topo->thread_sibling);
		if (cpu != cpuid)
			cpumask_set_cpu(cpu, &cpuid_topo->thread_sibling);
	}
	smp_wmb();
}

static int dualcores_found __initdata;

/*
 * store_cpu_topology is called at boot when only one cpu is running
 * and with the mutex cpu_hotplug.lock locked, when several cpus have booted,
 * which prevents simultaneous write access to cpu_topology array
 */
void __init store_cpu_topology(unsigned int cpuid)
{
	struct cputopo_parisc *cpuid_topo = &cpu_topology[cpuid];
	struct cpuinfo_parisc *p;
	int max_socket = -1;
	unsigned long cpu;

	/* If the cpu topology has been already set, just return */
	if (cpuid_topo->core_id != -1)
		return;

	/* create cpu topology mapping */
	cpuid_topo->thread_id = -1;
	cpuid_topo->core_id = 0;

	p = &per_cpu(cpu_data, cpuid);
	for_each_online_cpu(cpu) {
		const struct cpuinfo_parisc *cpuinfo = &per_cpu(cpu_data, cpu);

		if (cpu == cpuid) /* ignore current cpu */
			continue;

		if (cpuinfo->cpu_loc == p->cpu_loc) {
			cpuid_topo->core_id = cpu_topology[cpu].core_id;
			if (p->cpu_loc) {
				cpuid_topo->core_id++;
				cpuid_topo->socket_id = cpu_topology[cpu].socket_id;
				dualcores_found = 1;
				continue;
			}
		}

		if (cpuid_topo->socket_id == -1)
			max_socket = max(max_socket, cpu_topology[cpu].socket_id);
	}

	if (cpuid_topo->socket_id == -1)
		cpuid_topo->socket_id = max_socket + 1;

	update_siblings_masks(cpuid);

	pr_info("CPU%u: thread %d, cpu %d, socket %d\n",
		cpuid, cpu_topology[cpuid].thread_id,
		cpu_topology[cpuid].core_id,
		cpu_topology[cpuid].socket_id);
}

static struct sched_domain_topology_level parisc_mc_topology[] = {
#ifdef CONFIG_SCHED_MC
	{ cpu_coregroup_mask, cpu_core_flags, SD_INIT_NAME(MC) },
#endif

	{ cpu_cpu_mask, SD_INIT_NAME(DIE) },
	{ NULL, },
};

/*
 * init_cpu_topology is called at boot when only one cpu is running
 * which prevent simultaneous write access to cpu_topology array
 */
void __init init_cpu_topology(void)
{
	unsigned int cpu;

	/* init core mask and capacity */
	for_each_possible_cpu(cpu) {
		struct cputopo_parisc *cpu_topo = &(cpu_topology[cpu]);

		cpu_topo->thread_id = -1;
		cpu_topo->core_id =  -1;
		cpu_topo->socket_id = -1;
		cpumask_clear(&cpu_topo->core_sibling);
		cpumask_clear(&cpu_topo->thread_sibling);
	}
	smp_wmb();

	/* Set scheduler topology descriptor */
	if (dualcores_found)
		set_sched_topology(parisc_mc_topology);
}
=======
 * arch/parisc/kernel/topology.c - Populate sysfs with topology information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/init.h>
#include <linux/smp.h>
#include <linux/cpu.h>
#include <linux/cache.h>

static DEFINE_PER_CPU(struct cpu, cpu_devices);

static int __init topology_init(void)
{
	int num;

	for_each_present_cpu(num) {
		register_cpu(&per_cpu(cpu_devices, num), num);
	}
	return 0;
}

subsys_initcall(topology_init);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
