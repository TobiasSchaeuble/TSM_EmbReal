/*----------------------
 screen-test
 (c) H.Buchmann FHNW 2010
 $Id$
 -----------------------*/
#include "sys/screen.h"
int main()
{
 char ch='0';
 for(unsigned r=0;r<45;++r)
 {
  for(unsigned c=0;c<80;++c)
  {
   Screen->put(ch);
  }
  ch=(ch=='9')?'0':(ch+1);
 }
 for(unsigned c=0;c<80;++c)
 {
  Screen->put(ch);
 }
 Screen->put('z');
 return 0;
}
 
