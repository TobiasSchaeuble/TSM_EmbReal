//-----------------------
//big-bang-continued
//(c) H.Buchmann FHNW 2014
//-----------------------
#include "sys/boot/big-bang-continued.h"
#include "sys/abi/abi.h"
#include "sys/deb/deb.h"
//#include "sys/cortex-a9.h"
namespace sys
{
 
 namespace boot
 {
  extern "C" unsigned _bss_beg[];
  extern "C" unsigned _bss_end[];
  extern "C" Mod::Global __GLOBAL__CONSTRUCTORS_BEG[];
  extern "C" Mod::Global __GLOBAL__CONSTRUCTORS_END[];
  
  void start()
  {
   for(unsigned* d=_bss_beg;d!=_bss_end;++d) *d=0; //clear bss
   unsigned n=__GLOBAL__CONSTRUCTORS_END-__GLOBAL__CONSTRUCTORS_BEG;
   abi::Dtor pool[n];
   abi::Dtor::Stack stack(pool,n); 
   Mod::start();
   stack.finalize();
   while (true)
   {
   }//while
  }
 }
}
