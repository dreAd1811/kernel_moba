# SPDX-License-Identifier: GPL-2.0
obj-$(CONFIG_MLX4_CORE)		+= mlx4_core.o

mlx4_core-y :=	alloc.o catas.o cmd.o cq.o eq.o fw.o fw_qos.o icm.o intf.o \
		main.o mcg.o mr.o pd.o port.o profile.o qp.o reset.o sense.o \
<<<<<<< HEAD
		srq.o resource_tracker.o crdump.o
=======
		srq.o resource_tracker.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

obj-$(CONFIG_MLX4_EN)               += mlx4_en.o

mlx4_en-y := 	en_main.o en_tx.o en_rx.o en_ethtool.o en_port.o en_cq.o \
		en_resources.o en_netdev.o en_selftest.o en_clock.o
mlx4_en-$(CONFIG_MLX4_EN_DCB) += en_dcb_nl.o
