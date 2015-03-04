/*---------------------------
 simple-device
 (c) H.Buchmann FHNW 2012
 $Id$
 see http://tldp.org/LDP/lkmpg/2.6/html
 ---------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h> /* not the posix string */

#define DEVICE "simple_device"

static int Major;  

static const char      Msg[] =DEVICE " file='" __FILE__ "' made on: '" __DATE__ "'\n";
static const unsigned  MsgLen=sizeof(Msg);  /* incl terminating zero */

/*kernelspace  -> userspace*/
static ssize_t simple_read(struct file* src,
                        char __user *  buffer,
			size_t len, 
			loff_t* ofs)
{
 unsigned j=0;              /* index in buffer */
 while((j<len)&&(*ofs < MsgLen))
 {
  buffer[j++]=Msg[(*ofs)++];  
 }
 return j;
}

/* userspace -> kernelspace */
static ssize_t simple_write(struct file* dst, 
                     const char __user* buffer, 
		     size_t len, 
		     loff_t* ofs)
{
 print_hex_dump(KERN_INFO," ",0,16,1,buffer,len,1);
 return len;
}

/* see linux/fs.h */
static struct file_operations fops =  /* the call backs */
{
  read:simple_read,
 write:simple_write
};

/* register/deregister of module */
static int __init _init_(void)    /* local call-back function */
                            /* the compiler wants this (void) */
{
 Major = register_chrdev(0, DEVICE, &fops);
 printk(KERN_INFO "init: " DEVICE " Major=%d\n",Major);
            /*   ^ concatenation */
 return 0;
}

static void __exit _exit_(void)   /* local call-back function */
                            /* the compiler wants this (void) */
{
 unregister_chrdev(Major,DEVICE);
 printk(KERN_INFO "exit: " DEVICE "\n");
}

module_init(_init_);
module_exit(_exit_);
