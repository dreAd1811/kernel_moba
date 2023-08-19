#include <linux/spinlock.h>

#include <asm/checksum.h>
#include <asm/console.h>
#include <asm/page.h>
#include <asm/string.h>
<<<<<<< HEAD
#include <linux/uaccess.h>
=======
#include <asm/uaccess.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <asm-generic/asm-prototypes.h>

extern void __divl(void);
extern void __reml(void);
extern void __divq(void);
extern void __remq(void);
extern void __divlu(void);
extern void __remlu(void);
extern void __divqu(void);
extern void __remqu(void);
