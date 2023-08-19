#
# Arch-specific network modules
#
<<<<<<< HEAD

ifeq ($(CONFIG_X86_32),y)
        obj-$(CONFIG_BPF_JIT) += bpf_jit_comp32.o
else
        obj-$(CONFIG_BPF_JIT) += bpf_jit_comp.o
endif
=======
OBJECT_FILES_NON_STANDARD_bpf_jit.o += y

obj-$(CONFIG_BPF_JIT) += bpf_jit.o bpf_jit_comp.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
