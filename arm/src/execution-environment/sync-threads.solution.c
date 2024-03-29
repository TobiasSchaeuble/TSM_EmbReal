/*--------------------
  thread
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/timer.h"
#include "io/uart-poll.h"
#include "clock.h"
#include "sys/thread.h"
#include "stdio.h"

unsigned tickPool[0x400];
unsigned echoPool[0x400];

static void doTick()
{
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
  if (TIMER0.RIS) 
     {
      clock_tick(&clock);
      clock_display(&clock);
      TIMER0.IntClr=0;
     }
  thread_yield(); /* release cpu */
 }    
}

static void doEcho()
{
 uart_init();
 while(1)
 {
  if (uart_avail())
     {
      uart_out(uart_in());
     }
  thread_yield(); /* release cpu */
 }
}


int main()
{
 Thread tickTh;
 Thread echoTh;
 thread_create(&tickTh,doTick,tickPool,sizeof(tickPool));
 thread_create(&echoTh,doEcho,echoPool,sizeof(echoPool));
 thread_run();
 return 0; 
}
