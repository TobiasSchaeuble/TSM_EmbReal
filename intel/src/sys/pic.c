/*---------------------
 pic programmable interrupt controller  
 (c) H.Buchmann FHNW 2009
 $Id$
 see 8259A PROGRAMMABLE INTERRUPT CONTROLLER
 TODO integrate APIC
-----------------------*/ 
#include "sys/pic.h"
#include "io/screen.h"
#include "io/ascii.h"
#include "sys/sys.h"
#include "sys/deb.h"

#include "stdio.h"

#define PIC_INT_BASE 0x30
#define PIC_CMD 0x0    /* OWC2 OWC3 */
#define PIC_IMR 0x1         /* OWC1 */
#define PIC_ISR PIC_CMD
#define PIC_MASTER 0x20
#define PIC_SLAVE  0xa0

static Trap traps[PIC_TRAP_NBR];
static unsigned initialized=0;

static void trap(unsigned id)
{
 ascii_printf(Screen,"pi_c interrupt %x: Not Implemented\n",id);
 while(1)
 {
 }
}

static void pic_trap(unsigned id0) /* id 0..255 */
{
 unsigned id=id0-PIC_INT_BASE;
 if (traps[id]) traps[id](id);
 sys_outb(0x20,PIC_MASTER+PIC_CMD);            /* eoi */
}

static void init_chip()
{
                                       /* init master */ 
 sys_outb(                                    /* IWC1 */
           (1<<4) |                    /* select IWC1 */
           (1<<0) |                    /* IWC4 needed */
           (0<<1) |  /*  cascade VirtualBox needs this*/
               0,
          PIC_MASTER+PIC_CMD
	 );

 sys_outb(                                   /* IWC2 */
          PIC_INT_BASE,
          PIC_MASTER+PIC_IMR);

 sys_outb(1<<2,                              /* IWC3 */
          PIC_MASTER+PIC_IMR);	      /* bit 2 slave */ 

 sys_outb(                                   /* IWC4 */
	  (1<<0) |                      /* 8086 mode */
	  (1<<1) |                       /* auto eoi */
	      0,
          PIC_MASTER+PIC_IMR);    

#if 0
 ascii_string(Screen,"print any key...");
 kbd_get();
 ascii_string(Screen,"\n");
#endif

 sys_outb(0xff,               /* all masked */ 
          PIC_MASTER+PIC_IMR);
}


void pic_init()
{
 if (initialized) return;
 initialized=1;
 trap_init();
 unsigned id0=PIC_INT_BASE;
 for(unsigned i=0;i<PIC_TRAP_NBR;++i)
 {
  traps[i]=trap;
  trap_install(id0++,pic_trap);
 }
 init_chip();
}

void pic_enable(unsigned id)
{
/* TODO atomic access */
 if (id>=PIC_TRAP_NBR) return;
 sys_outb(sys_inb(PIC_MASTER+PIC_IMR)&(~(1<<id)),
          PIC_MASTER+PIC_IMR);
 
}

void pic_disable(unsigned id)
{
 if (id>=PIC_TRAP_NBR) return;
 sys_outb(sys_inb(PIC_MASTER+PIC_IMR)|(1<<id),
          PIC_MASTER+PIC_IMR);
}

void pic_install(unsigned id,Trap t)
{
 if (id>=PIC_TRAP_NBR) return;
 pic_disable(id);
 traps[id]=t;
}

