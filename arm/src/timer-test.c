/*------------------------
 timer-test
 (c) H.Buchmann FHWN 2012
 $Id$
 -------------------------*/
#include "sys/timer.h"
#include <stdio.h>

int main()
{
 TIMER0.Load=0x100000;
 TIMER0.Control=(0<<7) | /* disabled */
                (1<<6) | /* periodic */
                (1<<1) | /* 32 bit */
		(0<<0) | /* one shot */
		    0;
 TIMER0.Control|=(1<<7); /* enable */
 while(1)
 {
  printf("Value=%x RIS=%x\n",TIMER0.Value,TIMER0.RIS);
 }
 return 0; 
}
  
