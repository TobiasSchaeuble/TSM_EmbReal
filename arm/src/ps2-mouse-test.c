/*-------------------------
  kmi-test keyboard mouse interface
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/pl050-keyboard-mouse.pdf
---------------------------*/
#include "stdio.h"

volatile struct
{
       unsigned CR;
 const unsigned STAT;
       unsigned DAT;
       unsigned CLKDIV;
       unsigned IR;
} KMI1;

typedef enum
{
 LE_BUTTON =(1<<0),
 RI_BUTTON =(1<<1),
 MI_BUTTON =(1<<2)
} Button;

static int      xPos=0;
static int      yPos=0;
static unsigned button=0; 


static void show()
{
 static const char* Buttons[]={ /* LMR       mrl */ 
                             "---",  /* 000 */
			     "L--",  /* 001 */
			     "--R",  /* 010 */
			     "L-R",  /* 011 */
			     "-M-",  /* 100 */
			     "LM-",  /* 101 */
			     "-MR",  /* 110 */
			     "LMR"   /* 111 */
                         };
 printf("%s\t%d\t%d\n",Buttons[button],xPos,yPos);
}

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
 unsigned ack=read();
 printf("set %x\t%x\n",v,ack);
}

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
 button=0x7&b0;
// printf("%d\t%d\n",xPos,yPos);
 show();
}


int main()
{
 KMI1.CR|=(1<<2);
 set(0xf4); /* enable */
 set(0xea); /* set stream */
 while(1)
 {
  data();
 }
 return 0;
}
  
