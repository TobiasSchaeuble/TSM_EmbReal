//-----------------------------
//cortex-m
//(c) H.Buchmann FHWN 2013
//-----------------------------
IMPLEMENTATION(sys_cortex_m,$Id$)
#include "sys/cortex-m.h"
#include "sys/deb/deb.h"

namespace sys
{
 CortexM* CortexM::cortexM=0;

 CortexM::CortexM(VTable::Entry*const tbl[],unsigned size,
                 Trap**const trap)
 :size(size)
 ,trap(trap)
 {
  for(unsigned i=0;i<size;++i) trap[i]=0;
  reg::SCS.SCB.VTOR=tbl;
  cortexM=this;
 }

 void CortexM::trapIt()
 {
  Trap* t=cortexM->trap[ipsr()];
  if (t) t->onTrap();
 }
 
 bool CortexM::inRange(unsigned id)
 {
  return id<cortexM->size;
 }
 

 void CortexM::arm(unsigned id)
 {
  if (inRange(id)) 
     {
      reg::SCS.NVIC.ISER[id/32]=(1<<(id%32));
     }
 }
   
 void CortexM::disarm(unsigned id)
 {
  if (inRange(id)) 
     {
      reg::SCS.NVIC.ICER[id/32]=(1<<(id%32));
     }
 }
 
 void CortexM::install(unsigned id,Trap* t)
 {
  if (inRange(id))
    cortexM->trap[id]=t;
 }

 void CortexM::cpsIE_i()
 {
  asm volatile
  (
   "cpsie i\n\t"
   :
   :
  );
 }
 
 void CortexM::cpsID_i()
 {
  asm volatile
  (
   "cpsid i\n\t"
   :
   :
  );
 }
 
 void CortexM::cpsIE_f()
 {
  asm volatile
  (
   "cpsie f\n\t"
   :
   :
  );
 }
 
 void CortexM::cpsID_f()
 {
  asm volatile
  (
   "cpsid f\n\t"
   :
   :
  );
 }
 
#if 0
 
 volatile typename CortexM::NVIC*const CortexM::nvic=(volatile CortexM::NVIC*const)0xe000e100;

#if 0
 void CortexM::defaultTrap()
 {
  static volatile unsigned*const ICSR=(volatile unsigned*const)0xe000ed04;
  deb::hex("Trap ICSR:",*ICSR);
 }
#endif

 
 void CortexM::enable(unsigned id)
 {
#warning CortexM::enable
#if 0
  if (id>=cortex->vtN) return;
  unsigned i=id/32;
  unsigned b=1<<(id%32);
  nvic->ICPR[i]|=b;
  nvic->ISER[i]|=b;
#endif
 }
 
 void CortexM::disable(unsigned id)
 {
#warning CortexM::disable
#if 0
  if (id>=cortex->vtN) return;
  nvic->ICER[id/32]|=(1<<(id%32));
#endif
 }


// volatile const CortexM::Trap**const CortexM::VTOR=(volatile const CortexM::Trap**const)0xe000ed08;

#endif 
}
