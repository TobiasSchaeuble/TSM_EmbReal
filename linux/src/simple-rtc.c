/*---------------------------
  simple-module
  (c) H.Buchmann FHNW 2012
  $Id$
  see http://tldp.org/LDP/lkmpg/2.6/html
  Documentation/kbuild/modules.txt
 ----------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

#define DEVICE "simple_rtc"

static unsigned char read(unsigned reg)
{
 outb(reg,0x70);
 return inb(0x71);
}

/* --------------- taken from linux-kernel include/linux/mc146818rtc.h */
#define RTC_SECONDS		0
#define RTC_SECONDS_ALARM	1
#define RTC_MINUTES		2
#define RTC_MINUTES_ALARM	3
#define RTC_HOURS		4
#define RTC_HOURS_ALARM		5
/* RTC_*_alarm is always true if 2 MSBs are set */
# define RTC_ALARM_DONT_CARE 	0xC0

#define RTC_DAY_OF_WEEK		6
#define RTC_DAY_OF_MONTH	7
#define RTC_MONTH		8
#define RTC_YEAR		9

/* control registers - Moto names
 */
#define RTC_REG_A		10
#define RTC_REG_B		11
#define RTC_REG_C		12
#define RTC_REG_D		13

static char time[3];     /* ss:mm:hh */

static void latch_time()
{
 time[0]=read(RTC_SECONDS);
 time[1]=read(RTC_MINUTES);
 time[2]=read(RTC_HOURS);
}

static ssize_t rtc_read(struct file* src,
                        char __user *  buffer,
			size_t len,
			loff_t* ofs)
{
 unsigned j=0; /* index in buffer */
 if (*ofs==0) latch_time();
 while((j<len) && (*ofs<3))
 {
  buffer[j++]=time[(*ofs)++];
 }
 return j;
}

static struct file_operations fops =  /* the call backs */
{
  read:rtc_read
};


static int Major;
static int __init rtc_init()  /* local call-back function */
	                              /* called when loading */
{
 Major = register_chrdev(0, DEVICE, &fops);
 printk(KERN_INFO "init: " DEVICE " Major=%d\n",Major);
            /*   ^ concatenation */
 return 0;
}

static void __exit rtc_exit()  /* local call-back function */
                                     /* called when unloading */
{
 unregister_chrdev(Major,DEVICE);
 printk(KERN_INFO "exit: simple-rtc\n");
}

                                                 /* register */
module_init(rtc_init);
module_exit(rtc_exit);
