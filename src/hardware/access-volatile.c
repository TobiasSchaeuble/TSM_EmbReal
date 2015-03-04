/*-----------------
 hardware-register
 (c) H.Buchmann FHNW 2010
 $Id$
 intel: no effect
 arm:   effect
-------------------*/

void wait()
{
 volatile unsigned* hw_register=(volatile unsigned*)(1<<10);
 while(1)
 {
  if (*hw_register) break;    /* will be set by periphery */
 }
}  
