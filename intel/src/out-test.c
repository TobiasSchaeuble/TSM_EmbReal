/*---------------------
  out-test
  (c) H.Buchmann FHNW 2010
  $Id$
  ---------------------*/
#include "io/out.h"

void screen_init() /* used in start */
{
}

int main() /* return type for the compiler */
{
 out_init(); 
 for(unsigned i=0;i<9;++i)
 {
  out_char('9');
 }
}
   
