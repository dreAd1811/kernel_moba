# SPDX-License-Identifier: GPL-2.0
OBJECT_FILES_NON_STANDARD := y

purgatory-y := purgatory.o stack.o setup-x86_$(BITS).o sha256.o entry64.o string.o

targets += $(purgatory-y)
PURGATORY_OBJS = $(addprefix $(obj)/,$(purgatory-y))

<<<<<<< HEAD
$(obj)/string.o: $(srctree)/arch/x86/boot/compressed/string.c FORCE
	$(call if_changed_rule,cc_o_c)

$(obj)/sha256.o: $(srctree)/lib/sha256.c FORCE
	$(call if_changed_rule,cc_o_c)

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
LDFLAGS_purgatory.ro := -e purgatory_start -r --no-undefined -nostdlib -z nodefaultlib
targets += purgatory.ro

KASAN_SANITIZE	:= n
KCOV_INSTRUMENT := n

<<<<<<< HEAD
# These are adjustments to the compiler flags used for objects that
# make up the standalone purgatory.ro

PURGATORY_CFLAGS_REMOVE := -mcmodel=kernel
PURGATORY_CFLAGS := -mcmodel=large -ffreestanding -fno-zero-initialized-in-bss
PURGATORY_CFLAGS += $(DISABLE_STACKLEAK_PLUGIN)

# Default KBUILD_CFLAGS can have -pg option set when FTRACE is enabled. That
# in turn leaves some undefined symbols like __fentry__ in purgatory and not
# sure how to relocate those.
ifdef CONFIG_FUNCTION_TRACER
PURGATORY_CFLAGS_REMOVE		+= $(CC_FLAGS_FTRACE)
endif

ifdef CONFIG_STACKPROTECTOR
PURGATORY_CFLAGS_REMOVE		+= -fstack-protector
endif

ifdef CONFIG_STACKPROTECTOR_STRONG
PURGATORY_CFLAGS_REMOVE		+= -fstack-protector-strong
endif

ifdef CONFIG_RETPOLINE
PURGATORY_CFLAGS_REMOVE		+= $(RETPOLINE_CFLAGS)
endif

CFLAGS_REMOVE_purgatory.o	+= $(PURGATORY_CFLAGS_REMOVE)
CFLAGS_purgatory.o		+= $(PURGATORY_CFLAGS)

CFLAGS_REMOVE_sha256.o		+= $(PURGATORY_CFLAGS_REMOVE)
CFLAGS_sha256.o			+= $(PURGATORY_CFLAGS)

CFLAGS_REMOVE_string.o		+= $(PURGATORY_CFLAGS_REMOVE)
CFLAGS_string.o			+= $(PURGATORY_CFLAGS)
=======
# Default KBUILD_CFLAGS can have -pg option set when FTRACE is enabled. That
# in turn leaves some undefined symbols like __fentry__ in purgatory and not
# sure how to relocate those. Like kexec-tools, use custom flags.

KBUILD_CFLAGS := -fno-strict-aliasing -Wall -Wstrict-prototypes -fno-zero-initialized-in-bss -fno-builtin -ffreestanding -c -MD -Os -mcmodel=large
KBUILD_CFLAGS += -m$(BITS)
KBUILD_CFLAGS += $(call cc-option,-fno-PIE)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

$(obj)/purgatory.ro: $(PURGATORY_OBJS) FORCE
		$(call if_changed,ld)

targets += kexec-purgatory.c

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

obj-$(CONFIG_KEXEC_FILE)	+= kexec-purgatory.o
