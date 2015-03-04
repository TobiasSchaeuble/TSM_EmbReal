/*----------------------
  timer-trap-demo
  (c) H.Buchmann FHNW 2011
  calls onTick 'manually'
------------------------*/
#include "stdio.h"
#include "sys/timer.h"

static unsigned tick=0;

void onTick()
{
 printf("tick %d\n",tick++);
 TIMER0.IntClr=0;
}

int main()
{
 TIMER0.Load=0x100000; /* the count */
 TIMER0.Control=(1<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* wrapping */
		    0;
 while(1)
 {
  if (TIMER0.RIS) onTick();
 }
 return 0; 
} 
