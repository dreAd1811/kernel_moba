# SPDX-License-Identifier: GPL-2.0
#
# Cavium Liquidio ethernet device driver
#
<<<<<<< HEAD

common-objs :=	lio_ethtool.o		\
		lio_core.o		\
		request_manager.o	\
		response_manager.o	\
		octeon_device.o		\
		cn66xx_device.o		\
		cn68xx_device.o		\
		cn23xx_pf_device.o	\
		cn23xx_vf_device.o	\
		octeon_mailbox.o	\
		octeon_mem_ops.o	\
		octeon_droq.o		\
		octeon_nic.o

obj-$(CONFIG_LIQUIDIO) += liquidio.o
liquidio-y := lio_main.o octeon_console.o lio_vf_rep.o $(common-objs)

obj-$(CONFIG_LIQUIDIO_VF) += liquidio_vf.o
liquidio_vf-y := lio_vf_main.o $(common-objs)
=======
obj-$(CONFIG_LIQUIDIO) += liquidio.o

liquidio-$(CONFIG_LIQUIDIO) += lio_ethtool.o \
			lio_core.o         \
			request_manager.o  \
			response_manager.o \
			octeon_device.o    \
			cn66xx_device.o    \
			cn68xx_device.o    \
			cn23xx_pf_device.o \
			cn23xx_vf_device.o \
			octeon_mailbox.o   \
			octeon_mem_ops.o   \
			octeon_droq.o      \
			octeon_nic.o

liquidio-objs := lio_main.o octeon_console.o $(liquidio-y)

obj-$(CONFIG_LIQUIDIO_VF) += liquidio_vf.o

ifeq ($(CONFIG_LIQUIDIO)$(CONFIG_LIQUIDIO_VF), yy)
	liquidio_vf-objs := lio_vf_main.o
else
liquidio_vf-$(CONFIG_LIQUIDIO_VF) += lio_ethtool.o \
			lio_core.o         \
			request_manager.o  \
			response_manager.o \
			octeon_device.o    \
			cn66xx_device.o    \
			cn68xx_device.o    \
			cn23xx_pf_device.o \
			cn23xx_vf_device.o \
			octeon_mailbox.o   \
			octeon_mem_ops.o   \
			octeon_droq.o      \
			octeon_nic.o

liquidio_vf-objs := lio_vf_main.o $(liquidio_vf-y)
endif
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
