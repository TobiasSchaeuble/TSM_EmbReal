#pragma once
/*-----------------------------
 apic advanced programmable interrupt controller
 (c) H.Buchmann FHNW 2010
 $Id$
 ------------------------------*/

extern void apic_init(); /* must be called prior to all other calls */

typedef void (*Tick)();                             /* the callback */

extern void apic_timer(unsigned count,
                       Tick t);                /* timer not enabled */

extern void apic_timer_enable();
extern void apic_timer_disable();
