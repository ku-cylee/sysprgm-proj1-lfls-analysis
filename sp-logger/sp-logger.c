#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define PROC_DIRNAME   "sp-logger"
#define PROC_FILENAME  "sp-logger"

typedef struct {
	unsigned int blocknum;
	char* fsname;
	long timestamp;
} BlockInfo;

static int queueIndex = 0;

#define QUEUE_SIZE 3000
extern BlockInfo blockQueue[QUEUE_SIZE];

static struct proc_dir_entry *proc_dir;
static struct proc_dir_entry *proc_file;

static int sl_open(struct inode *inode, struct file *file) {
	return 0;
}

static ssize_t sl_read(struct file *file, char __user *user_buffer,
					   size_t count, loff_t *ppos) {
	if (queueIndex >= QUEUE_SIZE) {
		queueIndex = 0;
		return 0;
	}

	BlockInfo block = blockQueue[queueIndex];
	if (block.timestamp == NULL) {
		queueIndex = 0;
		return 0;
	}

	int len = sprintf(user_buffer, "idx: %d || time: %ld || fsname: %s || blocknum: %u\n", queueIndex, block.timestamp, block.fsname, block.blocknum);
	queueIndex++;

	return len;
}

static const struct file_operations sl_fops = {
	.owner = THIS_MODULE,
	.open = sl_open,
	.read = sl_read,
};

static int __init sl_init(void) {
	proc_dir = proc_mkdir(PROC_DIRNAME, NULL);
	proc_file = proc_create(PROC_FILENAME, 0777, proc_dir, &sl_fops);
	return 0;
}

static void __exit sl_exit(void) {
	remove_proc_entry(PROC_FILENAME, proc_dir);
	remove_proc_entry(PROC_DIRNAME, NULL);
	return;
}

module_init(sl_init);
module_exit(sl_exit);

MODULE_AUTHOR("KU");
MODULE_DESCRIPTION("LFS Profiling Module");
MODULE_LICENSE("GPL");
MODULE_VERSION("NEW");
