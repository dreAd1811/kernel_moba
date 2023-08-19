/* SPDX-License-Identifier: GPL-2.0 */
#ifndef MMC_QUEUE_H
#define MMC_QUEUE_H

#include <linux/types.h>
#include <linux/blkdev.h>
#include <linux/blk-mq.h>
#include <linux/mmc/core.h>
#include <linux/mmc/host.h>

<<<<<<< HEAD
enum mmc_issued {
	MMC_REQ_STARTED,
	MMC_REQ_BUSY,
	MMC_REQ_FAILED_TO_START,
	MMC_REQ_FINISHED,
};

enum mmc_issue_type {
	MMC_ISSUE_SYNC,
	MMC_ISSUE_DCMD,
	MMC_ISSUE_ASYNC,
	MMC_ISSUE_MAX,
};

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static inline struct mmc_queue_req *req_to_mmc_queue_req(struct request *rq)
{
	return blk_mq_rq_to_pdu(rq);
}

struct mmc_queue_req;

static inline struct request *mmc_queue_req_to_req(struct mmc_queue_req *mqr)
{
	return blk_mq_rq_from_pdu(mqr);
}

<<<<<<< HEAD
=======
struct task_struct;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct mmc_blk_data;
struct mmc_blk_ioc_data;

struct mmc_blk_request {
	struct mmc_request	mrq;
	struct mmc_command	sbc;
	struct mmc_command	cmd;
	struct mmc_command	stop;
	struct mmc_data		data;
<<<<<<< HEAD
=======
	int			retune_retry_done;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

/**
 * enum mmc_drv_op - enumerates the operations in the mmc_queue_req
 * @MMC_DRV_OP_IOCTL: ioctl operation
<<<<<<< HEAD
 * @MMC_DRV_OP_IOCTL_RPMB: RPMB-oriented ioctl operation
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @MMC_DRV_OP_BOOT_WP: write protect boot partitions
 * @MMC_DRV_OP_GET_CARD_STATUS: get card status
 * @MMC_DRV_OP_GET_EXT_CSD: get the EXT CSD from an eMMC card
 */
enum mmc_drv_op {
	MMC_DRV_OP_IOCTL,
<<<<<<< HEAD
	MMC_DRV_OP_IOCTL_RPMB,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	MMC_DRV_OP_BOOT_WP,
	MMC_DRV_OP_GET_CARD_STATUS,
	MMC_DRV_OP_GET_EXT_CSD,
};

struct mmc_queue_req {
	struct mmc_blk_request	brq;
	struct scatterlist	*sg;
<<<<<<< HEAD
=======
	struct mmc_async_req	areq;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	enum mmc_drv_op		drv_op;
	int			drv_op_result;
	void			*drv_op_data;
	unsigned int		ioc_count;
<<<<<<< HEAD
	int			retries;
=======
	struct mmc_cmdq_req	cmdq_req;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct mmc_queue {
	struct mmc_card		*card;
<<<<<<< HEAD
	struct mmc_ctx		ctx;
	struct blk_mq_tag_set	tag_set;
	struct mmc_blk_data	*blkdata;
	struct request_queue	*queue;
	int			in_flight[MMC_ISSUE_MAX];
	unsigned int		cqe_busy;
#define MMC_CQE_DCMD_BUSY	BIT(0)
#define MMC_CQE_QUEUE_FULL	BIT(1)
	bool			busy;
	bool			use_cqe;
	bool			recovery_needed;
	bool			in_recovery;
	bool			rw_wait;
	bool			waiting;
	struct work_struct	recovery_work;
	wait_queue_head_t	wait;
	struct request		*recovery_req;
	struct request		*complete_req;
	struct mutex		complete_lock;
	struct work_struct	complete_work;
};

extern int mmc_init_queue(struct mmc_queue *, struct mmc_card *, spinlock_t *,
			  const char *);
extern void mmc_cleanup_queue(struct mmc_queue *);
extern void mmc_queue_suspend(struct mmc_queue *);
extern void mmc_queue_resume(struct mmc_queue *);
extern unsigned int mmc_queue_map_sg(struct mmc_queue *,
				     struct mmc_queue_req *);

void mmc_cqe_check_busy(struct mmc_queue *mq);
void mmc_cqe_recovery_notifier(struct mmc_request *mrq);

enum mmc_issue_type mmc_issue_type(struct mmc_queue *mq, struct request *req);

static inline int mmc_tot_in_flight(struct mmc_queue *mq)
{
	return mq->in_flight[MMC_ISSUE_SYNC] +
	       mq->in_flight[MMC_ISSUE_DCMD] +
	       mq->in_flight[MMC_ISSUE_ASYNC];
}

static inline int mmc_cqe_qcnt(struct mmc_queue *mq)
{
	return mq->in_flight[MMC_ISSUE_DCMD] +
	       mq->in_flight[MMC_ISSUE_ASYNC];
}
=======
	struct task_struct	*thread;
	struct semaphore	thread_sem;
	unsigned long		flags;
#define MMC_QUEUE_SUSPENDED		0
	int (*issue_fn)(struct mmc_queue *, struct request *);
	int (*cmdq_issue_fn)(struct mmc_queue *,
			     struct request *);
	void (*cmdq_complete_fn)(struct request *);
	void (*cmdq_error_fn)(struct mmc_queue *);
	enum blk_eh_timer_return (*cmdq_req_timed_out)(struct request *);
	bool			suspended;
	bool			asleep;
	struct mmc_blk_data	*blkdata;
	struct request_queue	*queue;
	struct work_struct	cmdq_err_work;

	struct completion	cmdq_pending_req_done;
	struct completion	cmdq_shutdown_complete;
	struct request		*cmdq_req_peeked;
	void (*cmdq_shutdown)(struct mmc_queue *);
	/*
	 * FIXME: this counter is not a very reliable way of keeping
	 * track of how many requests that are ongoing. Switch to just
	 * letting the block core keep track of requests and per-request
	 * associated mmc_queue_req data.
	 */
	int			qcnt;
#ifdef CONFIG_MMC_SIMULATE_MAX_SPEED
	atomic_t max_write_speed;
	atomic_t max_read_speed;
	atomic_t cache_size;
	/* i/o tracking */
	atomic_long_t cache_used;
	unsigned long cache_jiffies;
#endif
};

extern int mmc_init_queue(struct mmc_queue *, struct mmc_card *, spinlock_t *,
			  const char *, int);
extern void mmc_cleanup_queue(struct mmc_queue *);
extern int mmc_queue_suspend(struct mmc_queue *mq, int wait);
extern void mmc_queue_resume(struct mmc_queue *);

extern unsigned int mmc_queue_map_sg(struct mmc_queue *,
				     struct mmc_queue_req *);
extern void mmc_queue_bounce_pre(struct mmc_queue_req *mqrq);
extern void mmc_queue_bounce_post(struct mmc_queue_req *mqrq);

extern int mmc_access_rpmb(struct mmc_queue *);

extern int mmc_cmdq_init(struct mmc_queue *mq, struct mmc_card *card);
extern void mmc_cmdq_clean(struct mmc_queue *mq, struct mmc_card *card);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif
