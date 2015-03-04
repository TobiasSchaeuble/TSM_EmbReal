//----------------------
//deblow
//(c) H.Buchmann FHNW 2014
//----------------------
#include "sys/reg/pio.h"
#include "sys/reg/uart.h"

namespace sys
{
 namespace deb
 {
  extern void wait(unsigned cnt);
  
  static const unsigned LED_TX=(1<<21); //reg::PIOA
  static const unsigned LED_L =(1<<27); //reg::PIOB
  static const unsigned LED_RX=(1<<30); //reg::PIOC

  void init()
  {
   reg::UART.CR=(1<<4)| //REXEN
                (1<<6)| //TXEN
		    0;
  }

#if 0
//works with g++
//works with clang++ -O0
// dont works with clang++ -O2  
  void signal0()  //LED_L
  {
   static const unsigned COUNT=0x80000;
   while(true)
   {
    reg::PIOB.SODR=LED_L;
    for(volatile unsigned i=0;i<COUNT;++i){}
    reg::PIOB.CODR=LED_L;
    for(volatile unsigned i=0;i<COUNT;++i){}
   }
  }
#endif  
  
  static const unsigned COUNT=0x200000;
  
  static void disarm()
  {
   asm volatile
   (
    "cpsid f\n\t"
    "cpsid i\n\t"
    :
    :
   );
  }
  
  void signal0()  //LED_L
  {
   disarm();
   reg::PIOB.PER=LED_L;
   reg::PIOB.OER=LED_L;
   while(true)
   {
    reg::PIOB.SODR=LED_L;
    wait(COUNT);
    reg::PIOB.CODR=LED_L;
    wait(COUNT);
   }
  }

  void signal1() //LED_TX
  {
   disarm();
   reg::PIOA.PER=LED_TX;
   reg::PIOA.OER=LED_TX;
   while(true)
   {
    reg::PIOA.SODR=LED_TX;
    wait(COUNT);
    reg::PIOA.CODR=LED_TX;
    wait(COUNT);
   }
  }
  
  void signal2()
  {
   disarm();
   reg::PIOC.PER=LED_RX;
   reg::PIOC.OER=LED_RX;
   while(true)
   {
    reg::PIOC.SODR=LED_RX;
    wait(COUNT);
    reg::PIOC.CODR=LED_RX;
    wait(COUNT);
   }
  }
  
  void signal3() //LED_L LED_TX
  {
   disarm();
   reg::PIOB.PER=LED_L;
   reg::PIOB.OER=LED_L;
   reg::PIOA.PER=LED_TX;
   reg::PIOA.OER=LED_TX;
   while(true)
   {
    reg::PIOA.SODR=LED_TX;
    reg::PIOB.SODR=LED_L;
    wait(COUNT);
    reg::PIOA.CODR=LED_TX;
    reg::PIOB.CODR=LED_L;
    wait(COUNT);
   }
  }
  
  void out(char ch)
  {
   if (ch=='\n') out('\r'); //handle cr/lf
   while ((reg::UART.SR&(1<<1))==0){}
   reg::UART.THR=ch;
  }
  
  char get()
  {
   while ((reg::UART.SR&(1<<0))==0){}
   return reg::UART.RHR;
  }
  
  bool avail()
  {
   return reg::UART.SR&(1<<0);
  }
  
  void enter()
  {
  }
  
  void halt()
  {
  }
  
 }
}//namespace sys
