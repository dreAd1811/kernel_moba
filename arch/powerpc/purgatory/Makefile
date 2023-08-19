# SPDX-License-Identifier: GPL-2.0
targets += trampoline.o purgatory.ro kexec-purgatory.c

LDFLAGS_purgatory.ro := -e purgatory_start -r --no-undefined

$(obj)/purgatory.ro: $(obj)/trampoline.o FORCE
		$(call if_changed,ld)

<<<<<<< HEAD
quiet_cmd_bin2c = BIN2C   $@
      cmd_bin2c = $(objtree)/scripts/bin2c kexec_purgatory < $< > $@
=======
CMD_BIN2C = $(objtree)/scripts/basic/bin2c
quiet_cmd_bin2c = BIN2C   $@
      cmd_bin2c = $(CMD_BIN2C) kexec_purgatory < $< > $@
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

$(obj)/kexec-purgatory.c: $(obj)/purgatory.ro FORCE
	$(call if_changed,bin2c)

obj-y	+= kexec-purgatory.o
