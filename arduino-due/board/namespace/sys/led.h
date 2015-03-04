#pragma once
//----------------------------
//led
//(c) H.Buchmann FHNW 2014
//an exercise in function calls
//----------------------------
INTERFACE(sys_led,$Id$)
#include "sys/reg/pio.h"
namespace sys
{
 class LED
 {
  public:
   enum ID {TX,
	    L ,
            RX
	   };
   static void set(ID led);
   static void clr(ID led);
   static void tgl(ID led);

  private:
   static LED led; //for initialization
   static const struct {unsigned pin;
                        volatile reg::PIO& pio;
			void (*set)(volatile reg::PIO&,unsigned);
			void (*clr)(volatile reg::PIO&,unsigned);
			} Desc[];
   static void sodr(volatile reg::PIO& pio,unsigned led); //the call backs
   static void codr(volatile reg::PIO& pio,unsigned led); //the call backs
   LED(); 
 };
}//namespace sys
