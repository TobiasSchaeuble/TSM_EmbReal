/*-----------------------
  uart-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/DUI0138E_CMxx6_UserGuide.pdf
  [2] literature/DDI0183-PrimeCell-UART.pdf
  [3] literature/DUI0159B_integratorcp_1_0_ug.pdf
  [4] literature/ARM-Architecture-Reference-Manual.pdf
  [5] http://gcc.gnu.org/onlinedocs/gcc-4.5.2/gcc/
-------------------------*/
#include "stdio.h"
#include "sys/sys.h"
#include "sys/deb.h"
                                       /* same struct for FIQ struct */
volatile struct                                     /* see [3] 3.6.1 */
{
 const unsigned STAT;
 const unsigned RSTAT;
 unsigned ENSET;
 unsigned ENCLR;
}* PRIMIRQ = 0x14000000;

volatile struct                                        /* see [2] 3.2 */
{
 unsigned DR;                                        /* Data Register */
 union                           /* union: SR/CR at the same loaction */
 {
  const unsigned SR;                         /* read: Status Register */
  unsigned CLR;                               /* write Clear Register */
 };
 unsigned res0[(0x18-0x08)/sizeof(unsigned)];
 const unsigned FR;                                   /*Flag register */
 unsigned res1[(0x30-0x1c)/sizeof(unsigned)];/* 0x1c - 0x2c  reserved */ 
 unsigned CR;                                /* 0x30 control register */
 unsigned IFLS;               /* Interrupt FIFO level select register */
 unsigned IMSC;                  /* Interrupt mask set/clear register */
 const unsigned RIS;                 /* Raw interrupt status register */
 const unsigned MIS;              /* Masked interrupt status register */
 unsigned ICR;                            /* Interrupt clear register */
}* UART = 0x16000000; 

typedef void (OnIRQ)();

extern OnIRQ* onIRQ; /* defined in big-bang.S */

/* see [4] A2.6.8 
       [5] Function-Attributes.html#Function-Attributes
*/
void main()
{
 onIRQ=myOnIRQ;
 sys_setCPSR(sys_getCPSR()&~(1<<7)); /* enable IRQ */

 UART->IMSC|=(1<<4);     /* RX  enabled */
 PRIMIRQ->ENSET|=(1<<1); /* bit 1 [3] 3.6 UART0 enabled*/
 char ch='0';
 while(1)
 {
 }
}
