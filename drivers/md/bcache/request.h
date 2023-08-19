/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _BCACHE_REQUEST_H_
#define _BCACHE_REQUEST_H_

struct data_insert_op {
	struct closure		cl;
	struct cache_set	*c;
	struct bio		*bio;
	struct workqueue_struct *wq;

<<<<<<< HEAD
	unsigned int		inode;
=======
	unsigned		inode;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	uint16_t		write_point;
	uint16_t		write_prio;
	blk_status_t		status;

	union {
		uint16_t	flags;

	struct {
<<<<<<< HEAD
		unsigned int	bypass:1;
		unsigned int	writeback:1;
		unsigned int	flush_journal:1;
		unsigned int	csum:1;

		unsigned int	replace:1;
		unsigned int	replace_collision:1;

		unsigned int	insert_data_done:1;
=======
		unsigned	bypass:1;
		unsigned	writeback:1;
		unsigned	flush_journal:1;
		unsigned	csum:1;

		unsigned	replace:1;
		unsigned	replace_collision:1;

		unsigned	insert_data_done:1;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	};
	};

	struct keylist		insert_keys;
	BKEY_PADDED(replace_key);
};

<<<<<<< HEAD
unsigned int bch_get_congested(struct cache_set *c);
=======
unsigned bch_get_congested(struct cache_set *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void bch_data_insert(struct closure *cl);

void bch_cached_dev_request_init(struct cached_dev *dc);
void bch_flash_dev_request_init(struct bcache_device *d);

extern struct kmem_cache *bch_search_cache, *bch_passthrough_cache;

#endif /* _BCACHE_REQUEST_H_ */
