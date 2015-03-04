#pragma once
//----------------------
//abi application binary interface
//see in boards for more specific inmplementation
//(c) H.Buchmann FHNW 2012
//$Id: gnu.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//----------------------
namespace sys
{
 namespace abi
 {
  class Dtor //destructors
  {
   public:
    class Stack
    {
     public:
      Stack(Dtor*const stack,unsigned size);
      void push(void (*dtor)(void*),void* self);
      void finalize();
     private:
      Dtor*const     pool;
      const unsigned top;
      unsigned       sp;
    };
    
    static void push(void (*dtor)(void*),void* self);
    
   private:
    static Stack* stack; 
    void (*dtor)(void*);
    void* self;
  };
 }//namespace abi
}//namespace sys

extern "C" 
{
 void __cxa_pure_virtual();
 void* memcpy(void* to,const void* from,unsigned size);
 void __cxa_pure_virtual();
 int __cxa_guard_acquire(int* guard_object);
 void __cxa_guard_release(int* guard_object);
 int __cxa_atexit ( void (*f)(void *), void *p, void *d );
 int __aeabi_atexit(void *p, void  (*f)(void *),  void *d );
}
