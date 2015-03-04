/*-------------------
 cpu-trap
 (c) H.Buchmann FHNW 2010
 $Id$
---------------------*/ 
#include "sys/trap.h"

static unsigned x=1;
static unsigned y=0;

int main()
{
 trap_init();
 volatile unsigned z=x/y; /* generates an */
 	                  /* Interrupt 0 Divide Error Exception (#DE) */
 return 0;
}
