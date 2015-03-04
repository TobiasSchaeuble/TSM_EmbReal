/*----------------------
 common-access 
 (c) H.Buchmann FHNW 2009
 $Id$
------------------------*/
#include "sys/screen.h"                       /* for output on screen */  
#include "io/ascii.h"                             /* for ascii output */
#include "sys/pic.h"     /* for the programmable interrupt controller */
#include "sys/sys.h"                                       /* for sti */

static volatile unsigned count=0;

static void trap(unsigned id)
{
 sys_inb(0x64);
 sys_inb(0x60);                 /* empty keyboard ready for next char */
 ++count;
}

static void init()                            /* the interrupt system */
{
 pic_init();
 pic_install(1,trap);
 pic_enable(1);
 sys_sti();
}

int main()
{
 init(); 
 while(1)                              /* the normal thread main loop */
 {
  unsigned v=count;
  ++v;
  if (v!=(count+1)) ascii_put(Screen,'x');
  count=v;
 }
 return 0;
}

