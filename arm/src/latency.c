/*----------------------
  interrupt latency
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/DUI0159B_integratorcp_1_0_ug.pdf
------------------------*/
#include "stdio.h"
#include "sys/sys.h"
                                       /* same struct for FIQ struct */
volatile struct                                     /* see [3] 3.6.1 */
{
 const unsigned STAT;
 const unsigned RSTAT;
 unsigned ENSET;
 unsigned ENCLR;
}* PRIMIRQ = 0x14000000;

volatile struct /* [1] 4.9.2 */
{
       unsigned load;
 const unsigned value;
       unsigned control;
       unsigned intClr;
 const unsigned RIS;
 const unsigned MIS;
       unsigned BGload;
}* TIMER0 = 0x13000000;

#define LOAD (1<<25)
void myOnIRQ() __attribute__((interrupt("IRQ")));

void myOnIRQ()
{
 TIMER0->intClr=1;
 unsigned val=TIMER0->value;
 printf("----tick--------%x\n",LOAD-val);
}

typedef void (OnIRQ)();

extern OnIRQ* onIRQ; /* defined in big-bang.S */

void main()
{
 onIRQ=myOnIRQ; 
 TIMER0->load=LOAD;
 TIMER0->control=(0<<0)| /* wrapping mode */
                 (1<<1)| /* 32 bit counter */
		 (0<<2)| /* prescale 0 */
		 (1<<5)| /* IE */
		 (1<<6)| /* periodic */
		 (1<<7); /* enable */
 sys_setCPSR(sys_getCPSR()&~(1<<7)); /* enable IRQ */
 PRIMIRQ->ENSET=(1<<5);
 while(1)
 {
/* uncommenting -> common access troubles */
/*  printf("%x %x\n",TIMER0->value,PRIMIRQ->RSTAT); */
 }
} 
