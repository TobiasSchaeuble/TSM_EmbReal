//----------------------------
//interrupt-demo
//(c) H.Buchmann FHNW 2015
// [1] AT91SAM ARM-based Flash MCU SAM3X SAM3A Series
//     at91sam3x.pdf
// [2] ARMv7-M Architecture Reference Manual
//     DDI0403D_arm_architecture_v7m_reference_manual_errata_markup_1_0.pdf
//----------------------------
IMPLEMENTATION(interrupt_demo,$Id$)
#include "sys/deb/deb.h"
#include "sys/msg.h"
#include "sys/reg/tc.h" 
#include "sys/soc.h"
#include "sys/reg/nvic.h"
/*--------------------------------------  objective
 enable the interrupt arm
 replace onTrap<43> with onTick
*/  

/*--------------------------------------- your notes
*/

typedef void (*Trap)(); //the call-back

extern Trap* VTOR; //an array of Trap's  see [1] 12.21.5

class Demo
{
 static Demo demo;
 static const unsigned CPCS=(1<<4); //bit 4 in SR [1] 37.7.17
 static const unsigned TC0_ID=27;
 static const sys::reg::TC::Channel CH=sys::reg::TC::CH0;  
                                     //our channel of TC0 
                                     //see [1] Chapter 37
 
 Demo();
 static void onTick(); 
 static void initTC();
 static const unsigned TRAPN=16+45; 
 static alignas (1<<8) Trap vectorTable[TRAPN];
 template<unsigned ID>
 static void onTrap(); //template
};


void Demo::initTC()
{
 sys::SOC::clockEnable(sys::SOC::TC0_0);
 sys::reg::TC0.channel[CH].CMR= sys::reg::TC::MCK_32 |   
                          (1<<15) |     //WAVE=1
			  (2<<13) |     //UP_RC
                                0;
 sys::reg::TC0.channel[CH].RC=(84*1000000)/32;
 sys::reg::TC0.channel[CH].IER=CPCS; //enable interrupt
 sys::reg::TC0.channel[CH].CCR=(1<<0)|  //CLKEN
                               (1<<2)|  //SWTRG    
                                   0;
}

void Demo::onTick()
{ 
 static unsigned count=0; //only visible in onTick
 sys::msg<<"tick="<<count<<"\n";
 ++count;
//read status register for clearing the interrupt
 sys::reg::TC0.channel[CH].SR;
}

template<unsigned ID>
void Demo::onTrap()
{
 sys::msg<<"Trap #"<<ID<<"\n";
}

alignas (1<<8) Trap Demo::vectorTable[]={
onTrap<0>,
onTrap<1>,
onTrap<2>,
onTrap<3>,
onTrap<4>,
onTrap<5>,
onTrap<6>,
onTrap<7>,
onTrap<8>,
onTrap<9>,

onTrap<10>,
onTrap<11>,
onTrap<12>,
onTrap<13>,
onTrap<14>,
onTrap<15>,
onTrap<16>,
onTrap<17>,
onTrap<18>,
onTrap<19>,

onTrap<20>,
onTrap<21>,
onTrap<22>,
onTrap<23>,
onTrap<24>,
onTrap<25>,
onTrap<26>,
onTrap<27>,
onTrap<28>,
onTrap<29>,

onTrap<30>,
onTrap<31>,
onTrap<32>,
onTrap<33>,
onTrap<34>,
onTrap<35>,
onTrap<36>,
onTrap<37>,
onTrap<38>,
onTrap<39>,

onTrap<40>,
onTrap<41>,
onTrap<42>,
onTick,        //onTrap<43>, 
onTrap<44>,
onTrap<45>,
onTrap<46>,
onTrap<47>,
onTrap<48>,
onTrap<49>,

onTrap<50>,
onTrap<51>,
onTrap<52>,
onTrap<53>,
onTrap<54>,
onTrap<55>,
onTrap<56>,
onTrap<57>,
onTrap<58>,
onTrap<59>,

onTrap<60>,
};

Demo Demo::demo;

Demo::Demo()
{
 sys::msg<<__FILE__ "\n";
 initTC();
 sys::msg<<"VTOR before = "<<(void*)VTOR<<"\n"
           "vectorTable = "<<(void*)vectorTable<<"\n";
 VTOR=vectorTable;
 sys::SOC::arm(); //enable the interrupt system 
 sys::reg::NVIC.ISER[0]=(1<<TC0_ID);
 while(true)
 {
  //wait until interrupt
 }
}
