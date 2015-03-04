/*--------------------
  interrupts
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/arm.h"
#include "sys/gic.h"
#include "sys/timer.h"
#include "io/uart-irq.h"
#include "clock.h"
#include "stdio.h"
#include "sys/deb.h"

#define TIMER_0_1 36
Time  t={23,59,55};
Clock clock;  

static void onTick()
{
 clock_tick(&clock);
 clock_display(&clock);
 TIMER0.IntClr=0;
}

static volatile char ch0=0;

static void onChar(char ch)
{
 deb_out(ch);
}


int main()
{
 arm_init();
 gic_init();
 clock_init();
 clock_create(&clock,&t,50,50);
 clock_display(&clock); 
 
 uart_irq_init();
 uart_irq_install(onChar);
 uart_irq_start();
 
 gic_install(TIMER_0_1,onTick);
 gic_enable(TIMER_0_1);
 arm_irq(1);

 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
		(1<<5) | /* interrupt enable */
		    0;
 while(1) /* main loop */
 {
 }
 return 0; 
}
