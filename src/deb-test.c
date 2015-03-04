/*-----------------------
  deb-test
  (c) H.Buchmann FHNW 2012
  $Id$
  -----------------------*/
#include "sys/deb.h"

int main()
{
 deb_string("Debug Test\n");
 while(1)
 {
  char ch=deb_in();
  deb_out(ch);deb_string("\t");deb_hex(ch);deb_string("\n");
 }
}
    
