/*--------------------
  polling
  (c) H.Buchmann FHNW 2013
 ---------------------*/
#include "sys/timer.h"
#include "io/uart-poll.h"
#include "clock.h"

Clock clock;                                               /* global */

static void doTick()
{
 if (TIMER0.RIS)                             /* counter reached zero */
    {
     clock_tick(&clock); 
     clock_display(&clock);
     TIMER0.IntClr=0;                           /* reset TIMER0.RIS */
    }
}

static void doEcho()
{
 if (uart_poll_avail())
    {
     uart_poll_out(uart_poll_in()); 
    }
}


int main()
{
 uart_poll_init();
 clock_init();
 Time  t={23,59,55};
 clock_create(&clock,
              &t, /* the local Time t will we copied into the clock */
              50,50);
 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
		    0;
 clock_display(&clock);                            /* initial value */
 while(1)
 {
  doTick();
  doEcho();
 }
 return 0; 
}
