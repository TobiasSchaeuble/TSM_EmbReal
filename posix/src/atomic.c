/*-------------------------
 atomic.c
 (c) H.Buchmann FHNW 2012
 $Id$
 see Atomic.java
---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT (1ul<<15)

static int error(int cod,char* msg)
{
 if (cod<0)
    {
     perror(msg);
     exit(1);
    }
 return cod;
}

typedef struct
{
 volatile unsigned val;
} Shared;

Shared theShared; /* try without volatile */

static void* increment(void* data)
{
 unsigned long count=COUNT;
 while(count--)
 {
  __sync_add_and_fetch(&theShared.val,1);
 }
}

static void* decrement(void *data)
{
 Shared* shared=(Shared*)data;
 unsigned long count=COUNT;
 while(count--)
 {
  __sync_add_and_fetch(&theShared.val,-1);
 }
}


static void result()
{
 printf("theShared->val=%d\n",theShared.val);    
}

static void concurrent()
{
 pthread_t inc;
 pthread_t dec;
 error(pthread_create(&inc, 
		      0, /* no attributes */
		      increment,
		      0),
       "inc"
      );
 error(pthread_create(&dec, 
                0, /* no attributes */
		decrement,
		0),
       "dec"	
      );

 pthread_join(inc,0);
 pthread_join(dec,0); 
}

int main(int argc,char** args)
{
 theShared.val=0; 
 concurrent();
 result();
 return 0;
}
