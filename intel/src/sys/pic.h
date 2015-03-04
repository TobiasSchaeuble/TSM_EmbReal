#ifndef SYS_PIC_H
#define SYS_PIC_H
/*---------------------
 pic programmable interrupt controller  
 (c) H.Buchmann FHNW 2009
 $Id$
 see 8259A PROGRAMMABLE INTERRUPT CONTROLLER
 TODO integrate APIC
-----------------------*/ 
#include "sys/trap.h"
#define PIC_TRAP_NBR 8         /* the number of interrupts */

                                        /* some interrupts */
#define PIC_PIT 0       /* the programmable interval timer */
#define PIC_KBD 1                              /* keyboard */
/* TODO some more adapt master/slave pic */

extern void pic_init();

extern void pic_install(unsigned id, /* 0<=id<PIC_TRAP_NBR */
                        Trap t);       /* will be disabled */

extern void pic_enable(unsigned id); /* 0<=id<PIC_TRAP_NBR */
extern void pic_disable(unsigned id);/* 0<=id<PIC_TRAP_NBR */
#endif
