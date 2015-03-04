/*--------------------
  undef-trap-demo-exceptions 
  see sys/boot/undef-trap-demo-exceptions.S
  demonstrates .onReset in sys/boot/undef-trap-demo-exceptions.S
  (c) H.Buchmann FHNW 2011
  $Id$
----------------------*/
#include <stdio.h>
#include "sys/sys.h"                                 /* for sys_undef */
#include "sys/deb.h"
typedef void (OnTrap)();       /* functions with signature void xxx() */

void myOnUndef() /* is of type OnTrap */
{
 deb_string("\n\nmyOnUndef\nresetting\n\n");
 deb_reset(); /* terminates */
}

extern OnTrap* onUndef;             /* defined in big-bang-call-c.S */

int main()
{
 onUndef=myOnUndef; /* register myOnUndef */
 for(unsigned v=0;v<100;++v)
 {
  printf("trap-demo %d\n",v);
  sys_undef(); /* calls undef */
 }
}
