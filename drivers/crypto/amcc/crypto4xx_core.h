/**
 * AMCC SoC PPC4xx Crypto Driver
 *
 * Copyright (c) 2008 Applied Micro Circuits Corporation.
 * All rights reserved. James Hsiao <jhsiao@amcc.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This is the header file for AMCC Crypto offload Linux device driver for
 * use with Linux CryptoAPI.

 */

#ifndef __CRYPTO4XX_CORE_H__
#define __CRYPTO4XX_CORE_H__

<<<<<<< HEAD
#include <linux/ratelimit.h>
#include <crypto/internal/hash.h>
#include <crypto/internal/aead.h>
#include <crypto/internal/skcipher.h>
#include "crypto4xx_reg_def.h"
#include "crypto4xx_sa.h"
=======
#include <crypto/internal/hash.h>

#define MODULE_NAME "crypto4xx"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define PPC460SX_SDR0_SRST                      0x201
#define PPC405EX_SDR0_SRST                      0x200
#define PPC460EX_SDR0_SRST                      0x201
#define PPC460EX_CE_RESET                       0x08000000
#define PPC460SX_CE_RESET                       0x20000000
#define PPC405EX_CE_RESET                       0x00000008

#define CRYPTO4XX_CRYPTO_PRIORITY		300
#define PPC4XX_NUM_PD				256
#define PPC4XX_LAST_PD				(PPC4XX_NUM_PD - 1)
#define PPC4XX_NUM_GD				1024
#define PPC4XX_LAST_GD				(PPC4XX_NUM_GD - 1)
#define PPC4XX_NUM_SD				256
#define PPC4XX_LAST_SD				(PPC4XX_NUM_SD - 1)
#define PPC4XX_SD_BUFFER_SIZE			2048

<<<<<<< HEAD
#define PD_ENTRY_BUSY				BIT(1)
#define PD_ENTRY_INUSE				BIT(0)
=======
#define PD_ENTRY_INUSE				1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define PD_ENTRY_FREE				0
#define ERING_WAS_FULL				0xffffffff

struct crypto4xx_device;

<<<<<<< HEAD
union shadow_sa_buf {
	struct dynamic_sa_ctl sa;

	/* alloc 256 bytes which is enough for any kind of dynamic sa */
	u8 buf[256];
} __packed;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct pd_uinfo {
	struct crypto4xx_device *dev;
	u32   state;
	u32 using_sd;
	u32 first_gd;		/* first gather discriptor
				used by this packet */
	u32 num_gd;             /* number of gather discriptor
				used by this packet */
	u32 first_sd;		/* first scatter discriptor
				used by this packet */
	u32 num_sd;		/* number of scatter discriptors
				used by this packet */
<<<<<<< HEAD
	struct dynamic_sa_ctl *sa_va;	/* shadow sa */
	struct sa_state_record *sr_va;	/* state record for shadow sa */
=======
	void *sa_va;		/* shadow sa, when using cp from ctx->sa */
	u32 sa_pa;
	void *sr_va;		/* state record for shadow sa */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 sr_pa;
	struct scatterlist *dest_va;
	struct crypto_async_request *async_req; 	/* base crypto request
							for this packet */
};

struct crypto4xx_device {
	struct crypto4xx_core_device *core_dev;
<<<<<<< HEAD
	void __iomem *ce_base;
	void __iomem *trng_base;

	struct ce_pd *pdr;	/* base address of packet descriptor ring */
	dma_addr_t pdr_pa;	/* physical address of pdr_base_register */
	struct ce_gd *gdr;	/* gather descriptor ring */
	dma_addr_t gdr_pa;	/* physical address of gdr_base_register */
	struct ce_sd *sdr;	/* scatter descriptor ring */
	dma_addr_t sdr_pa;	/* physical address of sdr_base_register */
	void *scatter_buffer_va;
	dma_addr_t scatter_buffer_pa;

	union shadow_sa_buf *shadow_sa_pool;
	dma_addr_t shadow_sa_pool_pa;
	struct sa_state_record *shadow_sr_pool;
=======
	char *name;
	u64  ce_phy_address;
	void __iomem *ce_base;
	void __iomem *trng_base;

	void *pdr;			/* base address of packet
					descriptor ring */
	dma_addr_t pdr_pa;		/* physical address used to
					program ce pdr_base_register */
	void *gdr;                      /* gather descriptor ring */
	dma_addr_t gdr_pa;		/* physical address used to
					program ce gdr_base_register */
	void *sdr;			/* scatter descriptor ring */
	dma_addr_t sdr_pa;		/* physical address used to
					program ce sdr_base_register */
	void *scatter_buffer_va;
	dma_addr_t scatter_buffer_pa;
	u32 scatter_buffer_size;

