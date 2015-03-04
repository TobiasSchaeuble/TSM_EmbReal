/*-------------------
  uart-demo foreground-background 
  (c) H.Buchmann FHNW 2013
 --------------------*/
#include "io/uart-irq.h" 
#include "sys/thread.h"
#include "io/lcd.h"
unsigned consumerPool[400]; 

void consumer() /* the background thread */
{
 Pixel pos=lcd_pixel(10,10);
 while(1)
 {
  char ch=uart_irq_in();
  pos+=lcd_char(pos,WHITE,ch); /* try once the ENTER key */
 }
}

int main()
{
 lcd_init();
 uart_irq_init();
 uart_irq_start();
 gic_init();
 arm_irq(1);
 Thread consumerTh;
 thread_create(&consumerTh,
               consumer,
	       consumerPool,sizeof(consumerPool));
 thread_run();	       
}
   
  
