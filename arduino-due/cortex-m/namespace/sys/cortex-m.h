#pragma once
//-----------------------------
//cortex-m
//(c) H.Buchmann FHWN 2013
//[1] Cortex-M4 Devices Generic User Guide
//-----------------------------
INTERFACE(sys_cortex_m,$Id$)
#include "sys/reg/scs.h"
#include "sys/trap.h"
namespace sys
{
 class CortexM        //it is a singleton
 {
  public:
   enum Exception
   {
    RESET         = 1,
    NMI           = 2,
    HARD_FAULT    = 3,
    MEM_MANAGE    = 4,
    BUS_FAULT     = 5,
    USAGE_FAULT   = 6,
    //reserved    7-10
    SV_CALL       =11,
    DEBUG_MONITOR =12,
    //reserved     13
    PEND_SV       =14,
    SYS_TICK      =15,
    EXTERNAL      =16
   };
   
   static void arm(unsigned id);  
   static void disarm(unsigned id);
   static void trigger(unsigned id);
   static void install(unsigned id,Trap* t);
   
   static void cpsIE_i();
   static void cpsID_i();
   static void cpsIE_f();
   static void cpsID_f();
   static void svc()
   {
    asm volatile
    (
     "svc #4\n\t"
     :
     :
    );
   }
   
   static unsigned ipsr()
   {
    unsigned id;
    asm volatile
    (
     "mrs %[id],ipsr\n\t"
     :[id] "=r" (id) //output
     :
    );
    return id;
   }

#if 0   
   template<typename T>
   static T ldx(const T*const addr) //exclusive
   {
    T val;
    asm volatile
    (
     "@----------------------------------- ldx\n\t"
     "ldrex %[val], [%[addr]]\n\t"
     :[val] "=r" (val)
     :[addr] "r" (addr)
    );
    return val;
   }
   
   template<typename T>
   static unsigned stx(T*const addr,T val)
   {
    unsigned res;
    asm volatile
    (
     "@----------------------------------- stx\n\t"
     "strex %[res],%[val],[%[addr]]\n\t"
     :[res] "=r" (res)
     :[addr] "r" (addr),
      [val]  "r" (val)
    );
    return res;
   }
#endif  
  protected:
   static void trapIt();
   
   CortexM(VTable::Entry*const table[],unsigned size,
           Trap** trap);
         
  private:
   const unsigned     size;
         Trap**       trap; 
   static CortexM*    cortexM;
   
   static bool inRange(unsigned id);
 };
}