	void *shadow_sa_pool;		/* pool of memory for sa in pd_uinfo */
	dma_addr_t shadow_sa_pool_pa;
	void *shadow_sr_pool;		/* pool of memory for sr in pd_uinfo */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	dma_addr_t shadow_sr_pool_pa;
	u32 pdr_tail;
	u32 pdr_head;
	u32 gdr_tail;
	u32 gdr_head;
	u32 sdr_tail;
	u32 sdr_head;
<<<<<<< HEAD
	struct pd_uinfo *pdr_uinfo;
	struct list_head alg_list;	/* List of algorithm supported
					by this device */
	struct ratelimit_state aead_ratelimit;
	bool is_revb;
=======
	void *pdr_uinfo;
	struct list_head alg_list;	/* List of algorithm supported
					by this device */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct crypto4xx_core_device {
	struct device *device;
	struct platform_device *ofdev;
	struct crypto4xx_device *dev;
	struct hwrng *trng;
	u32 int_status;
	u32 irq;
	struct tasklet_struct tasklet;
	spinlock_t lock;
};

struct crypto4xx_ctx {
	struct crypto4xx_device *dev;
<<<<<<< HEAD
	struct dynamic_sa_ctl *sa_in;
	struct dynamic_sa_ctl *sa_out;
	__le32 iv_nonce;
	u32 sa_len;
	union {
		struct crypto_skcipher *cipher;
		struct crypto_aead *aead;
	} sw_cipher;
};

struct crypto4xx_aead_reqctx {
	struct scatterlist dst[2];
=======
	void *sa_in;
	dma_addr_t sa_in_dma_addr;
	void *sa_out;
	dma_addr_t sa_out_dma_addr;
	void *state_record;
	dma_addr_t state_record_dma_addr;
	u32 sa_len;
	u32 offset_to_sr_ptr;           /* offset to state ptr, in dynamic sa */
	u32 direction;
	u32 next_hdr;
	u32 save_iv;
	u32 pd_ctl_len;
	u32 pd_ctl;
	u32 bypass;
	u32 is_hash;
	u32 hash_final;
};

struct crypto4xx_req_ctx {
	struct crypto4xx_device *dev;	/* Device in which
					operation to send to */
	void *sa;
	u32 sa_dma_addr;
	u16 sa_len;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct crypto4xx_alg_common {
	u32 type;
	union {
<<<<<<< HEAD
		struct skcipher_alg cipher;
		struct ahash_alg hash;
		struct aead_alg aead;
=======
		struct crypto_alg cipher;
		struct ahash_alg hash;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	} u;
};

struct crypto4xx_alg {
	struct list_head  entry;
	struct crypto4xx_alg_common alg;
	struct crypto4xx_device *dev;
};

<<<<<<< HEAD
int crypto4xx_alloc_sa(struct crypto4xx_ctx *ctx, u32 size);
void crypto4xx_free_sa(struct crypto4xx_ctx *ctx);
void crypto4xx_free_ctx(struct crypto4xx_ctx *ctx);
int crypto4xx_build_pd(struct crypto_async_request *req,
		       struct crypto4xx_ctx *ctx,
		       struct scatterlist *src,
		       struct scatterlist *dst,
		       const unsigned int datalen,
		       const __le32 *iv, const u32 iv_len,
		       const struct dynamic_sa_ctl *sa,
		       const unsigned int sa_len,
		       const unsigned int assoclen,
		       struct scatterlist *dst_tmp);
int crypto4xx_setkey_aes_cbc(struct crypto_skcipher *cipher,
			     const u8 *key, unsigned int keylen);
int crypto4xx_setkey_aes_cfb(struct crypto_skcipher *cipher,
			     const u8 *key, unsigned int keylen);
int crypto4xx_setkey_aes_ctr(struct crypto_skcipher *cipher,
			     const u8 *key, unsigned int keylen);
int crypto4xx_setkey_aes_ecb(struct crypto_skcipher *cipher,
			     const u8 *key, unsigned int keylen);
int crypto4xx_setkey_aes_ofb(struct crypto_skcipher *cipher,
			     const u8 *key, unsigned int keylen);
int crypto4xx_setkey_rfc3686(struct crypto_skcipher *cipher,
			     const u8 *key, unsigned int keylen);
int crypto4xx_encrypt_ctr(struct skcipher_request *req);
int crypto4xx_decrypt_ctr(struct skcipher_request *req);
int crypto4xx_encrypt_iv_stream(struct skcipher_request *req);
int crypto4xx_decrypt_iv_stream(struct skcipher_request *req);
int crypto4xx_encrypt_iv_block(struct skcipher_request *req);
int crypto4xx_decrypt_iv_block(struct skcipher_request *req);
int crypto4xx_encrypt_noiv_block(struct skcipher_request *req);
int crypto4xx_decrypt_noiv_block(struct skcipher_request *req);
int crypto4xx_rfc3686_encrypt(struct skcipher_request *req);
int crypto4xx_rfc3686_decrypt(struct skcipher_request *req);
int crypto4xx_sha1_alg_init(struct crypto_tfm *tfm);
int crypto4xx_hash_digest(struct ahash_request *req);
int crypto4xx_hash_final(struct ahash_request *req);
int crypto4xx_hash_update(struct ahash_request *req);
int crypto4xx_hash_init(struct ahash_request *req);

/**
 * Note: Only use this function to copy items that is word aligned.
 */
static inline void crypto4xx_memcpy_swab32(u32 *dst, const void *buf,
					   size_t len)
{
	for (; len >= 4; buf += 4, len -= 4)
		*dst++ = __swab32p((u32 *) buf);

	if (len) {
		const u8 *tmp = (u8 *)buf;

		switch (len) {
		case 3:
			*dst = (tmp[2] << 16) |
			       (tmp[1] << 8) |
			       tmp[0];
			break;
		case 2:
			*dst = (tmp[1] << 8) |
			       tmp[0];
			break;
		case 1:
			*dst = tmp[0];
			break;
		default:
			break;
		}
	}
}

static inline void crypto4xx_memcpy_from_le32(u32 *dst, const void *buf,
					      size_t len)
{
	crypto4xx_memcpy_swab32(dst, buf, len);
}

static inline void crypto4xx_memcpy_to_le32(__le32 *dst, const void *buf,
					    size_t len)
{
	crypto4xx_memcpy_swab32((u32 *)dst, buf, len);
}

int crypto4xx_setauthsize_aead(struct crypto_aead *ciper,
			       unsigned int authsize);
int crypto4xx_setkey_aes_ccm(struct crypto_aead *cipher,
			     const u8 *key, unsigned int keylen);
int crypto4xx_encrypt_aes_ccm(struct aead_request *req);
int crypto4xx_decrypt_aes_ccm(struct aead_request *req);
int crypto4xx_setkey_aes_gcm(struct crypto_aead *cipher,
			     const u8 *key, unsigned int keylen);
int crypto4xx_encrypt_aes_gcm(struct aead_request *req);
int crypto4xx_decrypt_aes_gcm(struct aead_request *req);

=======
static inline struct crypto4xx_alg *crypto_alg_to_crypto4xx_alg(
	struct crypto_alg *x)
{
	switch (x->cra_flags & CRYPTO_ALG_TYPE_MASK) {
	case CRYPTO_ALG_TYPE_AHASH:
		return container_of(__crypto_ahash_alg(x),
				    struct crypto4xx_alg, alg.u.hash);
	}

