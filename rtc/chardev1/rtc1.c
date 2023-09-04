#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/uaccess.h>

static int rtc_open(struct inode* inode, struct file* fp)
{
    printk("%s...\n", __func__);
    return 0;
}

static int rtc_release(struct inode* inode, struct file* fp)
{
    printk("%s...\n", __func__);
    return 0;
}

static ssize_t rtc_read(struct file* fp, char __user* buf, size_t size, loff_t* pos)
{
    printk("%s...\n", __func__);
    return 0;
}

static ssize_t rtc_write(struct file* fp, const char __user* buf, size_t size, loff_t* pos)
{
    printk("%s...\n", __func__);
    return 0;
}

static const struct file_operations rtc_fops = {
    .owner = THIS_MODULE,
    .read = rtc_read,
    .write = rtc_write,
    .open = rtc_open,
    .release = rtc_release,
};

static int __init rtc_init(void)
{
    int ret = 0;

    ret = register_chrdev(223, "rtc1-demo", &rtc_fops);
    if (ret < 0) {
        printk("Register char module: rtc failed..\n");
        return 0;
    } else {
        printk("Register char module: rtc success!\n");
    }
    return 0;
}

static void __exit rtc_exit(void)
{
    printk("Goodbye char module: rtc!\n");
    unregister_chrdev(223, "rtc1-demo");
}

module_init(rtc_init);
module_exit(rtc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vast-Jay@author");