/*
 * Copyright (C) 2016 Linaro
 * Viresh Kumar <viresh.kumar@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __CPUFREQ_DT_H__
#define __CPUFREQ_DT_H__

#include <linux/types.h>

<<<<<<< HEAD
struct cpufreq_policy;

struct cpufreq_dt_platform_data {
	bool have_governor_per_policy;

	int (*suspend)(struct cpufreq_policy *policy);
	int (*resume)(struct cpufreq_policy *policy);
=======
struct cpufreq_dt_platform_data {
	bool have_governor_per_policy;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

#endif /* __CPUFREQ_DT_H__ */