	return container_of(x, struct crypto4xx_alg, alg.u.cipher);
}

extern int crypto4xx_alloc_sa(struct crypto4xx_ctx *ctx, u32 size);
extern void crypto4xx_free_sa(struct crypto4xx_ctx *ctx);
extern u32 crypto4xx_alloc_sa_rctx(struct crypto4xx_ctx *ctx,
				   struct crypto4xx_ctx *rctx);
extern void crypto4xx_free_sa_rctx(struct crypto4xx_ctx *rctx);
extern void crypto4xx_free_ctx(struct crypto4xx_ctx *ctx);
extern u32 crypto4xx_alloc_state_record(struct crypto4xx_ctx *ctx);
extern u32 get_dynamic_sa_offset_state_ptr_field(struct crypto4xx_ctx *ctx);
extern u32 get_dynamic_sa_offset_key_field(struct crypto4xx_ctx *ctx);
extern u32 get_dynamic_sa_iv_size(struct crypto4xx_ctx *ctx);
extern void crypto4xx_memcpy_le(unsigned int *dst,
				const unsigned char *buf, int len);
extern u32 crypto4xx_build_pd(struct crypto_async_request *req,
			      struct crypto4xx_ctx *ctx,
			      struct scatterlist *src,
			      struct scatterlist *dst,
			      unsigned int datalen,
			      void *iv, u32 iv_len);
extern int crypto4xx_setkey_aes_cbc(struct crypto_ablkcipher *cipher,
				    const u8 *key, unsigned int keylen);
extern int crypto4xx_encrypt(struct ablkcipher_request *req);
extern int crypto4xx_decrypt(struct ablkcipher_request *req);
extern int crypto4xx_sha1_alg_init(struct crypto_tfm *tfm);
extern int crypto4xx_hash_digest(struct ahash_request *req);
extern int crypto4xx_hash_final(struct ahash_request *req);
extern int crypto4xx_hash_update(struct ahash_request *req);
extern int crypto4xx_hash_init(struct ahash_request *req);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
