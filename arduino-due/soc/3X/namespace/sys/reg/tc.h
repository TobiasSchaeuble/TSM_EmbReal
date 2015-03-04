#pragma once
//--------------------------
//tc 
//(c) H.Buchmann FHNW 2014
//[1] doc/at91sam3x.pdf
//--------------------------
INTERFACE(sys_reg_tc,$Id$)
#include "sys/hwreg.h"
namespace sys
{
 namespace reg
 {
  struct TC
  {
   enum Channel {CH0,CH1,CH2};
   
   enum CLK     {MCK_2,MCK_8,MCK_32,MCK_128,SLCK}; //bits 0..2 of CMR
   struct
   {
    unsigned CCR;    // Channel Control Register
    unsigned CMR;    // Channel Mode Register
    unsigned SMMR;   // Stepper Motor Mode Register
    unsigned Res0;   // Reserved
    unsigned CV;     // Counter Value
    unsigned RA;     // Register A
    unsigned RB;     // Register B
    unsigned RC;     // Register C
    unsigned SR;     // Status Register
    unsigned IER;    // Interrupt Enable Register
    unsigned IDR;    // Interrupt Disable Register
    unsigned IMR;    // Interrupt Mask Register
    Res<unsigned,0x30,0x40> Res1; 
    
   } channel[3];
   unsigned BCR;     // Block Control Register         0xc0
   unsigned BMR;     // Block Mode Register
   unsigned QIER;    // QDEC Interrupt Enable Register
   unsigned QIDR;    // QDEC Interrupt Disable Register
   unsigned QIMR;    // QDEC Interrupt Mask Register
   unsigned QISR;    // QDEC Interrupt Status Register
   unsigned FMR;     // Fault Mode Register
  };
  
  extern volatile TC TC0;
  extern volatile TC TC1;
  extern volatile TC TC2;
  
 }
}//namespace sys
