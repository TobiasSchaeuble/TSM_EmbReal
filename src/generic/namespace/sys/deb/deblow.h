#pragma once
//-----------------------
//debug low level 
//should be implemented in 'board/sys/deb'
//(c) H.Buchmann FHSO 2001
//$Id: deblow.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//-----------------------
namespace sys
{
 namespace deb //debug
 {
//elementary signal methods 
//display a signal and loops   
//coding for two leds green red 

//four different types of blinking
  [[noreturn]] void signal0();
  [[noreturn]] void signal1();
  [[noreturn]] void signal2();
  [[noreturn]] void signal3();

//low level
  extern void wait(unsigned cnt);
  void init();
  [[noreturn]] void halt();       
               //the program halts (whatever it means)
  [[noreturn]] void reset();
               //the program resets (whatever it means)
  void enter();      //enters debug mode normally all interrupts disabled
  void out(char ch); //transmits a char
  char get();        //waits until char ready
  bool avail();      //returns true if char available
  void test();	     //for tests
  void waitUntil();  //something happens
  unsigned getSP(); 
 }
}
