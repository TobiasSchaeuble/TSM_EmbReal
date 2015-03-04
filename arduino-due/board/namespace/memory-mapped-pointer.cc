//----------------------
//memory-mapped-pointer
//(c) H.Buchmann FHNW 2015
// [1] AT91SAM ARM-based Flash MCU SAM3X SAM3A Series
//     at91sam3x.pdf
// see section 32 Parallel Input/Output
// [2] http://arduino.cc/en/Hacking/PinMappingSAM3X
//----------------------
IMPLEMENTATION(memory_mapped_pointer,$Id$)
#include "sys/deb/deb.h"
#include "sys/msg.h"
#include "sys/soc.h"

struct PIO       //see [1] 32.7
{
  unsigned PER;  // 0x0000 PIO Enable Register Write-only 
  unsigned PDR;  // 0x0004 PIO Disable Register Write-only 
  unsigned PSR;  // 0x0008 PIO PSR Status Register 
  unsigned RES0; // 0x000C Reserved 
  unsigned OER;  // 0x0010 Output Enable Register Write-only 
  unsigned ODR;  // 0x0014 Output Disable Register Write-only 
  unsigned OSR;  // 0x0018 Output Status Register Read-only 0x0000 0000
  unsigned RES1; // 0x001C Reserved 
  unsigned IFER; // 0x0020 Glitch Input Filter Enable Register Write-only 
  unsigned IFDR; // 0x0024 Glitch Input Filter Disable Register Write-only 
  unsigned IFSR; // 0x0028 Glitch Input Filter Status Register Read-only 0x0000 0000
  unsigned RES2; // 0x002C Reserved 
  unsigned SODR; // 0x0030 Set Output Data Register Write-only 
  unsigned CODR; // 0x0034 Clear Output Data Register Write-only 
  unsigned ODSR; // 0x0038 Output Data Status Register Read-only or (2) Read-write 
  unsigned PDSR; // 0x003C Pin Data Status Register Read-only (3)
  unsigned IER;  // 0x0040 Interrupt Enable Register Write-only 
  unsigned IDR;  // 0x0044 Interrupt Disable Register Write-only 
  unsigned IMR;  // 0x0048 Interrupt Mask Register Read-only 0x00000000 PIO_ISR Read-only 0x00000000 (4)
  unsigned ISR;  // 0x004C Interrupt Status Register 
  unsigned MDER; // 0x0050 Multi-driver Enable Register Write-only 
  unsigned MDDR; // 0x0054 Multi-driver Disable Register Write-only 
  unsigned MDSR; // 0x0058 Multi-driver Status Register Read-only 0x00000000
  unsigned RES3; // 0x005C Reserved
  unsigned PUDR; // 0x0060 Pull-up Disable Register Write-only 
  unsigned PUER; // 0x0064 Pull-up Enable Register Write-only 
  unsigned PUSR; // 0x0068 Pad Pull-up Status Register Read-only 0x00000000
  unsigned RES4; // 0x006C Reserved
};


class Demo
{
 static Demo demo;
 static const unsigned TX_LED=1<<21; //bit number 21 of PIOA
 static volatile PIO*const pioA;              //declaration  
 static const unsigned INPUT =1<<25; //Due Pin2 see [2] PIOB
 static volatile PIO*const pioB;
 
//#pragma GCC optimize ("-O0")
 void init();
//#pragma GCC optimize ("-O0")
 void menu();
//#pragma GCC optimize ("-O0")
 void read();
 Demo();  //the constructor
};


Demo Demo::demo;  //instance created constructor called

volatile PIO*const Demo::pioA=(volatile PIO*const)0x400e0e00u; 
                    //cast      see [1] Fig 8.1
volatile PIO*const Demo::pioB=(volatile PIO*const)0x400e1000;
                    //cast      see [1] Fig 8.1

void Demo::init()
{
 //enable pin TX_LED as output see [1] 32.7.1
 pioA->PER=TX_LED; //setting as in|output
 pioA->OER=TX_LED; //setting as output
//clock must be enabled for input [1] 32.4.2
 sys::SOC::clockEnable(sys::SOC::PIOB);
 pioB->PER=INPUT;  //setting as in|output
 pioB->ODR=INPUT;  //setting as input
}

void Demo::read()
{
 unsigned inp=pioB->PDSR & INPUT;
 sys::msg<<io::ascii::hex()<<inp<<"\n";
 while(true)
 {
  unsigned inp1=pioB->PDSR & INPUT;
  if (inp1!=inp)
     {
      inp=inp1;
      sys::msg<<io::ascii::hex()<<inp<<"\n";
     }
 }
}

void Demo::menu()
{
 while(true)
 {
  sys::msg<<"memory-mapped-pointer\n"
            "            0: set   led\n"
	    "            1: clear led\n"
	    "            2: toggle led\n"
	    "            3: read input\n"
	    "your choice:";
	    
  switch(sys::deb::get()) //read a character
  {
   case '0':
    pioA->SODR=TX_LED;  //set bit
   break;
   
   case '1':
    pioA->CODR=TX_LED;  //clear bit
   break;
   
   case '2':
    sys::msg<<"TODO\n";
   break;
   
   case '3':
    read();
   break;
  }
 }
}

Demo::Demo()
{
 init();
 menu();
}

