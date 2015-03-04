#pragma once
/*--------------------------
 thread
 (c) H.Buchmann FHNW 2012
 $Id$
 TODO discuss the volatile stuff
----------------------------*/
#include "sys/coroutine.h"
typedef struct Thread Thread;
struct Thread
{
 volatile Thread*   next;
 Coroutine cor;
};


extern void thread_create(Thread* th,
                          void (*code)(),
                          void* pool,
			  unsigned pool_size_byte);

extern void thread_yield();


extern void thread_ready(volatile Thread* th);
 /* th *not* running */

extern __attribute__((noreturn)) void thread_run(); /* never returnS */
                                /* called from main as last function */

/* ------------------------------------------------ queues */ 
typedef struct WaitQueue WaitQueue; 

struct WaitQueue  
{
 void (*lock)();
 void (*unlock)();
 volatile Thread* first;     /* accessible fore-background */
 volatile Thread* last;
};


extern void thread_wait_init(volatile WaitQueue* q,void (*lock),void (*unlock)());
extern void thread_put(Thread*const th);
extern void thread_wait_at(volatile WaitQueue*const q);
extern void thread_ready_from(volatile WaitQueue*const q);
