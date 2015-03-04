//------------------------
//led-demo
//(c) H.Buchmann FHNW 2014
//------------------------
IMPLEMENTATION(led_demo,$Id$)
#include "sys/msg.h"
#include "sys/led.h"
#include "sys/deb/deb.h"

class Demo
{
 static Demo demo;
 Demo();
};


Demo Demo::demo;

Demo::Demo()
{
 static const char Menu[]=
 "            0:TX\n"
 "            1:L\n"
 "            2:RX\n"
 "            s:set\n"
 "            c:clr\n"
 "            t:tgl\n"
 "your choice: "; 
 
 static const char* LED[]={"TX","L","RX"};
 sys::LED::ID led=sys::LED::TX;
 while(true)
 {

  sys::msg<<"LED Test "<<LED[led]<<"\n"
          <<Menu;
  switch(sys::deb::get())
  {
   case '0':
    led=sys::LED::TX;
   break;
   case '1':
    led=sys::LED::L;
   break;
   case '2':
    led=sys::LED::RX;
   break;
   
   case 's':
    sys::LED::set(led);
   break;
   
   case 'c':
    sys::LED::clr(led);
   break;
   case 't': 
    sys::LED::tgl(led);
   break;
  }
  sys::msg<<"\n";
 }
}
