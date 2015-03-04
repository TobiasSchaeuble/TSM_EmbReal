/*----------------------
 trap-demo 
 (c) H.Buchmann FHNW 2009
 $Id$
 TODO easy to use api 
 TODO LED control
------------------------*/
#include "sys/screen.h"                       /* for output on screen */  
#include "io/ascii.h"                             /* for ascii output */
#include "sys/pic.h"     /* for the programmable interrupt controller */
#include "sys/sys.h"                                       /* for sti */
#include "sys/deb.h"

static char ch='0';                  /* will be printed to the screen */

static void trap(unsigned id)               /* called by the hardware */
{
 while(1)
 {
  ascii_put(Screen,'t');
 }
 
 deb_signal0();

 sys_inb(0x64);
 sys_inb(0x60);                 /* empty keyboard ready for next char */
 ch=(ch=='9')?'0':(ch+1);                                /* change ch */
}

static void init()                            /* the interrupt system */
{
 pic_init();
 pic_install(PIC_KBD,trap);
 pic_enable(PIC_KBD);
 sys_sti();                                /* enable interrupt system */
}

int main()
{
 init(); 
 while(1)                              /* the normal thread main loop */
 {
  ascii_put(Screen,ch);
 }
 return 0;
}
