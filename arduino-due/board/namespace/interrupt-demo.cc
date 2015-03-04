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
#include "sys/reg/nvic.h"           //the registers
/*--------------------------------------  objective
 Nested Vectored Interrupt Controller NVIC
 reading the pending bit
*/  

//our interrupt source:
extern volatile struct {  //see [2] B3.3.2
		 unsigned CSR;
		 unsigned RVR;
		 unsigned CVR;
		 unsigned CALIB;
		} TICK;


typedef void (*Trap)(); //the callback 
                        //called by hardware

extern volatile Trap* VTOR; //its a hardwareregister

class Demo
{
 static Demo demo;
 Demo();
 static void tickInit();
 static const unsigned TRAPN=16+45; 
 static alignas(1<<8) Trap vectorTable[TRAPN]; //see [1] Table 12-3
                                            //        12.21.5
					    //an array of call-backs
 template<unsigned N>  //using a template
 static void onTrap()
 {
  sys::msg<<"Trap# "<<N<<"\n";
 }
 
};

alignas(1<<8) Trap Demo::vectorTable[TRAPN]=
{
onTrap<0>,    //not used 
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

onTrap<16>,  //numbering see [1] Table 11-1. PID 0
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
onTrap<43>, //16+27 the trap number of Timer Counter TC0
            //pending bit 27  
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
onTrap<60>,  //CAN1
};


void Demo::tickInit() //see [2] Table B3-30
{
 TICK.RVR=(1<<24)-1; //the maximal count
 TICK.CSR=(1<<2)| //CLKSOURCE SysTick
          (1<<0); //enable
 TICK.IER=0xff; //enable all 
}

Demo Demo::demo;

Demo::Demo()
{
 sys::msg<<"interrupt-demo\n"
         <<(void*)vectorTable<<"\n"; //show address of vectorTable
	  //check alignement|bit 29 see [1] 12.21.5
 sys::msg<<"VTOR before = "<<(void*)VTOR<<"\n";
 VTOR=vectorTable;	  
 sys::msg<<"VTOR  after = "<<(void*)VTOR<<"\n";
 tickInit();
 //checking bit 27 in 
 unsigned ispr0= sys::reg::NVIC.ISPR[0]; 
 sys::msg<<io::ascii::hex()<<ispr0<<"\n";
 while(true)
 {
  unsigned ispr= sys::reg::NVIC.ISPR[0]; 
  if (ispr0!=ispr)
     {
      ispr0=ispr;
      sys::msg<<io::ascii::hex()<<ispr0<<"\n";
     }
 }
}
