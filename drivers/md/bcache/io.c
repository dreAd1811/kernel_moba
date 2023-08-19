// SPDX-License-Identifier: GPL-2.0
/*
 * Some low level IO code, and hacks for various block layer limitations
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#include "bcache.h"
#include "bset.h"
#include "debug.h"

#include <linux/blkdev.h>

/* Bios with headers */

void bch_bbio_free(struct bio *bio, struct cache_set *c)
{
	struct bbio *b = container_of(bio, struct bbio, bio);
<<<<<<< HEAD

	mempool_free(b, &c->bio_meta);
=======
	mempool_free(b, c->bio_meta);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

struct bio *bch_bbio_alloc(struct cache_set *c)
{
<<<<<<< HEAD
	struct bbio *b = mempool_alloc(&c->bio_meta, GFP_NOIO);
=======
	struct bbio *b = mempool_alloc(c->bio_meta, GFP_NOIO);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct bio *bio = &b->bio;

	bio_init(bio, bio->bi_inline_vecs, bucket_pages(c));

	return bio;
}

void __bch_submit_bbio(struct bio *bio, struct cache_set *c)
{
	struct bbio *b = container_of(bio, struct bbio, bio);

	bio->bi_iter.bi_sector	= PTR_OFFSET(&b->key, 0);
	bio_set_dev(bio, PTR_CACHE(c, &b->key, 0)->bdev);

	b->submit_time_us = local_clock_us();
<<<<<<< HEAD
	closure_bio_submit(c, bio, bio->bi_private);
}

void bch_submit_bbio(struct bio *bio, struct cache_set *c,
		     struct bkey *k, unsigned int ptr)
{
	struct bbio *b = container_of(bio, struct bbio, bio);

=======
	closure_bio_submit(bio, bio->bi_private);
}

void bch_submit_bbio(struct bio *bio, struct cache_set *c,
		     struct bkey *k, unsigned ptr)
{
	struct bbio *b = container_of(bio, struct bbio, bio);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	bch_bkey_copy_single_ptr(&b->key, k, ptr);
	__bch_submit_bbio(bio, c);
}

/* IO errors */
<<<<<<< HEAD
void bch_count_backing_io_errors(struct cached_dev *dc, struct bio *bio)
{
	unsigned int errors;

	WARN_ONCE(!dc, "NULL pointer of struct cached_dev");

	/*
	 * Read-ahead requests on a degrading and recovering md raid
	 * (e.g. raid6) device might be failured immediately by md
	 * raid code, which is not a real hardware media failure. So
	 * we shouldn't count failed REQ_RAHEAD bio to dc->io_errors.
	 */
	if (bio->bi_opf & REQ_RAHEAD) {
		pr_warn_ratelimited("%s: Read-ahead I/O failed on backing device, ignore",
				    dc->backing_dev_name);
		return;
	}

	errors = atomic_add_return(1, &dc->io_errors);
	if (errors < dc->error_limit)
		pr_err("%s: IO error on backing device, unrecoverable",
			dc->backing_dev_name);
	else
		bch_cached_dev_error(dc);
}

void bch_count_io_errors(struct cache *ca,
			 blk_status_t error,
			 int is_read,
			 const char *m)
=======

void bch_count_io_errors(struct cache *ca, blk_status_t error, const char *m)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	/*
	 * The halflife of an error is:
	 * log2(1/2)/log2(127/128) * refresh ~= 88 * refresh
	 */

	if (ca->set->error_decay) {
<<<<<<< HEAD
		unsigned int count = atomic_inc_return(&ca->io_count);

		while (count > ca->set->error_decay) {
			unsigned int errors;
			unsigned int old = count;
			unsigned int new = count - ca->set->error_decay;

			/*
			 * First we subtract refresh from count; each time we
			 * successfully do so, we rescale the errors once:
=======
		unsigned count = atomic_inc_return(&ca->io_count);

		while (count > ca->set->error_decay) {
			unsigned errors;
			unsigned old = count;
			unsigned new = count - ca->set->error_decay;

			/*
			 * First we subtract refresh from count; each time we
			 * succesfully do so, we rescale the errors once:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			 */

			count = atomic_cmpxchg(&ca->io_count, old, new);

			if (count == old) {
				count = new;

				errors = atomic_read(&ca->io_errors);
				do {
					old = errors;
					new = ((uint64_t) errors * 127) / 128;
					errors = atomic_cmpxchg(&ca->io_errors,
								old, new);
				} while (old != errors);
			}
		}
	}

	if (error) {
<<<<<<< HEAD
		unsigned int errors = atomic_add_return(1 << IO_ERROR_SHIFT,
=======
		char buf[BDEVNAME_SIZE];
		unsigned errors = atomic_add_return(1 << IO_ERROR_SHIFT,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
						    &ca->io_errors);
		errors >>= IO_ERROR_SHIFT;

		if (errors < ca->set->error_limit)
<<<<<<< HEAD
			pr_err("%s: IO error on %s%s",
			       ca->cache_dev_name, m,
			       is_read ? ", recovering." : ".");
		else
			bch_cache_set_error(ca->set,
					    "%s: too many IO errors %s",
					    ca->cache_dev_name, m);
=======
			pr_err("%s: IO error on %s, recovering",
			       bdevname(ca->bdev, buf), m);
		else
			bch_cache_set_error(ca->set,
					    "%s: too many IO errors %s",
					    bdevname(ca->bdev, buf), m);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

void bch_bbio_count_io_errors(struct cache_set *c, struct bio *bio,
			      blk_status_t error, const char *m)
{
	struct bbio *b = container_of(bio, struct bbio, bio);
	struct cache *ca = PTR_CACHE(c, &b->key, 0);
<<<<<<< HEAD
	int is_read = (bio_data_dir(bio) == READ ? 1 : 0);

	unsigned int threshold = op_is_write(bio_op(bio))
=======

	unsigned threshold = op_is_write(bio_op(bio))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		? c->congested_write_threshold_us
		: c->congested_read_threshold_us;

	if (threshold) {
<<<<<<< HEAD
		unsigned int t = local_clock_us();
=======
		unsigned t = local_clock_us();

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		int us = t - b->submit_time_us;
		int congested = atomic_read(&c->congested);

		if (us > (int) threshold) {
			int ms = us / 1024;
<<<<<<< HEAD

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			c->congested_last_us = t;

			ms = min(ms, CONGESTED_MAX + congested);
			atomic_sub(ms, &c->congested);
		} else if (congested < 0)
			atomic_inc(&c->congested);
	}

<<<<<<< HEAD
	bch_count_io_errors(ca, error, is_read, m);
=======
	bch_count_io_errors(ca, error, m);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

void bch_bbio_endio(struct cache_set *c, struct bio *bio,
		    blk_status_t error, const char *m)
{
	struct closure *cl = bio->bi_private;

	bch_bbio_count_io_errors(c, bio, error, m);
	bio_put(bio);
	closure_put(cl);
}
