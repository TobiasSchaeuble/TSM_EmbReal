#pragma once
/*---------------------------
  stack
  (c) H.Buchmann FHNW 2012
  $Id$
 ----------------------------*/
#if __ASSEMBLER__ == 1
.global _undef_stack_top
.global _abort_stack_top
.global _irq_stack_top
.global _stack_top
#else
extern unsigned*const _undef_stack_top;
extern unsigned*const _abort_stack_top;
extern unsigned*const _irq_stack_top;
extern unsigned*const _stack_top;
#endif
