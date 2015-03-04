/*--------------------------
 thread
 (c) H.Buchmann FHNW 2012
 TODO remove arm_irq(0),arm_irq(1)
----------------------------*/
#include "sys/thread.h"
#include "stdio.h"
#include "sys/arm.h"

static Thread* swap(Thread* in,volatile Thread** loc)
{
 Thread* out;
 asm volatile 
 (
 "@------------------------------\n"
 "\tswp %[out],%[in],[%[loc]]\n"
 :[out] "=&r" (out)     /* out */
 :[loc]"r" (loc),   /* in  */
  [in]  "r" (in)
 );
}

static Thread      main_={next:0};

static struct 
{
 Thread n0;
 Thread n1;
 volatile Thread* first;
 volatile Thread* last; /*accessible by fore and background */
} ready =            /* n0 -> n1 
                        ^     ^
			first last */
{
 n0:    {next:&ready.n1},
 n1:    {next:0},
 first: &ready.n0,
 last:  &ready.n1
};


static volatile Thread*     run=&main_;

static void showThread(volatile const Thread*const th)
{
  if (th==&ready.n0) 
     {
      printf("\tth=n0\n");
      return;
     }
  if (th==&ready.n1)
     {
      printf("\tth=n1\n");
      return;
     }   
  printf("\tth=%p\n",th);
}

static void show(const char*const msg)
{
 printf("%smain=%p\n",msg,&main_);
 printf("run =%p\n",run);
 printf("ready\n");
 volatile Thread* th=ready.first;
 while(th!=0)
 {
  showThread(th);
  th=th->next;
 }
}

static void showQueue(const WaitQueue* q)
{
 printf("queue: %p\n",q);
 volatile Thread* th=q->first;
 while(th)
 {
  printf("\t%p\n",th);
  th=th->next;
 }
}

void thread_ready(volatile Thread* th)
{
/*<<<<<<<<<<<<<<<<<<<<<<< critical  */
 th->next=0;
 ready.last->next=th;
 ready.last=th;
/*>>>>>>>>>>>>>>>>>>>>>>> critical */ 
#if 0
 Thread* l=swap(th,&ready.last);
 l->next=th;
#endif
}

void thread_create(Thread* th,
                   void (*run)(),
                   void* pool,
		   unsigned size_byte)
{
/*  printf("thread_create %p\n",th); */
 th->next=0;
 coroutine_init(run,pool,size_byte,&(th->cor));
 thread_ready(th);
}

static volatile Thread* next()
{
 while(1)
 {
  volatile Thread* th=ready.first;
  ready.first=th->next;
  if ((th!=&ready.n0) && (th!=&ready.n1))
     {
      return th;
     }
     else
     {
      thread_ready(th);
     }
 }
}

void thread_yield()
{
 Thread* r=run;
 arm_irq(0);
 thread_ready(r);
 run=next(); 
 arm_irq(1);
 coroutine_transfer(&(r->cor),&(run->cor));
}

void thread_run() 
{
 while(1) thread_yield();
}

void thread_wait_init(volatile WaitQueue*const q,void (*lock),void (*unlock)())
{
 q->lock=lock;
 q->unlock=unlock;
 q->first=0;
 q->last=0;
}



void thread_wait_at(volatile WaitQueue*const q)
{
 Thread* r=run;
 r->next=0;
 if (q->last==0)
    {
     q->first=r;
    }
    else
    {
     q->last->next=r;
    }
 q->last=r;
 arm_irq(0); /* try without */
 run=next();
 arm_irq(1);
 coroutine_transfer(&(r->cor),&(run->cor));   
}

void thread_ready_from(volatile WaitQueue*const q)
{
 volatile Thread* th=q->first;
 if (th==0) return; 
 q->first=th->next;
 if (q->first==0) q->last=0;
 thread_ready(th);
}
