# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
lib-y		:= clear_user.o delay.o copy_from_user.o		\
		   copy_to_user.o copy_in_user.o copy_page.o		\
		   clear_page.o memchr.o memcpy.o memmove.o memset.o	\
		   memcmp.o strcmp.o strncmp.o strlen.o strnlen.o	\
		   strchr.o strrchr.o tishift.o
=======
lib-y		:= bitops.o clear_user.o delay.o copy_from_user.o	\
		   copy_to_user.o copy_in_user.o copy_page.o		\
		   clear_page.o memchr.o memcpy.o memmove.o memset.o	\
		   memcmp.o strcmp.o strncmp.o strlen.o strnlen.o	\
		   strchr.o strrchr.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

# Tell the compiler to treat all general purpose registers (with the
# exception of the IP registers, which are already handled by the caller
# in case of a PLT) as callee-saved, which allows for efficient runtime
# patching of the bl instruction in the caller with an atomic instruction
# when supported by the CPU. Result and argument registers are handled
# correctly, based on the function prototype.
<<<<<<< HEAD
ifeq ($(CONFIG_LD_IS_LLD), y)
=======
ifeq ($(ld-name),lld)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
# https://bugs.llvm.org/show_bug.cgi?id=35841
obj-$(CONFIG_ARM64_LSE_ATOMICS) += atomic_ll_sc.o
else
lib-$(CONFIG_ARM64_LSE_ATOMICS) += atomic_ll_sc.o
endif
CFLAGS_atomic_ll_sc.o	:= -ffixed-x1 -ffixed-x2        		\
		   -ffixed-x3 -ffixed-x4 -ffixed-x5 -ffixed-x6		\
		   -ffixed-x7 -fcall-saved-x8 -fcall-saved-x9		\
		   -fcall-saved-x10 -fcall-saved-x11 -fcall-saved-x12	\
		   -fcall-saved-x13 -fcall-saved-x14 -fcall-saved-x15	\
<<<<<<< HEAD
		   -fcall-saved-x18 -fomit-frame-pointer
CFLAGS_REMOVE_atomic_ll_sc.o := -pg
GCOV_PROFILE_atomic_ll_sc.o	:= n
KASAN_SANITIZE_atomic_ll_sc.o	:= n
KCOV_INSTRUMENT_atomic_ll_sc.o	:= n
UBSAN_SANITIZE_atomic_ll_sc.o	:= n
=======
		   -fcall-saved-x18
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

lib-$(CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE) += uaccess_flushcache.o
