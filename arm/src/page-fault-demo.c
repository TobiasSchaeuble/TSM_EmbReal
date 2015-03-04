/*----------------------
  page-fault-demo
  (c) H.Buchmann FHNW 2012
  $Id$
------------------------*/
#include "stdio.h"
#include "sys/arm.h"

static __attribute__((interrupt("ABORT"))) void onData()
{
 unsigned* loc=arm_get_lr();
 unsigned* mem=arm_get_fault_address();
 printf("page fault loc=%p mem=%p\n",loc,mem);
 while(1)
 {
 }
}

int main()
{
 arm_init(); /* dont forget */
 arm_set_exception(DATA,onData);
 unsigned* p=(unsigned*)(64*(1<<20)+4); /* no memory there: see mmc.c */
 printf("before assignment\n");
 *p=0;
 printf("after assignment\n");
 return 0;
}  
