/*-------------------------
 critical-section-2
 (c) H.Buchmann FHNW 2012
 $Id$
---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT (1ul<<20)

static int error(int cod,const char*const msg)
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
 pthread_mutex_t guard;
 volatile unsigned val;
} Shared;

Shared theShared;

static void* increment(void* data)
{
 unsigned long count=COUNT;
 while(count--)
 {
  pthread_mutex_lock(&theShared.guard);
  ++theShared.val;
  pthread_mutex_unlock(&theShared.guard);
 }
}

static void* decrement(void *data)
{
 Shared* shared=(Shared*)data;
 unsigned long count=COUNT;
 while(count--)
 {
  pthread_mutex_lock(&theShared.guard);
  --theShared.val;
  pthread_mutex_unlock(&theShared.guard);
 }
}


static void result()
{
 printf("theShared->val=%d\n",theShared.val);    
}

static void sequentially()
{
 increment(0);
 decrement(0);
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
/* sequentially(); */
 concurrent();
 result();
 return 0;
}
