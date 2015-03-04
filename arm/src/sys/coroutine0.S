/*-----------------------
 coroutine0 
 (c) H.Buchmann FHNW 2012
 $Id$
-------------------------*/ 
#include "sys/coroutine0.h"

/*
 stack 
 running                          next  
---> r0                             r0  <--- sp 
     r1                             r1
     ..                             .. 
     r12                            r12
     lr                             lr 
     -  <--- sp->from  to->sp ---->  -
*/
.text
/* void coroutine_transfer(Coroutine* from,Coroutine* to) 
 r0 -> from
 r1 -> to
*/
coroutine_transfer:
	push {r0-r12,lr}              /* save state */
	str sp,[r0]                    /* into from */
	ldr sp,[r1]           
	pop {r0-r12,pc}            /* restore state */
	
