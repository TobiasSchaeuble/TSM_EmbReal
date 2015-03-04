/*------------------
 scancode-demo
 (c) H.Buchmann FHNW 2009
 $Id$
 how to use inb/outb
 http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
--------------------*/
#include "io/ascii.h"
#include "sys/screen.h"
#include "sys/sys.h"  /* for inb/outb */

int main()
{
 ascii_string(Screen,"scancode-demo\n");
 while(1)
 {
  unsigned char status=sys_inb(0x64);
  if (status&1)
     {
      ascii_printf(Screen,"in=%x\n",sys_inb(0x60));
     }
 }
}

