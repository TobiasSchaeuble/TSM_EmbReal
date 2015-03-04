/*-----------------------------
 apic advanced programmable interrupt controller
 (c) H.Buchmann FHNW 2010
 $Id$
 see apic-devel
 [1] Intel® 64 and IA-32 Architectures
     Software Developer's Manual 3A Chapter 8
 ------------------------------*/
#include "sys/apic.h"
#include "sys/pic.h"
#include "sys/sys.h"
#include "sys/trap.h"
#include "io/ascii.h"
#include "sys/screen.h"

#define TRAP_ENTRY 0x20
typedef unsigned Entry[4];  /* 16 bytes */

/* the apic register */
static volatile Entry* apic=0;  /* will be set in apic_init */
                                           /* see table 8.1 */
                                 /* TODO explain addressing */

void apic_init()
{
 if (apic) return;                   /* already initialized */
 pic_init();
 static const MSR MASK=(1<<12)-1;
 MSR base=sys_read_msr(0x1b); /*  [1] 8.4.2 */
 apic=(volatile Entry*)((unsigned)(base&~MASK));
}

static Tick onTick=0;

static void tick(unsigned id)
{
 if (onTick) onTick();
 *apic[0xb]=0; /* end of interrupt */
}

void apic_timer(unsigned count,Tick t)
{
 onTick=t;
 trap_install(TRAP_ENTRY,tick);
 *apic[0x38] =count;
 *apic[0x32] =(TRAP_ENTRY|       /* vector */
                  (0<<16)|       /* unmask */
  	          (1<<17));     /* periodic */
}

void apic_timer_enable()
{
 *apic[0x0f]|=(1<<8);
}

void apic_timer_disable()
{
 #warning TODO not yet done
}
