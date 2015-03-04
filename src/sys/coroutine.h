#pragma once
/*---------------------------
 coroutine
 (c) H.Buchmann FHNW 2012
 $Id$
-----------------------------*/
typedef struct Status Status;
typedef union Coroutine Coroutine;

union Coroutine
{
 unsigned* pool;
 Status*   status;
};

extern void coroutine_init(void (*code)(),
                           void*    pool,
			   unsigned pool_size_byte,
                           Coroutine*const co);
			   
extern void coroutine_transfer(Coroutine*const from,
                               Coroutine*const to);

extern void coroutine_show(const Coroutine*const co);
