#pragma once
//---------------------------
//pmc 
//(c) H.Buchmann FHNW 2014
//superfluous/eo3s/soc/AT91SAM/3X/doc/at91sam3x.pdf 29.2.15 
//---------------------------
INTERFACE(sys_reg_pmc,$Id$)
#include "sys/hwreg.h"
namespace sys
{
 namespace reg
 {
  extern volatile struct 
  {
   unsigned SCER;       // 0x0000 System Clock Enable Register Write-only 
   unsigned SCDR;       // 0x0004 System Clock Disable Register Write-only 
   unsigned SCSR;       // 0x0008 System Clock Status Register Read-only 0x0000_0001
   unsigned RES0;       // 0x000C Reserved  
   unsigned PCER0;      // 0x0010 Peripheral Clock Enable Register 0 Write-only 
   unsigned PCDR0;      // 0x0014 Peripheral Clock Disable Register 0 Write-only 
   unsigned PCSR0;      // 0x0018 Peripheral Clock Status Register 0 Read-only 0x0000_0000
   unsigned CKGR_UCKR;  // 0x001C UTMI Clock Register  Read-write 0x1020_0800
   unsigned CKGR_MOR;   // 0x0020 Main Oscillator Register  Read-write 0x0000_0001
   unsigned CKGR_MCFR;  // 0x0024 Main Clock Frequency Register  Read-only 0x0000_0000
   unsigned CKGR_PLLAR; // 0x0028 PLLA Register  Read-write 0x0000_3F00
   unsigned RES1;       // 0x002C Reserved  
   unsigned MCKR;       // 0x0030 Master Clock Register Read-write 0x0000_0001
   unsigned RES2;       // 0x0034 Reserved  
   unsigned USB;        // 0x0038 USB Clock Register Read/Write 0x0000_0000
   unsigned RES3;       // 0x003C Reserved  
   unsigned PCK4;       // 0x0040 Programmable Clock 0 Register Read-write 0x0000_0000
   unsigned PCK1;       // 0x0044 Programmable Clock 1 Register Read-write 0x0000_0000
   unsigned PCK2;       // 0x0048 Programmable Clock 2 Register Read-write 0x0000_0000
   Res<unsigned,0x004C,0x0060> RES5;     
   unsigned IER;        // 0x0060 Interrupt Enable Register Write-only 
   unsigned IDR;        // 0x0064 Interrupt Disable Register Write-only 
   unsigned SR;         // 0x0068 Status Register Read-only 0x0001_0008
   unsigned IMR;        // 0x006C Interrupt Mask Register Read-only 0x0000_0000
   unsigned FSMR;       // 0x0070 Fast Startup Mode Register Read-write 0x0000_0000
   unsigned FSPR;       // 0x0074 Fast Startup Polarity Register Read-write 0x0000_0000
   unsigned FOCR;       // 0x0078 Fault Output Clear Register Write-only 
   Res<unsigned,0x007C,0x00E4> RES6;  
   unsigned WPMR;       // 0x00E4 Write Protect Mode Register Read-write 0x0
   unsigned WPSR;       // 0x00E8 Write Protect Status Register Read-only 0x0
   Res<unsigned,0x00EC,0x0100> RES7;
   unsigned PCER1;      // 0x0100 Peripheral Clock Enable Register 1 Write-only 
   unsigned PCDR1;      // 0x0104 Peripheral Clock Disable Register 1 Write-only 
   unsigned PCSR1;      // 0x0108 Peripheral Clock Status Register 1 Read-only 0x0000_0000
   unsigned PCR;        // 0x010C Read-write 0x0000_0000
  } PMC; //only one 
 }
}
