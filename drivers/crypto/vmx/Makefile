# SPDX-License-Identifier: GPL-2.0
obj-$(CONFIG_CRYPTO_DEV_VMX_ENCRYPT) += vmx-crypto.o
vmx-crypto-objs := vmx.o aesp8-ppc.o ghashp8-ppc.o aes.o aes_cbc.o aes_ctr.o aes_xts.o ghash.o

ifeq ($(CONFIG_CPU_LITTLE_ENDIAN),y)
<<<<<<< HEAD
TARGET := linux-ppc64le
else
TARGET := linux-ppc64
endif

quiet_cmd_perl = PERL $@
      cmd_perl = $(PERL) $(<) $(TARGET) > $(@)
=======
override flavour := linux-ppc64le
else
override flavour := linux-ppc64
endif

quiet_cmd_perl = PERL $@
      cmd_perl = $(PERL) $(<) $(flavour) > $(@)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

targets += aesp8-ppc.S ghashp8-ppc.S

$(obj)/aesp8-ppc.S: $(src)/aesp8-ppc.pl FORCE
	$(call if_changed,perl)
  
$(obj)/ghashp8-ppc.S: $(src)/ghashp8-ppc.pl FORCE
	$(call if_changed,perl)

clean-files := aesp8-ppc.S ghashp8-ppc.S
