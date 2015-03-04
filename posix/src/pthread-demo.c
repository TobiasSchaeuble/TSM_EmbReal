/*-------------------------
 pthread.c
 (c) H.Buchmann FHNW 2012
 $Id$
---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for strncpy */
#include <pthread.h>

typedef struct
{
 pthread_t th; 
 char name[80];  
} LocalData;

static void* run(void* localData)
{
 while(1)                              /* forever */
 {
 // printf("%s\n",((LocalData*)localData)->name);
 }
}

LocalData th1;
LocalData th2;
            
int main(int argc,char** args)
{
 strncpy(th1.name,"111111111",sizeof(th1.name));
 strncpy(th2.name,"222222222",sizeof(th2.name));
 pthread_create(&th1.th,0,run,&th1);
 pthread_create(&th2.th,0,run,&th2);
 
 pthread_join(th1.th,0); /* wait until th1 terminates */
 pthread_join(th2.th,0); /* wait until th1 terminates */
 return 0;
}
