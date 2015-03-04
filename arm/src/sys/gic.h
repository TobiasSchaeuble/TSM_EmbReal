#pragma once
/*-----------------------------------
  gic generic interrupt controller
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
-------------------------------------*/
extern void gic_init();


#define TRAP_N 95                      /* the number of traps */
typedef void(*Trap)();                  /* called by hardware */

extern void gic_enable(unsigned id);
extern void gic_disable(unsigned id);
extern void gic_install(unsigned id,Trap t); /* trap disabled */

extern void gic_debug(); 
extern void gic_trigger(unsigned id); 
#if 0
extern void gic_active(); 
extern void gic_info();
#endif
