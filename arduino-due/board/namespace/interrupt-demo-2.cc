//----------------------------
//interrupt-demo
//(c) H.Buchmann FHNW 2015
// [1] AT91SAM ARM-based Flash MCU SAM3X SAM3A Series
//     at91sam3x.pdf
// [2] ARMv7-M Architecture Reference Manual
//     DDI0403D_arm_architecture_v7m_reference_manual_errata_markup_1_0.pdf
// interrupt source: TimerCounter TC
//----------------------------
IMPLEMENTATION(interrupt_demo,$Id$)
#include "sys/deb/deb.h"
#include "sys/msg.h"
#include "sys/reg/tc.h" 
#include "sys/soc.h"
/*--------------------------------------  objective
 The TimerCounter TC counts
   - polling the status register SR 
   - calling onTick()
*/  

/*--------------------------------------- your notes
*/


class Demo
{
 static Demo demo;
 static const unsigned CPCS=(1<<4); //bit 4 in SR [1] 37.7.17
 static const sys::reg::TC::Channel CH=sys::reg::TC::CH0;  
                                     //our channel of TC0 
                                     //see [1] Chapter 37
 
 Demo();
 static void onTick(); 
 static void initTC();
};

void Demo::initTC()
{
 sys::SOC::clockEnable(sys::SOC::TC0_0);
 sys::reg::TC0.channel[CH].CMR= sys::reg::TC::MCK_32 |   
                          (1<<15) |     //WAVE=1
			  (2<<13) |     //UP_RC
                                0;
 sys::reg::TC0.channel[CH].RC=(84*1000000)/32;
 sys::reg::TC0.channel[CH].CCR=(1<<0)|  //CLKEN
                               (1<<2)|  //SWTRG    
                                   0;
}

void Demo::onTick()
{ 
 static unsigned count=0; //only visible in onTick
 sys::msg<<"tick="<<count<<"\n";
 ++count;
}

Demo Demo::demo;

Demo::Demo()
{
 sys::msg<<__FILE__ "\n";
 initTC();
 while(true)
 {
  if (sys::reg::TC0.channel[CH].SR&CPCS)
     {
      onTick();
     }
 }
}
