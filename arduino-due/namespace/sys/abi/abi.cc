//----------------------
//abi application binary interface
//(c) H.Buchmann FHNW 2012
//$Id: gnu.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//see http://www.codesourcery.com/cxx-abi/abi.html
// 
//----------------------
#include "sys/abi/abi.h"
#include "sys/deb/deb.h"

namespace sys
{
 namespace abi
 {
  Dtor::Stack* Dtor::stack=0;
  
  Dtor::Stack::Stack(Dtor*const dtor,unsigned size)
  :pool(dtor)
  ,top(size)
  ,sp(size)
  {
   sys::deb::newln();
   stack=this;
  }

  void Dtor::Stack::push(void (*dtor)(void*),void* self)
  {
#if 0
   sys::deb::out("------------ push ");
   sys::deb::out(sp);
   sys::deb::out("\t");
   sys::deb::hex((void*)dtor);
   sys::deb::out("\t");
   sys::deb::hex((void*)self);
   sys::deb::newln();
#endif  
   Dtor* d=pool + --sp;
   d->dtor=dtor;
   d->self=self;
  }

  void Dtor::push(void (*dtor)(void*),void* self)
  {
   if (stack==0)
      {
       deb::out(__FILE__":");
       deb::out(__LINE__);
       deb::out(":not initialized\n");
       deb::halt();
      }
   stack->push(dtor,self);
  }
  
  void Dtor::Stack::finalize()
  {
   while(sp<top)
   {
    Dtor* d=pool+ sp++;
 #if 0
    sys::deb::out("------------ finalize ");
    sys::deb::out(sp);
    sys::deb::out("\t");  
    sys::deb::hex((void*)d->dtor);
    sys::deb::out("\t");
    sys::deb::hex((void*)d->self);
    sys::deb::newln();
 #endif
    d->dtor(d->self);
   }
  }

 }//namespace abi
}//namespace sys

extern "C" 
{
 void* __dso_handle=&__dso_handle;
 
 void __cxa_pure_virtual()
 {
  sys::deb::out("pure virtual called");
 }

 int __cxa_guard_acquire(int* guard_object)
 {
//  sys::deb::hex(__PRETTY_FUNCTION__,(unsigned)guard_object);
//  sys::deb::newln();
//  sys::deb::halt();
  return *guard_object++==0;
 }

 void __cxa_guard_release(int* guard_object)
 {
//  sys::deb::hex(__PRETTY_FUNCTION__,(unsigned)guard_object);
//  sys::deb::newln();
//  sys::deb::halt();
 }

 int __cxa_atexit ( void (*f)(void *), void *p, void *d )
 {
#if 0
  sys::deb::out(__PRETTY_FUNCTION__);
  sys::deb::out((void*)f);
  sys::deb::out('\t');
  sys::deb::out(p);
  sys::deb::out('\t');
  sys::deb::out(d);
  sys::deb::newln();
#endif  
  sys::abi::Dtor::push(f,p);
  return 0;
 }
 
 int __aeabi_atexit(void *p, void  (*f)(void *),  void *d )
 {
  sys::abi::Dtor::push(f,p);
  return 0;
 }
}


