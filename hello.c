#ifndef __KERNEL__
#define __KERNEL__
#endif
#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>

MODULE_AUTHOR("Zifung Yip");
MODULE_LICENSE("GPL");

static int hello_proc_open(struct inode *inode, struct file *file);
static int hello_open(struct inode *inode, struct file *file);
static int hello_release(struct inode *inode, struct file *file);
static int hello_show(struct seq_file *seq, void *offset);
static ssize_t hello_read(struct file *file, char *buf, size_t count, loff_t *f_pos);
static ssize_t hello_write(struct file *file, const char *buf, size_t count, loff_t *f_pos);


static const struct file_operations hello_fops = {
    .llseek = NULL,
    .read = hello_read,
    .write = hello_write,
    .open = hello_open,
    .release = hello_release,
};

static const struct file_operations hello_proc_fops = {
    .open = hello_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static struct miscdevice hello_dev = {
    .minor = 0,
    .name = "hello",
    .fops = &hello_fops,
};

static int hello_proc_open(struct inode *inode, struct file *file) {
    printk("hello_proc_open is called!!!\n");
    return single_open(file, hello_show, NULL);
}

static int hello_open(struct inode *inode, struct file *file) {
    printk("hello_open is called!!!\n");
    return 0;
}

static int hello_release(struct inode *inode, struct file *file) {
    printk("hello_release is called!!!\n");
    return 0;
}

static int hello_show(struct seq_file *seq, void *offset) {
    printk("hello_show is called!!!\n");
    seq_printf(seq, "Hello World!!!\n");
    return 0;
}

static ssize_t hello_read(struct file *file, char *buf, size_t count, loff_t *f_pos) {
    printk("hello_read is called!!!\n");
    return count;
}

static ssize_t hello_write(struct file *file, const char *buf, size_t count, loff_t *f_pos) {
    printk("hello_write is called!!!\n");
    return count;
}

static __init int hello_init(void) {

    printk("booga_init is called!!!\n");
    
    if (misc_register(&hello_dev)) {
        printk(KERN_WARNING "booga: can't get major %d\n", 0);
        return -ENODEV;
    }

    printk("hello device is loaded!!!\n");
    
    proc_create("driver/hello", 0, NULL, &hello_proc_fops);
    return 0;
}

static __exit void hello_exit(void) {
    printk("hello_exit is called!!!\n");
    remove_proc_entry("driver/hello", NULL);
    misc_deregister(&hello_dev);
}

module_init(hello_init);
module_exit(hello_exit);
