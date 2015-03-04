/*----------------------
  forground-background taken from timer-trap-demo-hw.c
  (c) H.Buchmann FHNW 2011
  $Id$
------------------------*/
#include "stdio.h"
#include "sys/timer.h"
#include "sys/gic.h"
#include "sys/arm.h"

#define TIMER_0_1 36
static unsigned tick=0;

static void onTick()        /* the call back the foreground*/
{
 printf("tick %d\n",tick++);
 TIMER0.IntClr=0; /* write simply something */
}

int main()
{
 arm_init();
 gic_init();
 gic_install(TIMER_0_1,onTick);
 gic_enable(TIMER_0_1);
 arm_irq(1);
/* TIMER configuration */ 
 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(1<<5) | /* interrupt enable */
		(0<<0) | /* wrapping */
		    0;
 while(1)                  /* the background */
 {
  deb_out(deb_in());
 }
 return 0; 
} 
