/*------------------------
  swi-trap-demo
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/ARM-Architecture-Reference-Manual.pdf
--------------------------*/
#include "stdio.h"
#include "sys/arm.h"

__attribute__((interrupt("SWI"))) void onSWI()
{
 unsigned swi=*(arm_get_lr()-1); /* get switch instruction [1] A2.6.4*/
 printf("swi %x\n",swi);
}

int main()
{
 printf("swi-trap-demo\n");
 arm_init();
 arm_set_exception(SWI,onSWI);
 while(1)
 {
  _SWI_(11); /* made with define */
 }
 return 0;
}
