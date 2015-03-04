/*------------------------
  kbdc-demo keyboard controller demo
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] http://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html
--------------------------*/
#include "sys/sys.h" /* for sys_inb sys_outb */
#include "stdio.h"

typedef unsigned char byte;

void out60(byte v)
{
 printf("out60\n");
 while(sys_inb(0x64)&(1<<1)){} /* wait until ready to write */
 sys_outb(v,0x60);
}

void out64(byte v)
{
 printf("out64\n");
 while(sys_inb(0x64)&(1<<1)){} /* wait until ready to write */
 sys_outb(v,0x64);
}

byte in60()
{
 printf("in60\n");
 while((sys_inb(0x64)&(1<<0))==0){} /* wait until ready to write */
 return sys_inb(0x60);
}

void main()
{
 out60(0xed); /* led */
 printf("a=%x\n",in60());
 out60(0xff);
 printf("a=%x\n",in60());
 printf("a=%x\n",in60());
 
}
  
