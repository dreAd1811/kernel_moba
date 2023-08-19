/* SPDX-License-Identifier: GPL-2.0 */
/*
 * These are exported solely for the purpose of mtd_blkdevs.c and mtdchar.c.
 * You should not use them for _anything_ else.
 */

extern struct mutex mtd_table_mutex;

struct mtd_info *__mtd_next_device(int i);
<<<<<<< HEAD
int add_mtd_device(struct mtd_info *mtd);
=======
int __must_check add_mtd_device(struct mtd_info *mtd);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int del_mtd_device(struct mtd_info *mtd);
int add_mtd_partitions(struct mtd_info *, const struct mtd_partition *, int);
int del_mtd_partitions(struct mtd_info *);

struct mtd_partitions;

int parse_mtd_partitions(struct mtd_info *master, const char * const *types,
<<<<<<< HEAD
=======
			 struct mtd_partitions *pparts,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			 struct mtd_part_parser_data *data);

void mtd_part_parser_cleanup(struct mtd_partitions *parts);

int __init init_mtdchar(void);
void __exit cleanup_mtdchar(void);

#define mtd_for_each_device(mtd)			\
	for ((mtd) = __mtd_next_device(0);		\
	     (mtd) != NULL;				\
	     (mtd) = __mtd_next_device(mtd->index + 1))
