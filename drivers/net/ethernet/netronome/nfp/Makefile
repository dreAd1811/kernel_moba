# SPDX-License-Identifier: GPL-2.0
obj-$(CONFIG_NFP)	+= nfp.o

nfp-objs := \
	    nfpcore/nfp6000_pcie.o \
	    nfpcore/nfp_cppcore.o \
	    nfpcore/nfp_cpplib.o \
	    nfpcore/nfp_hwinfo.o \
	    nfpcore/nfp_mip.o \
	    nfpcore/nfp_mutex.o \
	    nfpcore/nfp_nffw.o \
	    nfpcore/nfp_nsp.o \
	    nfpcore/nfp_nsp_cmds.o \
	    nfpcore/nfp_nsp_eth.o \
	    nfpcore/nfp_resource.o \
	    nfpcore/nfp_rtsym.o \
	    nfpcore/nfp_target.o \
<<<<<<< HEAD
	    nfp_asm.o \
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	    nfp_app.o \
	    nfp_app_nic.o \
	    nfp_devlink.o \
	    nfp_hwmon.o \
	    nfp_main.o \
	    nfp_net_common.o \
<<<<<<< HEAD
	    nfp_net_ctrl.o \
	    nfp_net_debugdump.o \
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	    nfp_net_ethtool.o \
	    nfp_net_main.o \
	    nfp_net_repr.o \
	    nfp_net_sriov.o \
	    nfp_netvf_main.o \
	    nfp_port.o \
<<<<<<< HEAD
	    nfp_shared_buf.o \
=======
	    bpf/main.o \
	    bpf/offload.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	    nic/main.o

ifeq ($(CONFIG_NFP_APP_FLOWER),y)
nfp-objs += \
	    flower/action.o \
	    flower/cmsg.o \
<<<<<<< HEAD
	    flower/lag_conf.o \
	    flower/main.o \
	    flower/match.o \
	    flower/metadata.o \
	    flower/offload.o \
	    flower/tunnel_conf.o
=======
	    flower/main.o \
	    flower/match.o \
	    flower/metadata.o \
	    flower/offload.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
endif

ifeq ($(CONFIG_BPF_SYSCALL),y)
nfp-objs += \
<<<<<<< HEAD
	    bpf/cmsg.o \
	    bpf/main.o \
	    bpf/offload.o \
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	    bpf/verifier.o \
	    bpf/jit.o
endif

<<<<<<< HEAD
ifeq ($(CONFIG_NFP_APP_ABM_NIC),y)
nfp-objs += \
	    abm/ctrl.o \
	    abm/main.o
endif

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
nfp-$(CONFIG_NFP_DEBUG) += nfp_net_debugfs.o
