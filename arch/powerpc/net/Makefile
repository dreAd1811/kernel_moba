# SPDX-License-Identifier: GPL-2.0
#
# Arch-specific network modules
#
<<<<<<< HEAD
ifdef CONFIG_PPC64
obj-$(CONFIG_BPF_JIT) += bpf_jit_comp64.o
=======
ifeq ($(CONFIG_PPC64),y)
obj-$(CONFIG_BPF_JIT) += bpf_jit_asm64.o bpf_jit_comp64.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
else
obj-$(CONFIG_BPF_JIT) += bpf_jit_asm.o bpf_jit_comp.o
endif
