/*---------------------------
  lcd-demo
  (c) H.Buchmann FHNW 2012
  $Id$
-----------------------------*/
#include "io/lcd.h"
#include <stdio.h>
int main()
{
 lcd_init();
 unsigned wi,he;
 lcd_dimension(&wi,&he);
 Pixel p=lcd_pixel(0,0);
 
 for(unsigned x=0;x<100;++x)
 {
  *p++=0xffff;
  p+=wi;
 }
 p=lcd_pixel(0,0);;
 for(char ch=' ';ch<0x80;++ch)
 {
  p+=lcd_char(p,0xffff,ch);
 }
 printf("------------ done\n");
 return 0;
}
