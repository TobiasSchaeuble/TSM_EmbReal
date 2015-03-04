/*----------------------------
  mouse.c PS2 implementation
  (c) H.Buchmann FHNW 2012
  $Id$
------------------------------*/
#include "io/mouse.h"

volatile struct
{
       unsigned CR;
 const unsigned STAT;
       unsigned DAT;
       unsigned CLKDIV;
       unsigned IR;
} KMI1;

/* ps2 interface */
static void cmd(unsigned v)
{
 while((KMI1.STAT&(1<<6))==0){}
 KMI1.DAT=v;
}

static volatile unsigned read()
{
 while((KMI1.STAT&(1<<4))==0){}
 return KMI1.DAT;
}

static void set(unsigned v)
{
 cmd(v);
 read(); /* expecting ack */
}

static int xPos;
static int yPos;

static OnMouse mouse=0;

static void data()
{
 int b0=read();
 int b1=read();
 int b2=read();
 /* fedcba9876543210fedcba9876543210 */
 /* 1xxxxxxxx */
 int dx=(((0x1&(b0>>4))<<31)|(b1<<0x17))>>0x17;
 int dy=(((0x1&(b0>>5))<<31)|(b2<<0x17))>>0x17;

 xPos+=dx;
 yPos+=dy;
 if (mouse) mouse(xPos,yPos,0x7&b0);
}

void mouse_register(OnMouse m)
{
 mouse=m;
}

void mouse_enable()
{
 KMI1.CR|=(1<<2);
 set(0xf4); /* enable */
 set(0xea); /* set stream */
 while(1) /* polling */
 {
  data();
 }
}
