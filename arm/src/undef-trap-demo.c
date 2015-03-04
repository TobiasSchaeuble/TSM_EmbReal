/*--------------------
  undef-trap-demo
  (c) H.Buchmann FHNW 2011
  $Id$
----------------------*/
#include <stdio.h>
#include "sys/arm.h"    /* for triggering undef */

static __attribute__((interrupt("UNDEF"))) void myUndef()
{
 printf("myUndef lr=%x\n",arm_get_lr());
}

int main()
{
 arm_init();
 arm_set_exception(UNDEF,myUndef);
 unsigned v=0;
 while(1)
 {
  printf("undef-trap-demo %d\n",v++);
  arm_undef();                /* call undef */
 }
}  
