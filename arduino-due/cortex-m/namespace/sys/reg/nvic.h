#pragma once
//---------------------------
//nvic nested vectored interrupt controller
//(c) H.Buchmann FHNW 2014
//[1] superfluous/eo3s/arm/doc/DDI0403D_arm_architecture_v7m_reference_manual_errata_markup_1_0.pdf
//---------------------------
INTERFACE(sys_reg_nvic,$Id$)
#include "sys/hwreg.h"
namespace sys
{
 namespace reg
 {
  extern volatile struct
  {
   unsigned ISER[16]; //Interrupt Set-Enable Registers
   Res<unsigned,0xe140,0xe180> RES0;
   unsigned ICER[16];  //Interrupt Clear-Enable Registers
   Res<unsigned,0xe1c0,0xe200> RES1;
   unsigned ISPR[16];  //Interrupt Set-Pending Registers
   Res<unsigned,0xe240,0xe280> RES2;
   unsigned ICPR[16]; 
//   Res<unsigned,0xe380,0xe400> RES3;
//   unsigned IPR[124];
  } NVIC;
 }
}
