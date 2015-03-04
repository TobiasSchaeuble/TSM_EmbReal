/*-----------------------
 irq-demo
 (c) H.Buchmann FHNW 2009
 $Id$
-------------------------*/ 
/*PIC Register */
#include "io/ascii.h"
#include "sys/screen.h"

#define PIC_CMD  0
#define PIC_IMR  1
#define PIC_ISR  PIC_CMD
#define PIC_POLL PIC_ISR
#define PIC_OCW3 PIC_ISR

#define MASTER 0x20
#define SLAVE  0xa1


typedef void(Trap)();

void trap()
{
 ascii_string(Screen,"Trap");
 
 while(1)
 {
 }
}

typedef long long unsigned Entry;

static Entry* IDT=(Entry*)0; /* could be read by sidt */

int main()
{
#if 0
 unsigned idt[4];
 for(unsigned i=0;i<4;++i) idt[i]=0xaaaaaaaa;
 
 asm volatile
 (
  "sidt %[idt]\n\t"
  :[idt] "=m" (idt)
  :
 );
 
 for(unsigned i=0;i<4;++i)
 {
  ascii_unsigned_hex(Screen,idt[i]);
  ascii_newln(Screen);
 }
#endif
 unsigned cs=0xaaaaaaaa;
 asm volatile
 (
  "mov %%cs,%[cs]\n\t"
  :[cs] "=m" (cs)
  :
 );
 ascii_unsigned_hex(Screen,cs);
 ascii_newln(Screen);
#if 1 
 unsigned Trap=0x8f00;  //1000 1111 0000 0000
 unsigned CS=0x8;       //taken manually
 Entry e= ((CS<<16)|(0xffff&(unsigned)trap)) |
          (Entry)(Trap|(0xffff0000&(unsigned)trap))<<32;
 IDT[3]=e;
 ascii_printf(Screen,"trap=%x %x %x\n",(unsigned)trap,
               (unsigned)IDT[3],(unsigned)(IDT[3]>>32));
#if 1
 asm volatile
 (
  "int3\n\t"
  :
  :
 );
#endif
#endif         
 return 0;
}
