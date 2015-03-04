/*----------------------
  timer-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
  dont works with qemu-system-arm v 1.4.0
------------------------*/
#include "stdio.h"
#include "sys/timer.h"
#include "sys/gic.h"
#include "sys/arm.h"
#include "sys/deb.h"

#define TIMER_0_1 36
#define TIMER_2_3 37

static unsigned tick=0;

static void onTick()        /* the call back */
{
 printf("tick %d\n",tick++);
 TIMER2.IntClr=0; /* write simply something */
}

int main()
{
 arm_init();
 gic_init();
 gic_install(TIMER_2_3,onTick);
 gic_enable(TIMER_2_3);
 arm_irq(1);
/* TIMER configuration */ 
 TIMER2.Load=0x100000; /* the count */
 TIMER2.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(1<<5) | /* interrupt enable */
		(0<<0) | /* wrapping */
		    0;
 printf("PSR=%x\n",arm_getCPSR());
 while(1)
 {
  deb_out(deb_in());
 }
 return 0; 
} 
