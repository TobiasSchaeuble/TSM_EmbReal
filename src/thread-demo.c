/*---------------------------
 thread-demo
 (c) H.Buchmann FHNW 2012
 $Id$
-----------------------------*/
#include "sys/thread.h"
#include "stdio.h"

void code1()
{
 while(1)
 {
  printf("th1\n");
  thread_yield();
 }
}

void code2()
{
 while(1)
 {
  printf("th2\n");
  thread_yield();
 }
}

unsigned pool1[0x200];
Thread th1;
unsigned pool2[0x200];
Thread th2;

int main()
{
 thread_create(&th1,code1,pool1,sizeof(pool1));
 thread_create(&th2,code2,pool2,sizeof(pool2));
 thread_run(); /* never returns */
}
