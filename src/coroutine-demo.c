/*-----------------------
 coroutine-test
 (c) H.Buchmann FHNW 2012
 $Id$
-------------------------*/
#include "stdio.h"
#include "sys/coroutine.h"

Coroutine cor0;
Coroutine cor1;

#define POOL 256
unsigned pool[POOL];

void coroutine()
{
 while(1)
 {
  printf("----------- cor1\n");
  coroutine_transfer(&cor1,&cor0);
 }
}

int main()
{
 coroutine_init(coroutine,pool,sizeof(pool),&cor1);
 while(1)
 {
  printf("----------- cor0\n");
  coroutine_transfer(&cor0,&cor1);
 }
 return 0;
}
 
