#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

typedef volatile struct {
	unsigned long RTCDR;
	unsigned long RTCMR;
	unsigned long RTCLR;
	unsigned long RTCCR;
	unsigned long RTCIMSC;
	unsigned long RTCRIS;
	unsigned long RTCMIS;
	unsigned long RTCICR;
} rtc_reg_t;

struct rtc_time{
	unsigned int year;
	unsigned int mon;
	unsigned int day;
	unsigned int hour;
	unsigned int min;
	unsigned int sec;
};

#define RTC_BASE 0x10017000 

static volatile rtc_reg_t* regs = NULL;
static unsigned long cur_time = 0;
static struct rtc_time tm;

static void rtc_time_translate(void){

	tm.hour = (cur_time % 8600) % 3600;
	tm.min = (cur_time %3600) % 60;
	tm.sec = cur_time % 60;
}


static int rtc_open(struct inode* inode, struct file* fp){
	printk("%s...\n",__func__);
	return 0;
}

static int rtc_release(struct inode* inode,struct file* fp){
	printk("%s...\n",__func__);
	return 0;
}

static ssize_t rtc_read(struct file* fp, char __user* buf, size_t size, loff_t* pos){
	cur_time = regs->RTCDR;
	rtc_time_translate();
	if(copy_to_user(buf,&tm,sizeof(struct rtc_time)) != 0){
		printk("read error!\n");
		return -1;
	}
	return 0;
}

static ssize_t rtc_write(struct file* fp, const char __user* buf, size_t size, loff_t* pos){
	int count = 0;
	return count;		
}

static const struct file_operations rtc_fops = {
	.owner = THIS_MODULE,
	.read = rtc_read,
	.write = rtc_write,
	.open = rtc_open,
	.release = rtc_release,
};

static int __init rtc_init(void){
	int ret = 0;

	ret = register_chrdev(223,"rtc-demo1",&rtc_fops);
	if(ret < 0){
		printk("Rigester char module: rtc failed..\n");
		return 0;
	}else{
		printk("Register char module: rtc success\n");
	}
	return 0;
}

static void __exit rtc_exit(void){
	printk("Goodbye char module: rtc!\n");
	unregister_chrdev(223,"rtc-demo1");
}

module_init(rtc_init);
module_exit(rtc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("vast-jay@qq.com");




