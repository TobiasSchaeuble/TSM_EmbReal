/*------------------
 kbd-demo
 (c) H.Buchmann FHNW 2009
 $Id$
--------------------*/
#include "io/kbd.h"
#include "io/ascii.h"
#include "sys/screen.h"

int main()
{
 while(1)
 {
  ascii_put(Screen,kbd_get());
 }
 return 0;
} 
