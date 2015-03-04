/*------------------
 trap-devel 
 (c) H.Buchmann FHNW 2009
 $Id$
--------------------*/
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/trap.h"

void trap()
{
 ascii_string(Screen,"Trap\n");
}

int main()
{
 ascii_string(Screen,"Trap-Devel\n");
 trap_init();
  trap_install(0x20,trap); /* uncomment for testing trap() */
 trap_show();
 asm volatile
 (
  "int $0x20\n\t"
  :
  :
 );
 ascii_string(Screen,"done\n");
 return 0;
}
