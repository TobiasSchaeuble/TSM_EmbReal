/*--------------------
  undef-trap-demo-exceptions 
  see sys/boot/undef-trap-demo-exceptions.S
  demonstrates .onReset in sys/boot/undef-trap-demo-exceptions.S
  (c) H.Buchmann FHNW 2011
  $Id$
----------------------*/
#include <stdio.h>
int main()
{
 for(unsigned v=0;v<100;++v)
 {
  printf("trap-demo %d\n",v);
 }
}
