/*
 * A FSI master controller, using a simple GPIO bit-banging interface
 */

#include <linux/crc4.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fsi.h>
#include <linux/gpio/consumer.h>
#include <linux/io.h>
<<<<<<< HEAD
#include <linux/irqflags.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
=======
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include "fsi-master.h"

#define	FSI_GPIO_STD_DLY	1	/* Standard pin delay in nS */
<<<<<<< HEAD
#define LAST_ADDR_INVALID		0x1
=======
#define	FSI_ECHO_DELAY_CLOCKS	16	/* Number clocks for echo delay */
#define	FSI_PRE_BREAK_CLOCKS	50	/* Number clocks to prep for break */
#define	FSI_BREAK_CLOCKS	256	/* Number of clocks to issue break */
#define	FSI_POST_BREAK_CLOCKS	16000	/* Number clocks to set up cfam */
#define	FSI_INIT_CLOCKS		5000	/* Clock out any old data */
#define	FSI_GPIO_STD_DELAY	10	/* Standard GPIO delay in nS */
					/* todo: adjust down as low as */
					/* possible or eliminate */
#define	FSI_GPIO_CMD_DPOLL      0x2
#define	FSI_GPIO_CMD_TERM	0x3f
#define FSI_GPIO_CMD_ABS_AR	0x4

#define	FSI_GPIO_DPOLL_CLOCKS	100      /* < 21 will cause slave to hang */

/* Bus errors */
#define	FSI_GPIO_ERR_BUSY	1	/* Slave stuck in busy state */
#define	FSI_GPIO_RESP_ERRA	2	/* Any (misc) Error */
#define	FSI_GPIO_RESP_ERRC	3	/* Slave reports master CRC error */
#define	FSI_GPIO_MTOE		4	/* Master time out error */
#define	FSI_GPIO_CRC_INVAL	5	/* Master reports slave CRC error */

/* Normal slave responses */
#define	FSI_GPIO_RESP_BUSY	1
#define	FSI_GPIO_RESP_ACK	0
#define	FSI_GPIO_RESP_ACKD	4

