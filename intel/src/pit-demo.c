/*-----------------------
 pit-demo pit programmable interval timer
 (c) H.Buchmann FHNW 2009
 $Id$
 see: 82C54 CHMOS PROGRAMMABLE INTERVAL TIMER
-------------------------*/
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/sys.h"
#include "io/kbd.h"
#include "sys/pit.h"

int main()
{
 pit_configure(0,0x07fff,2); //mode 2
 while(1)
 {
  if (pit_eoc(0))
     {
      ascii_string(Screen,"t");      
     }
 }
 return 0;
}
