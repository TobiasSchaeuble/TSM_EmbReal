/*------------------------
 gic-test
 (c) H.Buchmann FHNW 2012
 $Id$
 -------------------------*/
#include "sys/gic.h"
#include "sys/timer.h"
#include "sys/arm.h"
#include "sys/deb.h"
#include <stdio.h>

static unsigned cnt=0;

static void tick()
{
 printf("Tick %d\n",++cnt);
 TIMER0.IntClr=0;
}

static void timer()
{
 TIMER0.Load=0x100000;
 TIMER0.Control=(0<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
		    0;
 TIMER0.Control|=(1<<7)|  /* enable */
                 (1<<5)|  /* int enable */
		     0;
/* while(TIMER0.RIS==0){} */

}

int main()
{
 arm_irq(1);
 gic_init();
 gic_install(0x24,tick);
 gic_enable(0x24);
 timer();
 while(1)
 {
  
 }
 return 0; 
}

