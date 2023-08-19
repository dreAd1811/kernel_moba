/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _BCACHE_EXTENTS_H
#define _BCACHE_EXTENTS_H

extern const struct btree_keys_ops bch_btree_keys_ops;
extern const struct btree_keys_ops bch_extent_keys_ops;

struct bkey;
struct cache_set;

<<<<<<< HEAD
void bch_extent_to_text(char *buf, size_t size, const struct bkey *k);
bool __bch_btree_ptr_invalid(struct cache_set *c, const struct bkey *k);
bool __bch_extent_invalid(struct cache_set *c, const struct bkey *k);
=======
void bch_extent_to_text(char *, size_t, const struct bkey *);
bool __bch_btree_ptr_invalid(struct cache_set *, const struct bkey *);
bool __bch_extent_invalid(struct cache_set *, const struct bkey *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* _BCACHE_EXTENTS_H */
