//----------------------------
//interrupt-demo
//(c) H.Buchmann FHNW 2015
// [1] AT91SAM ARM-based Flash MCU SAM3X SAM3A Series
//     at91sam3x.pdf
// [2] ARMv7-M Architecture Reference Manual
//     DDI0403D_arm_architecture_v7m_reference_manual_errata_markup_1_0.pdf
// step by step see git 
// interrupt source:
//  SysTick [2] B3.3
//----------------------------
IMPLEMENTATION(interrupt_demo,$Id$)
#include "sys/deb/deb.h"
#include "sys/msg.h"
#include "sys/reg/tc.h" 
#include "sys/soc.h"
/*--------------------------------------  objective
 The VectorTable
  an array of call-backs
*/  



typedef void (*Trap)(); //the callback 
                        //called by hardware

class Demo
{
 static Demo demo;
 static const sys::reg::TC::Channel CH=sys::reg::TC::CH0;  
                                     //our channel of TC0 
                                     //see [1] Chapter 37
 
 Demo();
 
 static const unsigned CPCS=(1<<4); //bit 4
 static void initTC();
 static void onTick();
 static const unsigned TRAPN=61;  //the number of traps

 template<unsigned N>  //using a template
 static void onTrap()
 {
  sys::msg<<"Trap# "<<N<<"\n";
 }
 
 static Trap vectorTable[TRAPN];
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
 static unsigned cnt=0;
 sys::msg<<"tick "<<cnt<<"\n";
 ++cnt; 
}

Trap Demo::vectorTable[TRAPN]=
{
};

Demo Demo::demo;

Demo::Demo()
{
 sys::msg<<"interrupt-demo\n";
 initTC();
 while(true)
 {
  if (sys::reg::TC0.channel[CH].SR&CPCS)
     {
      onTick();
     }
 }
}
