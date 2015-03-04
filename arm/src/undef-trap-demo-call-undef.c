/*--------------------
  undef-trap-demo-exceptions 
  see sys/boot/undef-trap-demo-exceptions.S
  demonstrates .onReset in sys/boot/undef-trap-demo-exceptions.S
  (c) H.Buchmann FHNW 2011
  $Id$
----------------------*/
#include <stdio.h>
#include "sys/sys.h" /* for sys_undef */
int main()
{
 for(unsigned v=0;v<100;++v)
 {
  printf("trap-demo %d\n",v);
  sys_undef(); /* calls undef */ 
  printf("----------- done\n");
 }
}
