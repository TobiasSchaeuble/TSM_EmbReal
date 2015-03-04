#pragma once
//-----------------------
//sysdebug 
//see deblow.h
//(c) H.Buchmann FHSO 2001
//$Id: deb.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//-----------------------
//not a normal module INTERFACE/IMPLEMENTATION
#include "sys/deb/deblow.h"

//#define SYS_DEB_DEBUGGER

namespace sys
{
 namespace deb //debug
 {
#ifdef SYS_DEB_DEBUGGER
//------------------------------------------ debug
  struct Debugger
  {
   virtual void onDebug()=0;
   virtual ~Debugger();
  };
  
  extern bool Debug;
  extern Debugger* debugger;
#endif

  void out(const char s[]); //zero terminated
  void out(unsigned val);  
  void out(int val);
  void newln();

  template<typename T>
  void outln(T val){out(val);newln();}
  
  void out(const void* val);
  void out(const char key[],unsigned val);
  void out(const char key[],const unsigned val[],unsigned len);
  void out(const char key[],const char val[]); //zero terminated
  void out(const char key[],const void* val);
  void hex(unsigned short val);
  void hex(unsigned char ch);
  void hex(unsigned val);
  void hex(long long unsigned val);
  inline void hex(void* val){out(val);}
  void hex(const char key[],unsigned val);
  void hex(const char key[],unsigned* val,unsigned len);
  inline void hex(const char key[],void* val){out(key,val);}
  void dump(const unsigned char data[],unsigned len);
  void dump(const char s[],unsigned len);
  void pressAnyKey(const char msg[]);
  void waitForKey(char ch); //useful for starting
  void emergency(const char msg[])__attribute__((noreturn));
  
  inline void emergency(const char msg[])
  {
   out(msg);halt();
  }
 }
}
