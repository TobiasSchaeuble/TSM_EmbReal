/*---------------------
 trap
 (c) H.Buchmann FHNW 2009
 $Id$
-----------------------*/
#include "sys/trap.h"
#include "io/screen.h"
#include "io/ascii.h"
#include "sys/trap0.h"

/* TODO make better more robust init system */

#define SIZE (256)
typedef long long unsigned Entry;             /* of IDT */

/*--------------------------------------------- globals */
static Trap traps[SIZE];
static volatile Entry*   IDT=0;          /* base of IDT */
static unsigned CS;     /* the value of the cs register */
extern unsigned _ISR[];
static unsigned _ISR_LEN=0;

static void notImp(unsigned id)     /* the default trap */
{
 ascii_printf(Screen,"interrupt/trap %x: Not Implemented\n",id);
 while(1)
 {
 }
}

static void loadCS()
{
 asm volatile                       /* load cs register */
 (
  "mov %%cs,%[CS]\n\t"
  :[CS] "=m" (CS)
  :
 );
}

/* TODO set your own IDT */
static void loadIDT()
{
 unsigned idt[2]; 
 for(unsigned i=0;i<2;++i) idt[i]=0xaaaaaaaa;
 asm volatile
 (
  "sidt %[idt]\n\t"
  :[idt] "=m" (idt)
  :
 );
 IDT=(Entry*)((idt[0]>>16)|(idt[1]<<16));
}

/*TODO make exercise */
static void setGate(volatile Entry* e,unsigned type,unsigned isr)
{
 *e=((0xffff&(Entry)isr )     << 0)|
    ((0xffff&(Entry)CS  )     <<16)|
    ((0xffff&(Entry)type)     <<32)|
    ((0xffff&(Entry)(isr>>16))<<48);
}

/*TODO some gcc versions allows bit input: check ist */
static const unsigned INTERRUPT_GATE= 0x8e00; /* 1000 1110 0000 0000 */
static const unsigned TRAP_GATE     = 0x8f00; /* 1000 1111 0000 0000 */
                               /*  Present   P -| ||  |
                Descriptor Privilege Level DPL ---||  |
		Size of gate                 D -------| */


void trap_init()
{
 if (IDT) return;                     /* already initialized */
 loadIDT();
 loadCS();
 for(unsigned i=0;i<SIZE;++i) traps[i]=notImp;
 for(;_ISR[_ISR_LEN];++_ISR_LEN)   /* 0<=i<256 *not* checked */
 {
  setGate(IDT+_ISR_LEN,TRAP_GATE,_ISR[_ISR_LEN]);
 }
}

void trap_install(unsigned id,Trap t)
{
/*TODO disable */
 if (id<SIZE) traps[id]=t;
/*TODO enable */
}

void trap_show()
{
 ascii_printf(Screen,"ICS= %x IDT= %x\n",CS,IDT);
 for(unsigned i=0;i<_ISR_LEN;++i)
 {
  ascii_printf(Screen,"IDT[%d]=%x %x\n",
  i,
  (unsigned)(IDT[i]>>32),
  (unsigned)IDT[i]);
 }
}

/* called from trap0.S */
/* parameter in %ecx */

__attribute__ ((fastcall)) void _call_trap(unsigned id) 
{
 if (traps[id]) traps[id](id);
}

void _set_IDT(unsigned id,unsigned code)
{
}

