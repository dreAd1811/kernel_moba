/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MMC_CORE_BLOCK_H
#define _MMC_CORE_BLOCK_H

struct mmc_queue;
struct request;

<<<<<<< HEAD
void mmc_blk_cqe_recovery(struct mmc_queue *mq);

enum mmc_issued;

enum mmc_issued mmc_blk_mq_issue_rq(struct mmc_queue *mq, struct request *req);
void mmc_blk_mq_complete(struct request *req);
void mmc_blk_mq_recovery(struct mmc_queue *mq);

struct work_struct;

void mmc_blk_mq_complete_work(struct work_struct *work);
=======
void mmc_blk_issue_rq(struct mmc_queue *mq, struct request *req);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif
