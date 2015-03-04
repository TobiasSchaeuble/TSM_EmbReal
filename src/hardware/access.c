/*-----------------
 hardware-register
 (c) H.Buchmann FHNW 2010
 $Id$
 intel: no effect
 arm:   effect
-------------------*/


/* volatile */ unsigned* hw_register=(unsigned*)(1<<10);

void wait()
{
 while(1)
 {
  if (*hw_register) break;    /* will be set by periphery */
 }
}  
