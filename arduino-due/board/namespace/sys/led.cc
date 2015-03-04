//----------------------------
//led
//(c) H.Buchmann FHNW 2014
//----------------------------
IMPLEMENTATION(sys_led,$Id$)
#include "sys/led.h"
#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/soc.h"
#include "sys/reg/pio.h"

//#define SYS_LED_TEST

namespace sys
{
 decltype(LED::Desc) LED::Desc={ 
                  {1<<21,SOC::PIO_A,LED::codr,LED::sodr}, //TX
                  {1<<27,SOC::PIO_B,LED::sodr,LED::codr},
		  {1<<30,SOC::PIO_C,LED::codr,LED::sodr}}; //RX
 LED LED::led;
 
 LED::LED()
 {
  for(const auto& d:Desc)
  {
   d.pio.set(reg::PIO::OUT,d.pin);
   d.pio.OWER=d.pin; //outpt write enable
   d.clr(d.pio,d.pin);
  }
 }
 
 void LED::set(ID led)
 {
  const auto& d=Desc[led];
  d.set(d.pio,d.pin);
 }
 
 void LED::clr(ID led)
 {
  const auto& d=Desc[led];
  d.clr(d.pio,d.pin);
 }
 
 void LED::sodr(volatile reg::PIO& pio,unsigned pin)
 {
  pio.SODR=pin;
 }

 void LED::codr(volatile reg::PIO& pio,unsigned pin)
 {
  pio.CODR=pin;
 }
 
 void LED::tgl(ID led)
 {
  const auto& d=Desc[led];
  d.pio.ODSR^=d.pin;
 } 
}//namespace sys

#ifdef SYS_LED_TEST
//moved to led-demo
#endif