#define	FSI_GPIO_MAX_BUSY	100
#define	FSI_GPIO_MTOE_COUNT	1000
#define	FSI_GPIO_DRAIN_BITS	20
#define	FSI_GPIO_CRC_SIZE	4
#define	FSI_GPIO_MSG_ID_SIZE		2
#define	FSI_GPIO_MSG_RESPID_SIZE	2
#define	FSI_GPIO_PRIME_SLAVE_CLOCKS	100
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct fsi_master_gpio {
	struct fsi_master	master;
	struct device		*dev;
<<<<<<< HEAD
	struct mutex		cmd_lock;	/* mutex for command ordering */
=======
	spinlock_t		cmd_lock;	/* Lock for commands */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct gpio_desc	*gpio_clk;
	struct gpio_desc	*gpio_data;
	struct gpio_desc	*gpio_trans;	/* Voltage translator */
	struct gpio_desc	*gpio_enable;	/* FSI enable */
	struct gpio_desc	*gpio_mux;	/* Mux control */
<<<<<<< HEAD
	bool			external_mode;
	bool			no_delays;
	uint32_t		last_addr;
	uint8_t			t_send_delay;
	uint8_t			t_echo_delay;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

#define CREATE_TRACE_POINTS
#include <trace/events/fsi_master_gpio.h>

#define to_fsi_master_gpio(m) container_of(m, struct fsi_master_gpio, master)

struct fsi_gpio_msg {
	uint64_t	msg;
	uint8_t		bits;
};

static void clock_toggle(struct fsi_master_gpio *master, int count)
{
	int i;

	for (i = 0; i < count; i++) {
<<<<<<< HEAD
		if (!master->no_delays)
			ndelay(FSI_GPIO_STD_DLY);
		gpiod_set_value(master->gpio_clk, 0);
		if (!master->no_delays)
			ndelay(FSI_GPIO_STD_DLY);
=======
		ndelay(FSI_GPIO_STD_DLY);
		gpiod_set_value(master->gpio_clk, 0);
		ndelay(FSI_GPIO_STD_DLY);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		gpiod_set_value(master->gpio_clk, 1);
	}
}

<<<<<<< HEAD
static int sda_clock_in(struct fsi_master_gpio *master)
{
	int in;

	if (!master->no_delays)
		ndelay(FSI_GPIO_STD_DLY);
	gpiod_set_value(master->gpio_clk, 0);

	/* Dummy read to feed the synchronizers */
	gpiod_get_value(master->gpio_data);

	/* Actual data read */
	in = gpiod_get_value(master->gpio_data);
	if (!master->no_delays)
		ndelay(FSI_GPIO_STD_DLY);
	gpiod_set_value(master->gpio_clk, 1);
=======
static int sda_in(struct fsi_master_gpio *master)
{
	int in;

	ndelay(FSI_GPIO_STD_DLY);
	in = gpiod_get_value(master->gpio_data);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return in ? 1 : 0;
}

static void sda_out(struct fsi_master_gpio *master, int value)
{
	gpiod_set_value(master->gpio_data, value);
}

static void set_sda_input(struct fsi_master_gpio *master)
{
	gpiod_direction_input(master->gpio_data);
	gpiod_set_value(master->gpio_trans, 0);
}

static void set_sda_output(struct fsi_master_gpio *master, int value)
{
	gpiod_set_value(master->gpio_trans, 1);
	gpiod_direction_output(master->gpio_data, value);
}

static void clock_zeros(struct fsi_master_gpio *master, int count)
{
<<<<<<< HEAD
	trace_fsi_master_gpio_clock_zeros(master, count);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	set_sda_output(master, 1);
	clock_toggle(master, count);
}

<<<<<<< HEAD
static void echo_delay(struct fsi_master_gpio *master)
{
	clock_zeros(master, master->t_echo_delay);
}


=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static void serial_in(struct fsi_master_gpio *master, struct fsi_gpio_msg *msg,
			uint8_t num_bits)
{
	uint8_t bit, in_bit;

	set_sda_input(master);

	for (bit = 0; bit < num_bits; bit++) {
<<<<<<< HEAD
		in_bit = sda_clock_in(master);
=======
		clock_toggle(master, 1);
		in_bit = sda_in(master);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		msg->msg <<= 1;
		msg->msg |= ~in_bit & 0x1;	/* Data is active low */
	}
	msg->bits += num_bits;

	trace_fsi_master_gpio_in(master, num_bits, msg->msg);
}

static void serial_out(struct fsi_master_gpio *master,
			const struct fsi_gpio_msg *cmd)
{
	uint8_t bit;
	uint64_t msg = ~cmd->msg;	/* Data is active low */
	uint64_t sda_mask = 0x1ULL << (cmd->bits - 1);
	uint64_t last_bit = ~0;
	int next_bit;

	trace_fsi_master_gpio_out(master, cmd->bits, cmd->msg);

	if (!cmd->bits) {
		dev_warn(master->dev, "trying to output 0 bits\n");
		return;
	}
	set_sda_output(master, 0);

	/* Send the start bit */
	sda_out(master, 0);
	clock_toggle(master, 1);

	/* Send the message */
	for (bit = 0; bit < cmd->bits; bit++) {
		next_bit = (msg & sda_mask) >> (cmd->bits - 1);
		if (last_bit ^ next_bit) {
			sda_out(master, next_bit);
			last_bit = next_bit;
		}
		clock_toggle(master, 1);
		msg <<= 1;
	}
}

static void msg_push_bits(struct fsi_gpio_msg *msg, uint64_t data, int bits)
{
	msg->msg <<= bits;
	msg->msg |= data & ((1ull << bits) - 1);
	msg->bits += bits;
}

static void msg_push_crc(struct fsi_gpio_msg *msg)
{
	uint8_t crc;
	int top;

	top = msg->bits & 0x3;

	/* start bit, and any non-aligned top bits */
	crc = crc4(0, 1 << top | msg->msg >> (msg->bits - top), top + 1);

	/* aligned bits */
	crc = crc4(crc, msg->msg, msg->bits - top);

	msg_push_bits(msg, crc, 4);
}

<<<<<<< HEAD
static bool check_same_address(struct fsi_master_gpio *master, int id,
		uint32_t addr)
{
	/* this will also handle LAST_ADDR_INVALID */
	return master->last_addr == (((id & 0x3) << 21) | (addr & ~0x3));
}

static bool check_relative_address(struct fsi_master_gpio *master, int id,
		uint32_t addr, uint32_t *rel_addrp)
{
	uint32_t last_addr = master->last_addr;
	int32_t rel_addr;

	if (last_addr == LAST_ADDR_INVALID)
		return false;

	/* We may be in 23-bit addressing mode, which uses the id as the
	 * top two address bits. So, if we're referencing a different ID,
	 * use absolute addresses.
	 */
	if (((last_addr >> 21) & 0x3) != id)
		return false;

	/* remove the top two bits from any 23-bit addressing */
	last_addr &= (1 << 21) - 1;

	/* We know that the addresses are limited to 21 bits, so this won't
	 * overflow the signed rel_addr */
	rel_addr = addr - last_addr;
	if (rel_addr > 255 || rel_addr < -256)
		return false;

	*rel_addrp = (uint32_t)rel_addr;

	return true;
}

static void last_address_update(struct fsi_master_gpio *master,
		int id, bool valid, uint32_t addr)
{
	if (!valid)
		master->last_addr = LAST_ADDR_INVALID;
	else
		master->last_addr = ((id & 0x3) << 21) | (addr & ~0x3);
}

/*
 * Encode an Absolute/Relative/Same Address command
 */
static void build_ar_command(struct fsi_master_gpio *master,
		struct fsi_gpio_msg *cmd, uint8_t id,
		uint32_t addr, size_t size, const void *data)
{
	int i, addr_bits, opcode_bits;
	bool write = !!data;
	uint8_t ds, opcode;
	uint32_t rel_addr;
=======
/*
 * Encode an Absolute Address command
 */
static void build_abs_ar_command(struct fsi_gpio_msg *cmd,
		uint8_t id, uint32_t addr, size_t size, const void *data)
{
	bool write = !!data;
	uint8_t ds;
	int i;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	cmd->bits = 0;
	cmd->msg = 0;

<<<<<<< HEAD
	/* we have 21 bits of address max */
	addr &= ((1 << 21) - 1);

	/* cmd opcodes are variable length - SAME_AR is only two bits */
	opcode_bits = 3;

	if (check_same_address(master, id, addr)) {
		/* we still address the byte offset within the word */
		addr_bits = 2;
		opcode_bits = 2;
		opcode = FSI_CMD_SAME_AR;
		trace_fsi_master_gpio_cmd_same_addr(master);

	} else if (check_relative_address(master, id, addr, &rel_addr)) {
		/* 8 bits plus sign */
		addr_bits = 9;
		addr = rel_addr;
		opcode = FSI_CMD_REL_AR;
		trace_fsi_master_gpio_cmd_rel_addr(master, rel_addr);

	} else {
		addr_bits = 21;
		opcode = FSI_CMD_ABS_AR;
		trace_fsi_master_gpio_cmd_abs_addr(master, addr);
	}
=======
	msg_push_bits(cmd, id, 2);
	msg_push_bits(cmd, FSI_GPIO_CMD_ABS_AR, 3);
	msg_push_bits(cmd, write ? 0 : 1, 1);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * The read/write size is encoded in the lower bits of the address
	 * (as it must be naturally-aligned), and the following ds bit.
	 *
	 *	size	addr:1	addr:0	ds
	 *	1	x	x	0
	 *	2	x	0	1
	 *	4	0	1	1
	 *
	 */
	ds = size > 1 ? 1 : 0;
	addr &= ~(size - 1);
	if (size == 4)
		addr |= 1;

<<<<<<< HEAD
	msg_push_bits(cmd, id, 2);
	msg_push_bits(cmd, opcode, opcode_bits);
	msg_push_bits(cmd, write ? 0 : 1, 1);
	msg_push_bits(cmd, addr, addr_bits);
=======
	msg_push_bits(cmd, addr & ((1 << 21) - 1), 21);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	msg_push_bits(cmd, ds, 1);
	for (i = 0; write && i < size; i++)
		msg_push_bits(cmd, ((uint8_t *)data)[i], 8);

	msg_push_crc(cmd);
}

static void build_dpoll_command(struct fsi_gpio_msg *cmd, uint8_t slave_id)
{
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
<<<<<<< HEAD
	msg_push_bits(cmd, FSI_CMD_DPOLL, 3);
	msg_push_crc(cmd);
}

static void build_epoll_command(struct fsi_gpio_msg *cmd, uint8_t slave_id)
{
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
	msg_push_bits(cmd, FSI_CMD_EPOLL, 3);
	msg_push_crc(cmd);
=======
	msg_push_bits(cmd, FSI_GPIO_CMD_DPOLL, 3);
	msg_push_crc(cmd);
}

static void echo_delay(struct fsi_master_gpio *master)
{
	set_sda_output(master, 1);
	clock_toggle(master, FSI_ECHO_DELAY_CLOCKS);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void build_term_command(struct fsi_gpio_msg *cmd, uint8_t slave_id)
{
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
<<<<<<< HEAD
	msg_push_bits(cmd, FSI_CMD_TERM, 6);
=======
	msg_push_bits(cmd, FSI_GPIO_CMD_TERM, 6);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	msg_push_crc(cmd);
}

/*
<<<<<<< HEAD
 * Note: callers rely specifically on this returning -EAGAIN for
 * a CRC error detected in the response. Use other error code
 * for other situations. It will be converted to something else
 * higher up the stack before it reaches userspace.
 */
=======
 * Store information on master errors so handler can detect and clean
 * up the bus
 */
static void fsi_master_gpio_error(struct fsi_master_gpio *master, int error)
{

}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int read_one_response(struct fsi_master_gpio *master,
		uint8_t data_size, struct fsi_gpio_msg *msgp, uint8_t *tagp)
{
	struct fsi_gpio_msg msg;
<<<<<<< HEAD
	unsigned long flags;
	uint32_t crc;
	uint8_t tag;
	int i;

	local_irq_save(flags);

	/* wait for the start bit */
	for (i = 0; i < FSI_MASTER_MTOE_COUNT; i++) {
=======
	uint8_t id, tag;
	uint32_t crc;
	int i;

	/* wait for the start bit */
	for (i = 0; i < FSI_GPIO_MTOE_COUNT; i++) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		msg.bits = 0;
		msg.msg = 0;
		serial_in(master, &msg, 1);
		if (msg.msg)
			break;
	}
<<<<<<< HEAD
	if (i == FSI_MASTER_MTOE_COUNT) {
		dev_dbg(master->dev,
			"Master time out waiting for response\n");
		local_irq_restore(flags);
		return -ETIMEDOUT;
=======
	if (i == FSI_GPIO_MTOE_COUNT) {
		dev_dbg(master->dev,
			"Master time out waiting for response\n");
		fsi_master_gpio_error(master, FSI_GPIO_MTOE);
		return -EIO;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	msg.bits = 0;
	msg.msg = 0;

	/* Read slave ID & response tag */
	serial_in(master, &msg, 4);

<<<<<<< HEAD
	tag = msg.msg & 0x3;

	/* If we have an ACK and we're expecting data, clock the data in too */
	if (tag == FSI_RESP_ACK && data_size)
		serial_in(master, &msg, data_size * 8);

	/* read CRC */
	serial_in(master, &msg, FSI_CRC_SIZE);

	local_irq_restore(flags);
=======
	id = (msg.msg >> FSI_GPIO_MSG_RESPID_SIZE) & 0x3;
	tag = msg.msg & 0x3;

	/* If we have an ACK and we're expecting data, clock the data in too */
	if (tag == FSI_GPIO_RESP_ACK && data_size)
		serial_in(master, &msg, data_size * 8);

	/* read CRC */
	serial_in(master, &msg, FSI_GPIO_CRC_SIZE);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* we have a whole message now; check CRC */
	crc = crc4(0, 1, 1);
	crc = crc4(crc, msg.msg, msg.bits);
	if (crc) {
<<<<<<< HEAD
		/* Check if it's all 1's, that probably means the host is off */
		if (((~msg.msg) & ((1ull << msg.bits) - 1)) == 0)
			return -ENODEV;
		dev_dbg(master->dev, "ERR response CRC msg: 0x%016llx (%d bits)\n",
			msg.msg, msg.bits);
		return -EAGAIN;
=======
		dev_dbg(master->dev, "ERR response CRC\n");
		fsi_master_gpio_error(master, FSI_GPIO_CRC_INVAL);
		return -EIO;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	if (msgp)
		*msgp = msg;
	if (tagp)
		*tagp = tag;

	return 0;
}

static int issue_term(struct fsi_master_gpio *master, uint8_t slave)
{
	struct fsi_gpio_msg cmd;
<<<<<<< HEAD
	unsigned long flags;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	uint8_t tag;
	int rc;

	build_term_command(&cmd, slave);
<<<<<<< HEAD

	local_irq_save(flags);
	serial_out(master, &cmd);
	echo_delay(master);
	local_irq_restore(flags);
=======
	serial_out(master, &cmd);
	echo_delay(master);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	rc = read_one_response(master, 0, NULL, &tag);
	if (rc < 0) {
		dev_err(master->dev,
				"TERM failed; lost communication with slave\n");
		return -EIO;
<<<<<<< HEAD
	} else if (tag != FSI_RESP_ACK) {
=======
	} else if (tag != FSI_GPIO_RESP_ACK) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		dev_err(master->dev, "TERM failed; response %d\n", tag);
		return -EIO;
	}

	return 0;
}

static int poll_for_response(struct fsi_master_gpio *master,
		uint8_t slave, uint8_t size, void *data)
{
	struct fsi_gpio_msg response, cmd;
	int busy_count = 0, rc, i;
<<<<<<< HEAD
	unsigned long flags;
	uint8_t tag;
	uint8_t *data_byte = data;
	int crc_err_retries = 0;
retry:
	rc = read_one_response(master, size, &response, &tag);

	/* Handle retries on CRC errors */
	if (rc == -EAGAIN) {
		/* Too many retries ? */
		if (crc_err_retries++ > FSI_CRC_ERR_RETRIES) {
			/*
			 * Pass it up as a -EIO otherwise upper level will retry
			 * the whole command which isn't what we want here.
			 */
			rc = -EIO;
			goto fail;
		}
		dev_dbg(master->dev,
			 "CRC error retry %d\n", crc_err_retries);
		trace_fsi_master_gpio_crc_rsp_error(master);
		build_epoll_command(&cmd, slave);
		local_irq_save(flags);
		clock_zeros(master, FSI_MASTER_EPOLL_CLOCKS);
		serial_out(master, &cmd);
		echo_delay(master);
		local_irq_restore(flags);
		goto retry;
	} else if (rc)
		goto fail;

	switch (tag) {
	case FSI_RESP_ACK:
=======
	uint8_t tag;
	uint8_t *data_byte = data;

retry:
	rc = read_one_response(master, size, &response, &tag);
	if (rc)
		return rc;

	switch (tag) {
	case FSI_GPIO_RESP_ACK:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (size && data) {
			uint64_t val = response.msg;
			/* clear crc & mask */
			val >>= 4;
			val &= (1ull << (size * 8)) - 1;

			for (i = 0; i < size; i++) {
				data_byte[size-i-1] = val;
				val >>= 8;
			}
		}
		break;
<<<<<<< HEAD
	case FSI_RESP_BUSY:
=======
	case FSI_GPIO_RESP_BUSY:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/*
		 * Its necessary to clock slave before issuing
		 * d-poll, not indicated in the hardware protocol
		 * spec. < 20 clocks causes slave to hang, 21 ok.
		 */
<<<<<<< HEAD
		if (busy_count++ < FSI_MASTER_MAX_BUSY) {
			build_dpoll_command(&cmd, slave);
			local_irq_save(flags);
			clock_zeros(master, FSI_MASTER_DPOLL_CLOCKS);
			serial_out(master, &cmd);
			echo_delay(master);
			local_irq_restore(flags);
=======
		clock_zeros(master, FSI_GPIO_DPOLL_CLOCKS);
		if (busy_count++ < FSI_GPIO_MAX_BUSY) {
			build_dpoll_command(&cmd, slave);
			serial_out(master, &cmd);
			echo_delay(master);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			goto retry;
		}
		dev_warn(master->dev,
			"ERR slave is stuck in busy state, issuing TERM\n");
<<<<<<< HEAD
		local_irq_save(flags);
		clock_zeros(master, FSI_MASTER_DPOLL_CLOCKS);
		local_irq_restore(flags);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		issue_term(master, slave);
		rc = -EIO;
		break;

<<<<<<< HEAD
	case FSI_RESP_ERRA:
		dev_dbg(master->dev, "ERRA received: 0x%x\n", (int)response.msg);
		rc = -EIO;
		break;
	case FSI_RESP_ERRC:
		dev_dbg(master->dev, "ERRC received: 0x%x\n", (int)response.msg);
		trace_fsi_master_gpio_crc_cmd_error(master);
		rc = -EAGAIN;
		break;
	}

	if (busy_count > 0)
		trace_fsi_master_gpio_poll_response_busy(master, busy_count);
 fail:
	/*
	 * tSendDelay clocks, avoids signal reflections when switching
	 * from receive of response back to send of data.
	 */
	local_irq_save(flags);
	clock_zeros(master, master->t_send_delay);
	local_irq_restore(flags);

	return rc;
}

static int send_request(struct fsi_master_gpio *master,
		struct fsi_gpio_msg *cmd)
{
	unsigned long flags;

	if (master->external_mode)
		return -EBUSY;

	local_irq_save(flags);
	serial_out(master, cmd);
	echo_delay(master);
	local_irq_restore(flags);

	return 0;
}

static int fsi_master_gpio_xfer(struct fsi_master_gpio *master, uint8_t slave,
		struct fsi_gpio_msg *cmd, size_t resp_len, void *resp)
{
	int rc = -EAGAIN, retries = 0;

	while ((retries++) < FSI_CRC_ERR_RETRIES) {
		rc = send_request(master, cmd);
		if (rc)
			break;
		rc = poll_for_response(master, slave, resp_len, resp);
		if (rc != -EAGAIN)
			break;
		rc = -EIO;
		dev_warn(master->dev, "ECRC retry %d\n", retries);

		/* Pace it a bit before retry */
		msleep(1);
	}
=======
	case FSI_GPIO_RESP_ERRA:
	case FSI_GPIO_RESP_ERRC:
		dev_dbg(master->dev, "ERR%c received: 0x%x\n",
			tag == FSI_GPIO_RESP_ERRA ? 'A' : 'C',
			(int)response.msg);
		fsi_master_gpio_error(master, response.msg);
		rc = -EIO;
		break;
	}

	/* Clock the slave enough to be ready for next operation */
	clock_zeros(master, FSI_GPIO_PRIME_SLAVE_CLOCKS);
	return rc;
}

static int fsi_master_gpio_xfer(struct fsi_master_gpio *master, uint8_t slave,
		struct fsi_gpio_msg *cmd, size_t resp_len, void *resp)
{
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&master->cmd_lock, flags);
	serial_out(master, cmd);
	echo_delay(master);
	rc = poll_for_response(master, slave, resp_len, resp);
	spin_unlock_irqrestore(&master->cmd_lock, flags);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return rc;
}

static int fsi_master_gpio_read(struct fsi_master *_master, int link,
		uint8_t id, uint32_t addr, void *val, size_t size)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(_master);
	struct fsi_gpio_msg cmd;
<<<<<<< HEAD
	int rc;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (link != 0)
		return -ENODEV;

<<<<<<< HEAD
	mutex_lock(&master->cmd_lock);
	build_ar_command(master, &cmd, id, addr, size, NULL);
	rc = fsi_master_gpio_xfer(master, id, &cmd, size, val);
	last_address_update(master, id, rc == 0, addr);
	mutex_unlock(&master->cmd_lock);

	return rc;
=======
	build_abs_ar_command(&cmd, id, addr, size, NULL);
	return fsi_master_gpio_xfer(master, id, &cmd, size, val);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int fsi_master_gpio_write(struct fsi_master *_master, int link,
		uint8_t id, uint32_t addr, const void *val, size_t size)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(_master);
	struct fsi_gpio_msg cmd;
<<<<<<< HEAD
	int rc;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (link != 0)
		return -ENODEV;

<<<<<<< HEAD
	mutex_lock(&master->cmd_lock);
	build_ar_command(master, &cmd, id, addr, size, val);
	rc = fsi_master_gpio_xfer(master, id, &cmd, 0, NULL);
	last_address_update(master, id, rc == 0, addr);
	mutex_unlock(&master->cmd_lock);

	return rc;
=======
	build_abs_ar_command(&cmd, id, addr, size, val);
	return fsi_master_gpio_xfer(master, id, &cmd, 0, NULL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int fsi_master_gpio_term(struct fsi_master *_master,
		int link, uint8_t id)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(_master);
	struct fsi_gpio_msg cmd;
<<<<<<< HEAD
	int rc;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (link != 0)
		return -ENODEV;

<<<<<<< HEAD
	mutex_lock(&master->cmd_lock);
	build_term_command(&cmd, id);
	rc = fsi_master_gpio_xfer(master, id, &cmd, 0, NULL);
	last_address_update(master, id, false, 0);
	mutex_unlock(&master->cmd_lock);

	return rc;
=======
	build_term_command(&cmd, id);
	return fsi_master_gpio_xfer(master, id, &cmd, 0, NULL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int fsi_master_gpio_break(struct fsi_master *_master, int link)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(_master);
<<<<<<< HEAD
	unsigned long flags;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (link != 0)
		return -ENODEV;

	trace_fsi_master_gpio_break(master);

<<<<<<< HEAD
	mutex_lock(&master->cmd_lock);
	if (master->external_mode) {
		mutex_unlock(&master->cmd_lock);
		return -EBUSY;
	}

	local_irq_save(flags);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	set_sda_output(master, 1);
	sda_out(master, 1);
	clock_toggle(master, FSI_PRE_BREAK_CLOCKS);
	sda_out(master, 0);
	clock_toggle(master, FSI_BREAK_CLOCKS);
	echo_delay(master);
	sda_out(master, 1);
	clock_toggle(master, FSI_POST_BREAK_CLOCKS);

<<<<<<< HEAD
	local_irq_restore(flags);

	last_address_update(master, 0, false, 0);
	mutex_unlock(&master->cmd_lock);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* Wait for logic reset to take effect */
	udelay(200);

	return 0;
}

static void fsi_master_gpio_init(struct fsi_master_gpio *master)
{
<<<<<<< HEAD
	unsigned long flags;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	gpiod_direction_output(master->gpio_mux, 1);
	gpiod_direction_output(master->gpio_trans, 1);
	gpiod_direction_output(master->gpio_enable, 1);
	gpiod_direction_output(master->gpio_clk, 1);
	gpiod_direction_output(master->gpio_data, 1);

	/* todo: evaluate if clocks can be reduced */
<<<<<<< HEAD
	local_irq_save(flags);
	clock_zeros(master, FSI_INIT_CLOCKS);
	local_irq_restore(flags);
}

static void fsi_master_gpio_init_external(struct fsi_master_gpio *master)
{
	gpiod_direction_output(master->gpio_mux, 0);
	gpiod_direction_output(master->gpio_trans, 0);
	gpiod_direction_output(master->gpio_enable, 1);
	gpiod_direction_input(master->gpio_clk);
	gpiod_direction_input(master->gpio_data);
=======
	clock_zeros(master, FSI_INIT_CLOCKS);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int fsi_master_gpio_link_enable(struct fsi_master *_master, int link)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(_master);
<<<<<<< HEAD
	int rc = -EBUSY;

	if (link != 0)
		return -ENODEV;

	mutex_lock(&master->cmd_lock);
	if (!master->external_mode) {
		gpiod_set_value(master->gpio_enable, 1);
		rc = 0;
	}
	mutex_unlock(&master->cmd_lock);

	return rc;
}

static int fsi_master_gpio_link_config(struct fsi_master *_master, int link,
				       u8 t_send_delay, u8 t_echo_delay)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(_master);

	if (link != 0)
		return -ENODEV;

	mutex_lock(&master->cmd_lock);
	master->t_send_delay = t_send_delay;
	master->t_echo_delay = t_echo_delay;
	mutex_unlock(&master->cmd_lock);
=======

	if (link != 0)
		return -ENODEV;
	gpiod_set_value(master->gpio_enable, 1);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

<<<<<<< HEAD
static ssize_t external_mode_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct fsi_master_gpio *master = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE - 1, "%u\n",
			master->external_mode ? 1 : 0);
}

static ssize_t external_mode_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct fsi_master_gpio *master = dev_get_drvdata(dev);
	unsigned long val;
	bool external_mode;
	int err;

	err = kstrtoul(buf, 0, &val);
	if (err)
		return err;

	external_mode = !!val;

	mutex_lock(&master->cmd_lock);

	if (external_mode == master->external_mode) {
		mutex_unlock(&master->cmd_lock);
		return count;
	}

	master->external_mode = external_mode;
	if (master->external_mode)
		fsi_master_gpio_init_external(master);
	else
		fsi_master_gpio_init(master);

	mutex_unlock(&master->cmd_lock);

	fsi_master_rescan(&master->master);

	return count;
}

static DEVICE_ATTR(external_mode, 0664,
		external_mode_show, external_mode_store);

static void fsi_master_gpio_release(struct device *dev)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(dev_to_fsi_master(dev));

	of_node_put(dev_of_node(master->dev));

	kfree(master);
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int fsi_master_gpio_probe(struct platform_device *pdev)
{
	struct fsi_master_gpio *master;
	struct gpio_desc *gpio;
<<<<<<< HEAD
	int rc;

	master = kzalloc(sizeof(*master), GFP_KERNEL);
=======

	master = devm_kzalloc(&pdev->dev, sizeof(*master), GFP_KERNEL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!master)
		return -ENOMEM;

	master->dev = &pdev->dev;
	master->master.dev.parent = master->dev;
<<<<<<< HEAD
	master->master.dev.of_node = of_node_get(dev_of_node(master->dev));
	master->master.dev.release = fsi_master_gpio_release;
	master->last_addr = LAST_ADDR_INVALID;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	gpio = devm_gpiod_get(&pdev->dev, "clock", 0);
	if (IS_ERR(gpio)) {
		dev_err(&pdev->dev, "failed to get clock gpio\n");
<<<<<<< HEAD
		rc = PTR_ERR(gpio);
		goto err_free;
=======
		return PTR_ERR(gpio);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
	master->gpio_clk = gpio;

	gpio = devm_gpiod_get(&pdev->dev, "data", 0);
	if (IS_ERR(gpio)) {
		dev_err(&pdev->dev, "failed to get data gpio\n");
<<<<<<< HEAD
		rc = PTR_ERR(gpio);
		goto err_free;
=======
		return PTR_ERR(gpio);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
	master->gpio_data = gpio;

	/* Optional GPIOs */
	gpio = devm_gpiod_get_optional(&pdev->dev, "trans", 0);
	if (IS_ERR(gpio)) {
		dev_err(&pdev->dev, "failed to get trans gpio\n");
<<<<<<< HEAD
		rc = PTR_ERR(gpio);
		goto err_free;
=======
		return PTR_ERR(gpio);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
	master->gpio_trans = gpio;

	gpio = devm_gpiod_get_optional(&pdev->dev, "enable", 0);
	if (IS_ERR(gpio)) {
		dev_err(&pdev->dev, "failed to get enable gpio\n");
<<<<<<< HEAD
		rc = PTR_ERR(gpio);
		goto err_free;
=======
		return PTR_ERR(gpio);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
	master->gpio_enable = gpio;

	gpio = devm_gpiod_get_optional(&pdev->dev, "mux", 0);
	if (IS_ERR(gpio)) {
		dev_err(&pdev->dev, "failed to get mux gpio\n");
<<<<<<< HEAD
		rc = PTR_ERR(gpio);
		goto err_free;
	}
	master->gpio_mux = gpio;

	/*
	 * Check if GPIO block is slow enought that no extra delays
	 * are necessary. This improves performance on ast2500 by
	 * an order of magnitude.
	 */
	master->no_delays = device_property_present(&pdev->dev, "no-gpio-delays");

	/* Default FSI command delays */
	master->t_send_delay = FSI_SEND_DELAY_CLOCKS;
	master->t_echo_delay = FSI_ECHO_DELAY_CLOCKS;

=======
		return PTR_ERR(gpio);
	}
	master->gpio_mux = gpio;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	master->master.n_links = 1;
	master->master.flags = FSI_MASTER_FLAG_SWCLOCK;
	master->master.read = fsi_master_gpio_read;
	master->master.write = fsi_master_gpio_write;
	master->master.term = fsi_master_gpio_term;
	master->master.send_break = fsi_master_gpio_break;
	master->master.link_enable = fsi_master_gpio_link_enable;
<<<<<<< HEAD
	master->master.link_config = fsi_master_gpio_link_config;
	platform_set_drvdata(pdev, master);
	mutex_init(&master->cmd_lock);

	fsi_master_gpio_init(master);

	rc = device_create_file(&pdev->dev, &dev_attr_external_mode);
	if (rc)
		goto err_free;

	rc = fsi_master_register(&master->master);
	if (rc) {
		device_remove_file(&pdev->dev, &dev_attr_external_mode);
		put_device(&master->master.dev);
		return rc;
	}
	return 0;
 err_free:
	kfree(master);
	return rc;
}



=======
	platform_set_drvdata(pdev, master);
	spin_lock_init(&master->cmd_lock);

	fsi_master_gpio_init(master);

	return fsi_master_register(&master->master);
}


>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int fsi_master_gpio_remove(struct platform_device *pdev)
{
	struct fsi_master_gpio *master = platform_get_drvdata(pdev);

<<<<<<< HEAD
	device_remove_file(&pdev->dev, &dev_attr_external_mode);

=======
	devm_gpiod_put(&pdev->dev, master->gpio_clk);
	devm_gpiod_put(&pdev->dev, master->gpio_data);
	if (master->gpio_trans)
		devm_gpiod_put(&pdev->dev, master->gpio_trans);
	if (master->gpio_enable)
		devm_gpiod_put(&pdev->dev, master->gpio_enable);
	if (master->gpio_mux)
		devm_gpiod_put(&pdev->dev, master->gpio_mux);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	fsi_master_unregister(&master->master);

	return 0;
}

static const struct of_device_id fsi_master_gpio_match[] = {
	{ .compatible = "fsi-master-gpio" },
	{ },
};

static struct platform_driver fsi_master_gpio_driver = {
	.driver = {
		.name		= "fsi-master-gpio",
		.of_match_table	= fsi_master_gpio_match,
	},
	.probe	= fsi_master_gpio_probe,
	.remove = fsi_master_gpio_remove,
};

module_platform_driver(fsi_master_gpio_driver);
MODULE_LICENSE("GPL");
