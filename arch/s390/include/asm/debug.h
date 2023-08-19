/* SPDX-License-Identifier: GPL-2.0 */
/*
 *   S/390 debug facility
 *
 *    Copyright IBM Corp. 1999, 2000
 */
#ifndef DEBUG_H
#define DEBUG_H

#include <linux/string.h>
#include <linux/spinlock.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/refcount.h>
#include <uapi/asm/debug.h>

<<<<<<< HEAD
#define DEBUG_MAX_LEVEL		   6  /* debug levels range from 0 to 6 */
#define DEBUG_OFF_LEVEL		   -1 /* level where debug is switched off */
#define DEBUG_FLUSH_ALL		   -1 /* parameter to flush all areas */
#define DEBUG_MAX_VIEWS		   10 /* max number of views in proc fs */
#define DEBUG_MAX_NAME_LEN	   64 /* max length for a debugfs file name */
#define DEBUG_DEFAULT_LEVEL	   3  /* initial debug level */

#define DEBUG_DIR_ROOT "s390dbf" /* name of debug root directory in proc fs */

#define DEBUG_DATA(entry) (char *)(entry + 1) /* data is stored behind */
					      /* the entry information */
=======
#define DEBUG_MAX_LEVEL            6  /* debug levels range from 0 to 6 */
#define DEBUG_OFF_LEVEL            -1 /* level where debug is switched off */
#define DEBUG_FLUSH_ALL            -1 /* parameter to flush all areas */
#define DEBUG_MAX_VIEWS            10 /* max number of views in proc fs */
#define DEBUG_MAX_NAME_LEN         64 /* max length for a debugfs file name */
#define DEBUG_DEFAULT_LEVEL        3  /* initial debug level */

#define DEBUG_DIR_ROOT "s390dbf" /* name of debug root directory in proc fs */

#define DEBUG_DATA(entry) (char*)(entry + 1) /* data is stored behind */
                                             /* the entry information */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

typedef struct __debug_entry debug_entry_t;

struct debug_view;

