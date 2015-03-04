/*-------------------------
 sys-id 
 (c) H.Buchmann FHNW 2012
 $Id$
 --------------------------*/
#include <stdio.h>

extern volatile unsigned SYS_ID;

int main()
{
 printf("SYS_ID=%x\n",SYS_ID);
 return 0;
} 
 
