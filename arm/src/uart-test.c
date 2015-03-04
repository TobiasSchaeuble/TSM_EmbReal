/*----------------------
  uart-test
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
  ----------------------*/
#include "io/uart-poll.h"
#include "sys/arm.h"
#include "sys/gic.h"
int main()
{
 arm_init();
 arm_irq(1);
 gic_init();
 uart_poll_enable();
 while(1)
 {
  uart_poll_out(uart_poll_in());
 }
}  
  