<<<<<<< HEAD
typedef struct debug_info {
	struct debug_info *next;
	struct debug_info *prev;
	refcount_t ref_count;
	spinlock_t lock;
=======
typedef struct debug_info {	
	struct debug_info* next;
	struct debug_info* prev;
	refcount_t ref_count;
	spinlock_t lock;			
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int level;
	int nr_areas;
	int pages_per_area;
	int buf_size;
<<<<<<< HEAD
	int entry_size;
	debug_entry_t ***areas;
	int active_area;
	int *active_pages;
	int *active_entries;
	struct dentry *debugfs_root_entry;
	struct dentry *debugfs_entries[DEBUG_MAX_VIEWS];
	struct debug_view *views[DEBUG_MAX_VIEWS];
=======
	int entry_size;	
	debug_entry_t*** areas;
	int active_area;
	int *active_pages;
	int *active_entries;
	struct dentry* debugfs_root_entry;
	struct dentry* debugfs_entries[DEBUG_MAX_VIEWS];
	struct debug_view* views[DEBUG_MAX_VIEWS];	
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	char name[DEBUG_MAX_NAME_LEN];
	umode_t mode;
} debug_info_t;

<<<<<<< HEAD
typedef int (debug_header_proc_t) (debug_info_t *id,
				   struct debug_view *view,
				   int area,
				   debug_entry_t *entry,
				   char *out_buf);

typedef int (debug_format_proc_t) (debug_info_t *id,
				   struct debug_view *view, char *out_buf,
				   const char *in_buf);
typedef int (debug_prolog_proc_t) (debug_info_t *id,
				   struct debug_view *view,
				   char *out_buf);
typedef int (debug_input_proc_t) (debug_info_t *id,
				  struct debug_view *view,
				  struct file *file,
				  const char __user *user_buf,
				  size_t in_buf_size, loff_t *offset);

int debug_dflt_header_fn(debug_info_t *id, struct debug_view *view,
			 int area, debug_entry_t *entry, char *out_buf);

struct debug_view {
	char name[DEBUG_MAX_NAME_LEN];
	debug_prolog_proc_t *prolog_proc;
	debug_header_proc_t *header_proc;
	debug_format_proc_t *format_proc;
	debug_input_proc_t  *input_proc;
	void		    *private_data;
=======
typedef int (debug_header_proc_t) (debug_info_t* id,
				   struct debug_view* view,
				   int area,
				   debug_entry_t* entry,
				   char* out_buf);

typedef int (debug_format_proc_t) (debug_info_t* id,
				   struct debug_view* view, char* out_buf,
				   const char* in_buf);
typedef int (debug_prolog_proc_t) (debug_info_t* id,
				   struct debug_view* view,
				   char* out_buf);
typedef int (debug_input_proc_t) (debug_info_t* id,
				  struct debug_view* view,
				  struct file* file,
				  const char __user *user_buf,
				  size_t in_buf_size, loff_t* offset);

int debug_dflt_header_fn(debug_info_t* id, struct debug_view* view,
		         int area, debug_entry_t* entry, char* out_buf);						
				
struct debug_view {
	char name[DEBUG_MAX_NAME_LEN];
	debug_prolog_proc_t* prolog_proc;
	debug_header_proc_t* header_proc;
	debug_format_proc_t* format_proc;
	debug_input_proc_t*  input_proc;
	void*                private_data;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

extern struct debug_view debug_hex_ascii_view;
extern struct debug_view debug_raw_view;
extern struct debug_view debug_sprintf_view;

/* do NOT use the _common functions */

<<<<<<< HEAD
debug_entry_t *debug_event_common(debug_info_t *id, int level,
				  const void *data, int length);

debug_entry_t *debug_exception_common(debug_info_t *id, int level,
				      const void *data, int length);
=======
debug_entry_t* debug_event_common(debug_info_t* id, int level, 
                                  const void* data, int length);

debug_entry_t* debug_exception_common(debug_info_t* id, int level, 
                                      const void* data, int length);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* Debug Feature API: */

debug_info_t *debug_register(const char *name, int pages, int nr_areas,
<<<<<<< HEAD
			     int buf_size);
=======
                             int buf_size);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

debug_info_t *debug_register_mode(const char *name, int pages, int nr_areas,
				  int buf_size, umode_t mode, uid_t uid,
				  gid_t gid);

<<<<<<< HEAD
void debug_unregister(debug_info_t *id);

void debug_set_level(debug_info_t *id, int new_level);
=======
void debug_unregister(debug_info_t* id);

void debug_set_level(debug_info_t* id, int new_level);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

void debug_set_critical(void);
void debug_stop_all(void);

<<<<<<< HEAD
static inline bool debug_level_enabled(debug_info_t *id, int level)
=======
static inline bool debug_level_enabled(debug_info_t* id, int level)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	return level <= id->level;
}

<<<<<<< HEAD
static inline debug_entry_t *debug_event(debug_info_t *id, int level,
					 void *data, int length)
{
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
	return debug_event_common(id, level, data, length);
}

static inline debug_entry_t *debug_int_event(debug_info_t *id, int level,
					     unsigned int tag)
{
	unsigned int t = tag;

	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
	return debug_event_common(id, level, &t, sizeof(unsigned int));
}

static inline debug_entry_t *debug_long_event(debug_info_t *id, int level,
					      unsigned long tag)
{
	unsigned long t = tag;

	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
	return debug_event_common(id, level, &t, sizeof(unsigned long));
}

static inline debug_entry_t *debug_text_event(debug_info_t *id, int level,
					      const char *txt)
{
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
	return debug_event_common(id, level, txt, strlen(txt));
=======
static inline debug_entry_t*
debug_event(debug_info_t* id, int level, void* data, int length)
{
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
        return debug_event_common(id,level,data,length);
}

static inline debug_entry_t*
debug_int_event(debug_info_t* id, int level, unsigned int tag)
{
        unsigned int t=tag;
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
        return debug_event_common(id,level,&t,sizeof(unsigned int));
}

static inline debug_entry_t *
debug_long_event (debug_info_t* id, int level, unsigned long tag)
{
        unsigned long t=tag;
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
        return debug_event_common(id,level,&t,sizeof(unsigned long));
}

static inline debug_entry_t*
debug_text_event(debug_info_t* id, int level, const char* txt)
{
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
        return debug_event_common(id,level,txt,strlen(txt));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*
 * IMPORTANT: Use "%s" in sprintf format strings with care! Only pointers are
 * stored in the s390dbf. See Documentation/s390/s390dbf.txt for more details!
 */
extern debug_entry_t *
__debug_sprintf_event(debug_info_t *id, int level, char *string, ...)
	__attribute__ ((format(printf, 3, 4)));

#define debug_sprintf_event(_id, _level, _fmt, ...)			\
({									\
	debug_entry_t *__ret;						\
	debug_info_t *__id = _id;					\
	int __level = _level;						\
<<<<<<< HEAD
									\
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if ((!__id) || (__level > __id->level))				\
		__ret = NULL;						\
	else								\
		__ret = __debug_sprintf_event(__id, __level,		\
					      _fmt, ## __VA_ARGS__);	\
	__ret;								\
})

<<<<<<< HEAD
static inline debug_entry_t *debug_exception(debug_info_t *id, int level,
					     void *data, int length)
{
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
	return debug_exception_common(id, level, data, length);
}

static inline debug_entry_t *debug_int_exception(debug_info_t *id, int level,
						 unsigned int tag)
{
	unsigned int t = tag;

	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
	return debug_exception_common(id, level, &t, sizeof(unsigned int));
}

static inline debug_entry_t *debug_long_exception (debug_info_t *id, int level,
						   unsigned long tag)
{
	unsigned long t = tag;

	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
	return debug_exception_common(id, level, &t, sizeof(unsigned long));
}

static inline debug_entry_t *debug_text_exception(debug_info_t *id, int level,
						  const char *txt)
{
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
	return debug_exception_common(id, level, txt, strlen(txt));
=======
static inline debug_entry_t*
debug_exception(debug_info_t* id, int level, void* data, int length)
{
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
        return debug_exception_common(id,level,data,length);
}

static inline debug_entry_t*
debug_int_exception(debug_info_t* id, int level, unsigned int tag)
{
        unsigned int t=tag;
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
        return debug_exception_common(id,level,&t,sizeof(unsigned int));
}

static inline debug_entry_t *
debug_long_exception (debug_info_t* id, int level, unsigned long tag)
{
        unsigned long t=tag;
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
        return debug_exception_common(id,level,&t,sizeof(unsigned long));
}

static inline debug_entry_t*
debug_text_exception(debug_info_t* id, int level, const char* txt)
{
	if ((!id) || (level > id->level) || (id->pages_per_area == 0))
		return NULL;
        return debug_exception_common(id,level,txt,strlen(txt));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*
 * IMPORTANT: Use "%s" in sprintf format strings with care! Only pointers are
 * stored in the s390dbf. See Documentation/s390/s390dbf.txt for more details!
 */
extern debug_entry_t *
__debug_sprintf_exception(debug_info_t *id, int level, char *string, ...)
	__attribute__ ((format(printf, 3, 4)));

#define debug_sprintf_exception(_id, _level, _fmt, ...)			\
({									\
	debug_entry_t *__ret;						\
	debug_info_t *__id = _id;					\
	int __level = _level;						\
<<<<<<< HEAD
									\
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if ((!__id) || (__level > __id->level))				\
		__ret = NULL;						\
	else								\
		__ret = __debug_sprintf_exception(__id, __level,	\
						  _fmt, ## __VA_ARGS__);\
	__ret;								\
})

<<<<<<< HEAD
int debug_register_view(debug_info_t *id, struct debug_view *view);
int debug_unregister_view(debug_info_t *id, struct debug_view *view);
=======
int debug_register_view(debug_info_t* id, struct debug_view* view);
int debug_unregister_view(debug_info_t* id, struct debug_view* view);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/*
   define the debug levels:
   - 0 No debugging output to console or syslog
<<<<<<< HEAD
   - 1 Log internal errors to syslog, ignore check conditions
=======
   - 1 Log internal errors to syslog, ignore check conditions 
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
   - 2 Log internal errors and check conditions to syslog
   - 3 Log internal errors to console, log check conditions to syslog
   - 4 Log internal errors and check conditions to console
   - 5 panic on internal errors, log check conditions to console
   - 6 panic on both, internal errors and check conditions
 */

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 4
#endif

#define INTERNAL_ERRMSG(x,y...) "E" __FILE__ "%d: " x, __LINE__, y
#define INTERNAL_WRNMSG(x,y...) "W" __FILE__ "%d: " x, __LINE__, y
#define INTERNAL_INFMSG(x,y...) "I" __FILE__ "%d: " x, __LINE__, y
#define INTERNAL_DEBMSG(x,y...) "D" __FILE__ "%d: " x, __LINE__, y

#if DEBUG_LEVEL > 0
<<<<<<< HEAD
#define PRINT_DEBUG(x...)	printk(KERN_DEBUG PRINTK_HEADER x)
#define PRINT_INFO(x...)	printk(KERN_INFO PRINTK_HEADER x)
#define PRINT_WARN(x...)	printk(KERN_WARNING PRINTK_HEADER x)
#define PRINT_ERR(x...)		printk(KERN_ERR PRINTK_HEADER x)
#define PRINT_FATAL(x...)	panic(PRINTK_HEADER x)
#else
#define PRINT_DEBUG(x...)	printk(KERN_DEBUG PRINTK_HEADER x)
#define PRINT_INFO(x...)	printk(KERN_DEBUG PRINTK_HEADER x)
#define PRINT_WARN(x...)	printk(KERN_DEBUG PRINTK_HEADER x)
#define PRINT_ERR(x...)		printk(KERN_DEBUG PRINTK_HEADER x)
#define PRINT_FATAL(x...)	printk(KERN_DEBUG PRINTK_HEADER x)
#endif /* DASD_DEBUG */

#endif /* DEBUG_H */
=======
#define PRINT_DEBUG(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
#define PRINT_INFO(x...) printk ( KERN_INFO PRINTK_HEADER x )
#define PRINT_WARN(x...) printk ( KERN_WARNING PRINTK_HEADER x )
#define PRINT_ERR(x...) printk ( KERN_ERR PRINTK_HEADER x )
#define PRINT_FATAL(x...) panic ( PRINTK_HEADER x )
#else
#define PRINT_DEBUG(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
#define PRINT_INFO(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
#define PRINT_WARN(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
#define PRINT_ERR(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
#define PRINT_FATAL(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
#endif				/* DASD_DEBUG */

#endif				/* DEBUG_H */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
