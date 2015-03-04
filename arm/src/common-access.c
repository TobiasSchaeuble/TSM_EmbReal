/*----------------------
  timer-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
------------------------*/
#include "stdio.h"
#include "sys/timer.h"
#include "sys/gic.h"
#include "sys/arm.h"
#include "io/uart-poll.h"

#define TIMER_0_1 36

volatile static int tick=0;
volatile static int own_IRQ_tick=0;
static void onTick()        /* the call back */
{
 ++tick;
 ++own_IRQ_tick;
 TIMER0.IntClr=0; /* write simply something */
}

static void init()
{
 arm_irq(1);
 gic_init();
 gic_install(TIMER_0_1,onTick);
 gic_enable(TIMER_0_1);
 TIMER0.Load=0x1000; /* the count */
 TIMER0.Control=(1<<7) | /* enabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(1<<5) | /* interrupt enable
		(0<<0) | /* wrapping */
		    0;
}


static void wait(unsigned cnt) /* use TIMER1 for busy wait */
{
 TIMER1.Load=cnt;
 TIMER1.Control=(1<<7)|
                (1<<1)|
		(1<<0)| /* one shot */
		  0;
 while(TIMER1.RIS==0){}
 TIMER1.IntClr=0;
}

static void loop()
{
 int own_loop_tick=0;
 while(1)
 {
  if (uart_poll_avail()) break;
  volatile int l0=tick; /* for real assignment */
  --l0;
  wait(0x10);
  tick=l0;
  ++own_loop_tick;
 }
 printf("balance=%d\n",tick-(own_IRQ_tick-own_loop_tick));
}

int main()
{
 init();
 loop();
 printf("done\n");
 return 0; 
} 
