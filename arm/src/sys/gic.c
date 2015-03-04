/*-----------------------------------
  gic generic interrupt controller
  (c) H.Buchmann FHNW 2012
  [1] literature/realview_emulation_basebord_ug.pdf
  only GIC1 is used 
       nesting interrupts
-------------------------------------*/
#include "sys/gic.h"
#include "sys/gic0.h"
#include "sys/arm.h"
#include "sys/deb.h"

#include "sys/stack.h"

typedef struct{
       unsigned CPUControl;         /* 000 */
       unsigned Priority;           /* 004 */   
       unsigned Point;              /* 008 */
 const unsigned Acknowledge;        /* 00c */
       unsigned EndInterrupt;       /* 010 */
 const unsigned Running;            /* 014 */
 const unsigned Highest_Pending;    /* 018 */
} GIC_IFC; 


#undef ARR
#undef RES

#define ARR(name,start,end) unsigned name[1+(end-start)/sizeof(unsigned)] 
#define RES(id,start,end) ARR(RES##id,start,end)


typedef struct{
      unsigned Control;
const unsigned ControllerType;
	       RES(0,0x1008,0x10fc);
      unsigned EnableSet[3];
	       RES(1,0x110c,0x117c);
      unsigned ClearSet[3];
	       RES(2,0x118c,0x11fc);
      unsigned PendingSet[3];
	       RES(3,0x120c,0x127c);
      unsigned PendingClear[3];
	       RES(4,0x128c,0x12fc);
const unsigned ActiveSet[3];
	       RES(5,0x130c,0x13fc);
	       ARR(Priority,0x1400,0x143c);
	       RES(6,0x1440,0x17FC);
      unsigned CPUTargets[24];
	       RES(7,0x1860,0x1bfc);
      unsigned Configuration[6];
	       RES(8,0x1c18,0x1efc);
      unsigned Software;
} GIC_DIS;


extern volatile GIC_IFC GIC1_IFC;
extern volatile GIC_DIS GIC1_DIS;


static Trap traps[TRAP_N]; /* the call back */

void gic_enable(unsigned id)
{
 if (id>=TRAP_N) return;
 GIC1_DIS.EnableSet[id/32]|=(1<<(id%32));
}

void gic_disable(unsigned id)
{
 if (id>=TRAP_N) return;
 GIC1_DIS.EnableSet[id/32]&=~(1<<(id%32));
}

void gic_install(unsigned id,Trap t)
{
 if (id>=TRAP_N) return;
// gic_disable(id);
 traps[id]=t;
 gic_disable(id);
}

#if 1
void gic_onIRQ()
{
#if 0
 printf("    _stack_top= %p\n"
        "_irq_stack_top= %p\n",_stack_top,_irq_stack_top);
 printf("sp=%x\n",arm_get_sp());
#endif 
 while(1)
 {
  unsigned id=GIC1_IFC.Acknowledge;
  if (id>=TRAP_N) break;
  Trap t=traps[id];
  if (t) t(); /* call trap */
  GIC1_IFC.EndInterrupt=id;
 }
}
#endif

#ifndef ON_IRQ
/*------------------------------- called by hardware */
#ifdef __clang__
#error not yet implemented
__attribute__((naked)) static void onIRQ()
#else
__attribute__((interrupt("IRQ"))) static void onIRQ()
#endif
{
 gic_onIRQ();
}
#endif

void gic_init()
{
 static unsigned initialized=0;
 if (initialized) return; /* already initialized */
 ++initialized;
/* for(unsigned i=0;i<16;++i) GIC1_DIS.Priority[i]=0xffffffff; */
 for(unsigned i=0;i<TRAP_N;++i) traps[i]=0;
 GIC1_IFC.CPUControl=1;
 GIC1_IFC.Priority=0xff;
 GIC1_DIS.Control=1;
 for(unsigned k=0;k<24;++k) GIC1_DIS.CPUTargets[k]=1;
 arm_set_exception(IRQ,onIRQ);
}

void gic_trigger(unsigned id)
{
 for(unsigned i=0;i<4;++i)
 {
  GIC1_DIS.Software=id;
 }
}

static void bits(const char*const name,const unsigned*const b,unsigned len)
{
 deb_pointer(b);deb_out('\t');deb_string(name);deb_out('\t');
 for(unsigned i=0;i<len;++i)
 {
  deb_hex(b[i]);
  deb_out(' ');
 }
 deb_newln();
}

void gic_debug()
{
#if 0
// deb_key_val("Highest_Pending",GIC1_IFC.Highest_Pending);
 bits("EnableSet",GIC1_DIS.EnableSet,3);
 bits("PendingSet",GIC1_DIS.PendingSet,3);
// bits("ActiveSet",GIC1_DIS.ActiveSet,3);
// bits("CPUTargets",GIC1_DIS.CPUTargets,0x60/4);
 deb_key_val("Acknowledge",GIC1_IFC.Acknowledge);
#endif
}

