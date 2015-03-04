#pragma once
/*-----------------------------------
  vic vectored interrupt controller
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/versatile_application_baseboard_arm926ej_s_ug.pdf
-------------------------------------*/
extern void vic_init();


#define TRAP_N 32                      /* the number of traps */
typedef void(*Trap)();                  /* called by hardware */

extern void vic_enable(unsigned id);
extern void vic_disable(unsigned id);
extern void vic_install(unsigned id,Trap t); /* trap disabled */

