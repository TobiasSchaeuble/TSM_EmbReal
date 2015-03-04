/*--------------------
  threads-interrupt
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/arm.h"
#include "sys/timer.h"
#include "io/uart-irq.h"
#include "clock.h"
#include "sys/thread.h"
#include "sys/gic.h"
#include "stdio.h"

unsigned tickPool[0x400];
unsigned echoPool[0x400];

WaitQueue tickQ;

#define TIMER_0_1 36
static volatile unsigned tick=0;
static void onTick()
{
 ++tick;
 TIMER0.IntClr=0;
 thread_ready_from(&tickQ);
}

static void doTick()
{
 thread_wait_init(&tickQ,0,0);
 gic_install(TIMER_0_1,onTick);
 gic_enable(TIMER_0_1);
 Time  t={23,59,55};
 Clock clock;  
 clock_init();
 clock_create(&clock,&t,50,50);
 clock_display(&clock);
 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
 		(1<<5) | /* interrupt enable */
		    0;
 while(1)
 {
  thread_wait_at(&tickQ);
  --tick;
  clock_tick(&clock);
  clock_display(&clock);
 }    
}

static void doEcho()  
{
 uart_irq_init();
 uart_irq_start();
 while(1)
 {
  char ch=uart_irq_in();
  uart_irq_out(ch);
 }
}


int main()
{
 arm_init();
 gic_init();
 arm_irq(1);
 Thread tickTh;
 Thread echoTh;
 thread_create(&tickTh,doTick,tickPool,sizeof(tickPool));
 thread_create(&echoTh,doEcho,echoPool,sizeof(echoPool));
 thread_run();
 return 0; 
}
