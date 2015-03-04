/*-----------------------
 coroutine-test
 (c) H.Buchmann FHNW 2012
 $Id$
-------------------------*/
#include "stdio.h"
#include "sys/coroutine.h"
#include "sys/arm.h"

Coroutine corMain;
Coroutine cor0,cor1;

#define POOL 256
unsigned pool0[POOL];
unsigned pool1[POOL];

void coroutine0()
{
 while(1)
 {
  printf("----------- cor0 sp=%x\n",arm_get_sp());
  coroutine_transfer(&cor0,&cor1);
 }
}

void coroutine1()
{
 while(1)
 {
  printf("----------- cor1 sp=%x\n",arm_get_sp());
  coroutine_transfer(&cor1,&corMain);
 }
}


int main()
{
 coroutine_init(coroutine0,pool0,sizeof(pool0),&cor0);
 coroutine_init(coroutine1,pool1,sizeof(pool1),&cor1);
 while(1)
 {
  printf("----------- main sp=%x\n",arm_get_sp());
  coroutine_transfer(&corMain,&cor0);
 }
 return 0;
}
 
