/*------------------------
 pthread-trigger
 (c) H.Buchmann FHNW 2012
 $Id$
--------------------------*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

/*---------------------------------------------------------- the semaphores */
sem_t initializeS;
sem_t triggerS;

#define SHOOTN 10

void* shoot(void* data)
{
 unsigned id=*(unsigned*)data; /* copy */
/* printf("id= %d\n",id); */
 sem_post(&initializeS);
 while(1)
 {
  sem_wait(&triggerS); /* wait for trigger */
  fprintf(stderr,"\nshoot: %d\n",id);
 }
}

static void init()
{
 sem_init(&triggerS,0,0);
 sem_init(&initializeS,0,0);
 for(unsigned s=0;s<SHOOTN;++s)
 {
  pthread_t th;
  pthread_create(&th,0,shoot,&s);
  sem_wait(&initializeS);               /* wait until thread th initialized */
 }   
}

static void trigger(unsigned cnt)
{
 while(cnt--)
 {
  sem_post(&triggerS);
 }
}

static void menu()
{
 while(1)
 {
  fprintf(stderr,"Menu\n"
        	 "             0:exit\n"
		 "             1:trigger 1\n"
		 "             2:trigger 2\n"
		 "             3:trigger 3\n"
		 "             4:trigger 4\n"
		 "             5:trigger 5\n"
		 "your choice: ");
  char answer;
  int size=fread(&answer,sizeof(answer),1,stdin);
  switch(answer)
  {
   case '0':
   return;
   
   case '1':
   case '2':
   case '3':
   case '4':
   case '5':
    trigger(answer-'0');
   break;
  }
 }
}

int main(int argc,char** args)
{
 init();
 menu();
/* TODO clean up 
   the semaphores */  
}  
