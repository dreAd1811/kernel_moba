/* SPDX-License-Identifier: GPL-2.0 */
#define EOF	(-1)

<<<<<<< HEAD
=======
#define printf	xmon_printf
#define putchar	xmon_putchar

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
extern void xmon_set_pagination_lpp(unsigned long lpp);
extern void xmon_start_pagination(void);
extern void xmon_end_pagination(void);
extern int xmon_putchar(int c);
extern void xmon_puts(const char *);
extern char *xmon_gets(char *, int);
<<<<<<< HEAD
extern __printf(1, 2) void xmon_printf(const char *fmt, ...);

#define printf	xmon_printf
#define putchar	xmon_putchar
=======
extern void xmon_printf(const char *, ...);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
