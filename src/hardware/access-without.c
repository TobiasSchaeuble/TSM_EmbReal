/*-----------------
 hardware-register
 (c) H.Buchmann FHNW 2010
 $Id$
 intel: no effect
 arm:   effect
-------------------*/

void wait()
{
 unsigned* hw_register=(unsigned*)(1<<10);
 while(1)
 {
  if (*hw_register) break;    /* will be set by periphery */
 }
}  
