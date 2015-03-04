/*--------------------------
  stdio-test
  (c) H.Buchmann FHNW 2011
  $Id$
  ignore conflicting types for built-in function printf
 ---------------------------*/
#include "stdio.h"
int main()
{
 printf("Hello %s %d 0x%x\n","sss",8,0x123);
} 
