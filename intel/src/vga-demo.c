/*-------------------
 vga-demo example of io-mapped
 (c) H.Buchmann FHNW 2010
 $Id$
 www.osdever.net/FreeVGA/vga/crtcreg.htm
 typical access
  - two registers 
     . index
     . value
---------------------*/
#include "sys/sys.h" /* for sys_inb/sys_outb */
#define CRTADDRESS 0x3d4
#define CRTVALUE   0x3d5

typedef unsigned char byte;

static void set(byte val,byte reg)
{
 sys_outb(reg,CRTADDRESS); /* select register */
 sys_outb(val,CRTVALUE);         /* set value */
}

static byte get(byte reg)
{
 sys_outb(reg,CRTADDRESS); /* select register */
 return sys_inb(CRTVALUE);       /* set value */
}


/*
 row 0
     1  <--------- start register
     2
     3
     4
     5  <--------- end register
     
*/
int main()
{
 /* set cursor */
 set (0,0x0a);      /* cursor start register */
 set(31,0x0b);         /* cursor end register */
 while(1)
 {
 }
 return 0;
}
