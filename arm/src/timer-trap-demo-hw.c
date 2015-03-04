/*----------------------
  timer-trap-demo
  (c) H.Buchmann FHNW 2011
  shows TIMER0.Value TIMER0.RIS
------------------------*/
#include "stdio.h"
#include "sys/timer.h"

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
  printf("Value=%x RIS=%x\n",TIMER0.Value,TIMER0.RIS);
 }
 return 0; 
} 
