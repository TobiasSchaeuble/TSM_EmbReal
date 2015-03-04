/*--------------------
  coroutines
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/timer.h"
#include "io/uart-poll.h"
#include "clock.h"
#include "sys/coroutine.h"
#include "stdio.h"

Coroutine tickCo;
unsigned  tickPool[0x400];

Coroutine echoCo;
unsigned echoPool[0x400];

static void doTick()
{
 Time  t={23,59,55};
 Clock clock;           /* clock now local */
 clock_init();
 clock_create(&clock,&t,50,50);
 clock_display(&clock);
 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
		    0;
  if (TIMER0.RIS) 
     {
      clock_tick(&clock);
      clock_display(&clock);
      TIMER0.IntClr=0;
     }
}


static void doEcho()
{
 uart_poll_init();
  if (uart_poll_avail())
     {
      uart_poll_out(uart_poll_in());
     }
  coroutine_transfer(&echoCo,&tickCo); /* explicit transfer */
}


int main()
{
 Coroutine mainCo;
 return 0; 
}
