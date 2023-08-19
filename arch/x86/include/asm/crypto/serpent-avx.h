/* SPDX-License-Identifier: GPL-2.0 */
#ifndef ASM_X86_SERPENT_AVX_H
#define ASM_X86_SERPENT_AVX_H

<<<<<<< HEAD
#include <crypto/b128ops.h>
#include <crypto/serpent.h>
#include <linux/types.h>

struct crypto_skcipher;

#define SERPENT_PARALLEL_BLOCKS 8

=======
#include <linux/crypto.h>
#include <crypto/serpent.h>

#define SERPENT_PARALLEL_BLOCKS 8

struct serpent_lrw_ctx {
	struct lrw_table_ctx lrw_table;
	struct serpent_ctx serpent_ctx;
};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct serpent_xts_ctx {
	struct serpent_ctx tweak_ctx;
	struct serpent_ctx crypt_ctx;
};

asmlinkage void serpent_ecb_enc_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src);
asmlinkage void serpent_ecb_dec_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src);

asmlinkage void serpent_cbc_dec_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src);
asmlinkage void serpent_ctr_8way_avx(struct serpent_ctx *ctx, u8 *dst,
				     const u8 *src, le128 *iv);

asmlinkage void serpent_xts_enc_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src, le128 *iv);
asmlinkage void serpent_xts_dec_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src, le128 *iv);

extern void __serpent_crypt_ctr(void *ctx, u128 *dst, const u128 *src,
				le128 *iv);

extern void serpent_xts_enc(void *ctx, u128 *dst, const u128 *src, le128 *iv);
extern void serpent_xts_dec(void *ctx, u128 *dst, const u128 *src, le128 *iv);

<<<<<<< HEAD
extern int xts_serpent_setkey(struct crypto_skcipher *tfm, const u8 *key,
=======
extern int lrw_serpent_setkey(struct crypto_tfm *tfm, const u8 *key,
			      unsigned int keylen);

extern void lrw_serpent_exit_tfm(struct crypto_tfm *tfm);

extern int xts_serpent_setkey(struct crypto_tfm *tfm, const u8 *key,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			      unsigned int keylen);

#endif
