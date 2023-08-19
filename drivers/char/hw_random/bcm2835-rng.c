/**
 * Copyright (c) 2010-2012 Broadcom. All rights reserved.
 * Copyright (c) 2013 Lubomir Rintel
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License ("GPL")
 * version 2, as published by the Free Software Foundation.
 */

#include <linux/hw_random.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/printk.h>
<<<<<<< HEAD
#include <linux/clk.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define RNG_CTRL	0x0
#define RNG_STATUS	0x4
#define RNG_DATA	0x8
#define RNG_INT_MASK	0x10

/* enable rng */
#define RNG_RBGEN	0x1

/* the initial numbers generated are "less random" so will be discarded */
#define RNG_WARMUP_COUNT 0x40000

#define RNG_INT_OFF	0x1

<<<<<<< HEAD
struct bcm2835_rng_priv {
	struct hwrng rng;
	void __iomem *base;
	bool mask_interrupts;
	struct clk *clk;
};

static inline struct bcm2835_rng_priv *to_rng_priv(struct hwrng *rng)
{
	return container_of(rng, struct bcm2835_rng_priv, rng);
}

static inline u32 rng_readl(struct bcm2835_rng_priv *priv, u32 offset)
{
	/* MIPS chips strapped for BE will automagically configure the
	 * peripheral registers for CPU-native byte order.
	 */
	if (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		return __raw_readl(priv->base + offset);
	else
		return readl(priv->base + offset);
}

static inline void rng_writel(struct bcm2835_rng_priv *priv, u32 val,
			      u32 offset)
{
	if (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_writel(val, priv->base + offset);
	else
		writel(val, priv->base + offset);
=======
static void __init nsp_rng_init(void __iomem *base)
{
	u32 val;

	/* mask the interrupt */
	val = readl(base + RNG_INT_MASK);
	val |= RNG_INT_OFF;
	writel(val, base + RNG_INT_MASK);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int bcm2835_rng_read(struct hwrng *rng, void *buf, size_t max,
			       bool wait)
{
<<<<<<< HEAD
	struct bcm2835_rng_priv *priv = to_rng_priv(rng);
	u32 max_words = max / sizeof(u32);
	u32 num_words, count;

	while ((rng_readl(priv, RNG_STATUS) >> 24) == 0) {
=======
	void __iomem *rng_base = (void __iomem *)rng->priv;
	u32 max_words = max / sizeof(u32);
	u32 num_words, count;

	while ((__raw_readl(rng_base + RNG_STATUS) >> 24) == 0) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (!wait)
			return 0;
		cpu_relax();
	}

<<<<<<< HEAD
	num_words = rng_readl(priv, RNG_STATUS) >> 24;
=======
	num_words = readl(rng_base + RNG_STATUS) >> 24;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (num_words > max_words)
		num_words = max_words;

	for (count = 0; count < num_words; count++)
<<<<<<< HEAD
		((u32 *)buf)[count] = rng_readl(priv, RNG_DATA);
=======
		((u32 *)buf)[count] = readl(rng_base + RNG_DATA);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return num_words * sizeof(u32);
}

<<<<<<< HEAD
static int bcm2835_rng_init(struct hwrng *rng)
{
	struct bcm2835_rng_priv *priv = to_rng_priv(rng);
	int ret = 0;
	u32 val;

	if (!IS_ERR(priv->clk)) {
		ret = clk_prepare_enable(priv->clk);
		if (ret)
			return ret;
	}

	if (priv->mask_interrupts) {
		/* mask the interrupt */
		val = rng_readl(priv, RNG_INT_MASK);
		val |= RNG_INT_OFF;
		rng_writel(priv, val, RNG_INT_MASK);
	}

	/* set warm-up count & enable */
	rng_writel(priv, RNG_WARMUP_COUNT, RNG_STATUS);
	rng_writel(priv, RNG_RBGEN, RNG_CTRL);

	return ret;
}

static void bcm2835_rng_cleanup(struct hwrng *rng)
{
	struct bcm2835_rng_priv *priv = to_rng_priv(rng);

	/* disable rng hardware */
	rng_writel(priv, 0, RNG_CTRL);

	if (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);
}

struct bcm2835_rng_of_data {
	bool mask_interrupts;
};

static const struct bcm2835_rng_of_data nsp_rng_of_data = {
	.mask_interrupts = true,
=======
static struct hwrng bcm2835_rng_ops = {
	.name	= "bcm2835",
	.read	= bcm2835_rng_read,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static const struct of_device_id bcm2835_rng_of_match[] = {
	{ .compatible = "brcm,bcm2835-rng"},
<<<<<<< HEAD
	{ .compatible = "brcm,bcm-nsp-rng", .data = &nsp_rng_of_data },
	{ .compatible = "brcm,bcm5301x-rng", .data = &nsp_rng_of_data },
	{ .compatible = "brcm,bcm6368-rng"},
=======
	{ .compatible = "brcm,bcm-nsp-rng", .data = nsp_rng_init},
	{ .compatible = "brcm,bcm5301x-rng", .data = nsp_rng_init},
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	{},
};

static int bcm2835_rng_probe(struct platform_device *pdev)
{
<<<<<<< HEAD
	const struct bcm2835_rng_of_data *of_data;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	const struct of_device_id *rng_id;
	struct bcm2835_rng_priv *priv;
	struct resource *r;
	int err;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	/* map peripheral */
	priv->base = devm_ioremap_resource(dev, r);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	/* Clock is optional on most platforms */
	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk) && PTR_ERR(priv->clk) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	priv->rng.name = pdev->name;
	priv->rng.init = bcm2835_rng_init;
	priv->rng.read = bcm2835_rng_read;
	priv->rng.cleanup = bcm2835_rng_cleanup;

	rng_id = of_match_node(bcm2835_rng_of_match, np);
	if (!rng_id)
		return -EINVAL;

	/* Check for rng init function, execute it */
	of_data = rng_id->data;
	if (of_data)
		priv->mask_interrupts = of_data->mask_interrupts;

	/* register driver */
	err = devm_hwrng_register(dev, &priv->rng);
	if (err)
		dev_err(dev, "hwrng registration failed\n");
	else
=======
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	void (*rng_setup)(void __iomem *base);
	const struct of_device_id *rng_id;
	void __iomem *rng_base;
	int err;

	/* map peripheral */
	rng_base = of_iomap(np, 0);
	if (!rng_base) {
		dev_err(dev, "failed to remap rng regs");
		return -ENODEV;
	}
	bcm2835_rng_ops.priv = (unsigned long)rng_base;

	rng_id = of_match_node(bcm2835_rng_of_match, np);
	if (!rng_id) {
		iounmap(rng_base);
		return -EINVAL;
	}
	/* Check for rng init function, execute it */
	rng_setup = rng_id->data;
	if (rng_setup)
		rng_setup(rng_base);

	/* set warm-up count & enable */
	__raw_writel(RNG_WARMUP_COUNT, rng_base + RNG_STATUS);
	__raw_writel(RNG_RBGEN, rng_base + RNG_CTRL);

	/* register driver */
	err = hwrng_register(&bcm2835_rng_ops);
	if (err) {
		dev_err(dev, "hwrng registration failed\n");
		iounmap(rng_base);
	} else
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		dev_info(dev, "hwrng registered\n");

	return err;
}

<<<<<<< HEAD
MODULE_DEVICE_TABLE(of, bcm2835_rng_of_match);

static struct platform_device_id bcm2835_rng_devtype[] = {
	{ .name = "bcm2835-rng" },
	{ .name = "bcm63xx-rng" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(platform, bcm2835_rng_devtype);
=======
static int bcm2835_rng_remove(struct platform_device *pdev)
{
	void __iomem *rng_base = (void __iomem *)bcm2835_rng_ops.priv;

	/* disable rng hardware */
	__raw_writel(0, rng_base + RNG_CTRL);

	/* unregister driver */
	hwrng_unregister(&bcm2835_rng_ops);
	iounmap(rng_base);

	return 0;
}

MODULE_DEVICE_TABLE(of, bcm2835_rng_of_match);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static struct platform_driver bcm2835_rng_driver = {
	.driver = {
		.name = "bcm2835-rng",
		.of_match_table = bcm2835_rng_of_match,
	},
	.probe		= bcm2835_rng_probe,
<<<<<<< HEAD
	.id_table	= bcm2835_rng_devtype,
=======
	.remove		= bcm2835_rng_remove,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};
module_platform_driver(bcm2835_rng_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("BCM2835 Random Number Generator (RNG) driver");
MODULE_LICENSE("GPL v2");
