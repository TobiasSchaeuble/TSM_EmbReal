/*-------------------------
 pthread-semaphore.c
 (c) H.Buchmann FHNW 2012
 $Id$
---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define COUNT (1ul<<25)

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
 sem_t guard;                      /* the semaphore */
 volatile unsigned val; /* check if really volatile */
} Shared;

Shared theShared;

static void* increment(void* data)
{
 unsigned long count=COUNT;
 while(count--)
 {
  sem_wait(&theShared.guard);/* close semaphore */
  ++theShared.val;
  sem_post(&theShared.guard); /* open semaphore */
 }
}

static void* decrement(void *data)
{
 Shared* shared=(Shared*)data;
 unsigned long count=COUNT;
 while(count--)
 {
  sem_wait(&theShared.guard); /* close semaphore */
  --theShared.val;
  sem_post(&theShared.guard); /* open semaphore */
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
 error(sem_init(&theShared.guard,
                0, /* not shared among processes */
		1), /* initially open */
		"sem_init");
 concurrent();
 result();
 return 0;
}
