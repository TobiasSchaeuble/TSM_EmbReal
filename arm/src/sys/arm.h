#pragma once
/*--------------------
 arm important functions for arm architecture
 (c) H.Buchmann FHNW 2011
 $Id$
 [1] literature/ARM-Architecture-Reference-Manual.pdf
 exercise in inline assembler
----------------------*/
      /*              interrupt attribute */
typedef enum { RESET, 
	       UNDEF,           /* UNDEF */ 
	       SWI,             /* SWI   */
	       PREFETCH,        /* ABORT */
	       DATA,            /* ABORT */
	       RESERVED,        
	       IRQ,             /* IRQ */
	       FIQ              /* FIQ */
	     } Exception;

extern void arm_set_exception(Exception ex,void (*exception)());
 /* guarantee that exception is defined with the appropriate attribute
   __attribute__((interrupt(attr)))
   
 */
extern void arm_init();

extern void arm_undef();  /* executes an undef instruction triggering the
                             undef exeception */
/* CPSR see [1] A2.5 */
extern unsigned arm_getCPSR(); 
extern void arm_setCPSR(unsigned val);


extern void arm_irq(unsigned v);  /* v==0 disable v!=0 enable */
extern void arm_fiq(unsigned v);

/*----------------------------------------------- inline functions */
inline unsigned* arm_get_lr() /* return linkregister lr as pointer */
{
 unsigned* lr;
 asm volatile
 (
 "@----------------- arm_get_lr\n"
 "\t mov %[lr],lr\n"
 :[lr] "=r" (lr)
 :
 );
 return lr;
}

inline unsigned* arm_get_fault_address()
{
 unsigned* fa;
 asm volatile
 (
 "@----------------- arm_get_fault_address\n"
 "\t mrc p15,0,%[fa],c6,c0,0\n"
 :[fa] "=r" (fa)
 :
 );
 return fa; 
}

inline unsigned* arm_get_sp()
{
 unsigned* sp;
 asm volatile
 (
 "@----------------- arm_get_fault_address\n"
 "\t mov %[sp],sp\n"
 :[sp] "=r" (sp)
 :
 );
 return sp; 
}

/* swi made with define id as parameter */
#define _SWI_(id) \
asm volatile \
(\
"@----------------- swi\n"\
"\t swi " #id::)

inline void arm_swi() /* how to define an id */
{
 asm volatile
 (
 "@----------------- arm_swi\n"
 "\t swi 0x1234"
 :
 :
 );
}
