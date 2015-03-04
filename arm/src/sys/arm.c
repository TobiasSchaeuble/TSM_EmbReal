/*--------------------
 sys important sys functions
 (c) H.Buchmann FHNW 2011
 $Id$
 see [1] literature/ARM-Architecture-Reference-Manual.pdf
     [2] gcc.gnu.org/onlinedocs/gcc-4.6.3/gcc/
 an exercise in gcc specialties    
----------------------*/
#include "sys/arm.h"
#include "sys/deb.h"


/* -------------------------------------------- the exception handlers */
/* see [2] Function-Attributes */

extern void onReset();       /* defined in big-bang.S */
static __attribute__((interrupt("UNDEF"))) void onUndef()
{
 deb_msg("unexpected UNDEF");
}

static __attribute__((interrupt("SWI"))) void onSWI()
{
 deb_msg("unexpected SWI");
}

static __attribute__((interrupt("ABORT"))) void onPrefetch()
{
 deb_msg("unexpected ABORT:prefetch");
}

static __attribute__((interrupt("ABORT"))) void onData()
{
 deb_msg("unexpected ABORT:Data");
}

static void onReserved()
{
 deb_msg("onReserved");
}

static __attribute__((interrupt("IRQ"))) void onIRQ()
{
 deb_msg("unexpected IRQ");
}

static __attribute__((interrupt("FIQ"))) void onFIQ()
{
 deb_msg("unexpected FIQ");
}



/*------------------------------------------------ the exception table */
typedef  struct /* see see [1] A2.6  */
{
 unsigned PC[8];                      /* code for ldr pc,exception[i] */
 void (*exception[8])();               /* array of functions void (); */
} ExceptionTable;

#define LDRPC 0xe59ff018

static const ExceptionTable DefaultExceptionTable=
{
 {LDRPC,LDRPC,LDRPC,LDRPC,LDRPC,LDRPC,LDRPC,LDRPC},
 {onReset,         /* see big-bang.S */
  onUndef,
  onSWI,
  onPrefetch,
  onData,
  onReserved,
  onIRQ,
  onFIQ
 }
};

volatile ExceptionTable* exceptionTable = 0;


void arm_init()
{
 static unsigned init=0;
 if (init) return; /* already initalized */
 init=1; 
 *exceptionTable=DefaultExceptionTable; 
}


void arm_set_exception(Exception ex,void (*exception)())
{
 arm_init();
 exceptionTable->exception[ex]=exception;
}

void arm_undef()
{
 asm volatile /* see [2] Extended-Asm.html#Extended-Asm */
 (
  ".word 0xe7f000f0"           /* see [1] A3.16.5 p 147 */
  :
  :
 );
}

unsigned arm_getCPSR()
{
 unsigned v;
 asm volatile /* see [2] Extended-Asm.html#Extended-Asm */
 (
  "@--------------- sys_getCPSR\n"
  "\tmrs %[v],cpsr"            /* see [1] A3.10.2 128 */
  :[v] "=r" (v)/* out */
  :            /* in */
 );
 return v;
}
 
void arm_setCPSR(unsigned v)
{
  asm volatile /* see [2] Extended-Asm.html#Extended-Asm */
 (
  "@--------------- sys_setCPSR\n"
  "\tmsr cpsr,%[v]"               /* see [1] A3.10.2 128 */
  :            /* out */
  :[v] "r" (v)  /* in */
 );
}

void arm_irq(unsigned v) /* see [1] A2.5 */
{
 unsigned psr=arm_getCPSR();
 arm_setCPSR((v)?psr&~(1<<7):psr|(1<<7));
                /*  |          |----------- set   
                    |---------------------- clear */
}

void arm_fiq(unsigned v)
{
 unsigned psr=arm_getCPSR();
 arm_setCPSR( (v)?psr&~(1<<6):psr|(1<<6));
}
