/*---------------------------
  stack
  (c) H.Buchmann FHNW 2012
  $Id$
  see sys/boot/big-bang.S
  see config/Makefile
  TODO define the other stack segments: fiq etc.
 ----------------------------*/
#include "sys/stack.h"
__attribute__((section(".stack")))
static __attribute__((section(".stack"))) 
 struct
 {
  unsigned undef   [UNDEF_STACK_SIZE_WORD]; 
  unsigned abort   [ABORT_STACK_SIZE_WORD];
  unsigned irq     [IRQ_STACK_SIZE_WORD];
  unsigned normal  [STACK_SIZE_WORD];
  unsigned top     [0];
 } stack;
 
unsigned*const  _undef_stack_top= stack.abort;
unsigned*const  _abort_stack_top= stack.irq;
unsigned*const  _irq_stack_top  = stack.normal;
unsigned*const  _stack_top      = stack.top;
