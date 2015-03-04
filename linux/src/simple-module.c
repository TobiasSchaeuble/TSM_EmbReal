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


static int __init simple_init()  /* local call-back function */
	                              /* called when loading */
{
 printk(KERN_INFO "init: simple-module\n");
            /*   ^ concatentaion */
 return 0;
}

static void __exit simple_exit()  /* local call-back function */
                                     /* called when unloading */
{
 printk(KERN_INFO "exit: simple-module\n");
}

                                                 /* register */
module_init(simple_init);
module_exit(simple_exit);
