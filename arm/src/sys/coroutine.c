/*---------------------------
 coroutine
 (c) H.Buchmann FHNW 2012
 $Id$
 TODO
 ../src/sys/coroutine.c:27:12: warning: assignment from incompatible pointer type [enabled by default]
-----------------------------*/
#include "sys/coroutine.h"
#include "sys/coroutine0.h"
#include "stdio.h"


struct Status
{                          /* low address */
 unsigned ri[13];  /* r12 .. r0 registers */
 void (*lr)();     
};  

void coroutine_init(void (*code)(),
                    void* pool,
	            unsigned size_byte,
		    Coroutine*const co)
{
 Status* status=(Status*)((unsigned char*)pool+(size_byte-sizeof(Status)));
 for(unsigned i=0;i<13;++i) status->ri[i]=i;
 status->lr=code;
 co->status=status;
}

void coroutine_show(const Coroutine*const co)
{
 printf("pool = %p\n",co->pool);
 if (co->pool==0) return;
 Status* s=co->status;
 printf("status = %p\n"
        "r0 =%x r1 =%x r2 =%x  r3 =%x\n"
	"r4 =%x r5 =%x r6 =%x  r7 =%x\n"
	"r8 =%x r9 =%x r10=%x  r11=%x\n"
	"r12=%x\n"
	" lr=%x\n",
	s,
	s->ri[ 0],s->ri[ 1],s->ri[ 2], s->ri[ 3],
	s->ri[ 4],s->ri[ 5],s->ri[ 6], s->ri[ 7],
	s->ri[ 8],s->ri[ 9],s->ri[10], s->ri[11],
	s->ri[20],
	s->lr);
 
 for(unsigned i=0;i<14;++i)
 {
  printf("%d\t%x\n",i,co->pool[i]);
 }
 	
}


/* void coroutine_transfer(Coroutine* from¨Coroutine* to) 
  see coroutine0.S */
