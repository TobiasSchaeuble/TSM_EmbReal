#pragma once
//-----------------------------
//scs system control space
//(c) H.Buchmann FHNW 2013
//[1] superfluous/eo3s/arm/doc/DDI0403D_arm_architecture_v7m_reference_manual_errata_markup_1_0.pdf
//-----------------------------
INTERFACE(sys_reg_scs,$Id$)
#include "sys/hwreg.h"
#include "sys/vtable.h"

namespace sys
{
 namespace reg
 {
  extern volatile struct			//0xe000e000 size 4KiB 0x1000
  {
	 unsigned MCR;	   //0xe000e000 RW 0x00000000 Master Control
	 unsigned ICTR;	   //0xe000e004 RW Interrupt Controller Type
	 unsigned ACTLR;   //0xe000e008 RW Auxiliary Control Register

   const Res<unsigned,0xe000e00c,0xe000e010> Res0;
   
   struct		   			//0xe000e010
   {
           unsigned CSR;
           unsigned RVR;
           unsigned CVR;
     const unsigned CALIB;
   } TICK; 
   

   const Res<unsigned,0xe000e010+sizeof(TICK),0xe000e100> Res1;
   
   struct                  			//0xe000e100
   {
          unsigned ISER[16];
    const Res<unsigned,0xe000e100+sizeof(ISER),0xe000e180> Res0;
          unsigned ICER[16];	//0xe000e180
    const Res<unsigned,0xe000e180+sizeof(ICER),0xe000e200> Res1;
          unsigned ISPR[16];    //0xe000e200
    const Res<unsigned,0xe000e200+sizeof(ISPR),0xe000e300> Res2;
    const unsigned IABR[16];    //0xe000e300
    const Res<unsigned,0xe000e300+sizeof(IABR),0xE000E400> Res3;
          unsigned IPR[124];	//0xE000E400
   } NVIC;
   
   const Res<unsigned,0xe000e100+sizeof(NVIC),0xe000ed00> Res2;
   
   struct 					//0xe000ed00
   {
    const unsigned CPUID;  // 0xe000ed00 RO IMPLEMENTATION CPUID Base Register on page B3-713.
	  unsigned ICSR;   // 0xe000ed04 RW 0x00000000 Interrupt Control and State Register, ICSR on
    const VTable::Entry** VTOR;   // 0xe000ed08 RW 0x00000000 a Vector Table Offset Register, VTOR on page B3-716.
	  unsigned AIRCR;  // 0xe000ed0c RW Application Interrupt and Reset Control Register,
	  unsigned SCR;    // 0xe000ed10 RW 0x00000000 System Control Register, SCR on page B3-718.
	  unsigned CCR;    // 0xe000ed14 RW 0x00000000 Configuration and Control Register, CCR on
	  unsigned SHPR1;  // 0xe000ed18 RW 0x00000000 System Handler Priority Register 1, SHPR1 on
	  unsigned SHPR2;  // 0xe000ed1c RW 0x00000000 System Handler Priority Register 2, SHPR2 on
	  unsigned SHPR3;  // 0xe000ed20 RW 0x00000000 System Handler Priority Register 3, SHPR3 on
	  unsigned SHCSR;  // 0xe000ed24 RW 0x00000000 System Handler Control and State Register, SHCSR on
	  unsigned CFSR;   // 0xe000ed28 RW 0x00000000 Configurable Fault Status Register, CFSR on
	  unsigned HFSR;   // 0xe000ed2c RW 0x00000000 HardFault Status Register, HFSR on page B3-732.
	  unsigned DFSR;   // 0xe000ed30 RW 0x00000000 c Debug Fault Status Register, DFSR on page C1-828.
	  unsigned MMFAR;  // 0xe000ed34 RW UNKNOWN MemManage Fault Address Register, MMFAR on
	  unsigned BFAR;   // 0xe000ed38 RW UNKNOWN BusFault Address Register, BFAR on page B3-734.
	  unsigned AFSR;   // 0xe000ed3c RW UNKNOWN Auxiliary Fault Status Register, AFSR on page B3-735,
    const Res<unsigned,0xE000ED40,0xE000ED88> Res0;
          unsigned CPACR;  // 0xE000ED88 RW UNKNOWN Coprocessor Access Control Register, CPACR on
   } SCB;

   
   const Res<unsigned,0xe000ed00+sizeof(SCB),0xe000ed90> Res3;

   struct 					//0xe000ed90
   {
    const unsigned TYPE;
	  unsigned CTRL;
	  unsigned RNR;
	  unsigned RBAR;
	  unsigned RASR;
	  unsigned RBAR_A1;
	  unsigned RASR_A1;
	  unsigned RBAR_A2;
	  unsigned RASR_A2;
	  unsigned RBAR_A3;
	  unsigned RASR_A3;
   } MPU;
  
   const Res<unsigned,0xe000ed90+sizeof(MPU),0xe000ef00> Res4;   

         unsigned STIR;	   //0xe000ef00 WO Software Triggered Interrupt 
   const Res<unsigned,0xe000ef04,0xe000efd0> Res5;
   const unsigned PID[8];  //0xe000efd0 RO Peripheral Identification R
   const unsigned CID[4];  //0xe000eff0 RO Component Identification
   
  } SCS;
 }//namespace reg
}//namespace sys
