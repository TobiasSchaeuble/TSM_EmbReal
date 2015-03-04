/*----------------------
 kbc-demo (keyboard controller)
 (c) H.Buchmann FHNW 2009
 $Id$
 TODO easy to use api 
 TODO LED control
------------------------*/
#include "sys/screen.h"                       /* for output on screen */  
#include "io/ascii.h"                             /* for ascii output */
#include "sys/pic.h"     /* for the programmable interrupt controller */
#include "sys/sys.h"                                       /* for sti */

static char ch='0';
static void trap(unsigned id)
{
 sys_inb(0x64);
 sys_inb(0x60);
 ch=(ch=='9')?'0':(ch+1);
}

int main()
{
 pic_init();
 pic_install(1,trap);
 pic_enable(1);
 sys_sti();
 
 while(1)
 {
  ascii_put(Screen,ch);
 }
 return 0;
}

