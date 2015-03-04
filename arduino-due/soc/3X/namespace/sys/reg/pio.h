#pragma once
//---------------------------
//pio
//(c) H.Buchmann FHNW 2014
//common
//see doc/at91sam3x.pdf 32.7
//---------------------------
INTERFACE(sys_reg_pio,$Id$)
#include "sys/reg/pio0.h"
#include "sys/hwreg.h"
namespace sys
{
 namespace reg
 {
  struct PIO:PIO0
  {
   unsigned ABSR;    // 0x0070 Peripheral AB Select Register Read-Write 0x00000000
   Res<unsigned,0x0074,0x0080> RES0;
   unsigned SCIFSR;  // 0x0080 System Clock Glitch Input Filter Select Register Write-Only 
   unsigned DIFSR;   // 0x0084 Debouncing Input Filter Select Register Write-Only 
   unsigned IFDGSR;  // 0x0088 Glitch or Debouncing Input Filter Clock Selection Status Register Read-Only 0x00000000
   unsigned SCDR;    // 0x008C Slow Clock Divider Debouncing Register Read-Write 0x00000000
   Res<unsigned,0x0090,0x00A0> RES1;
   unsigned OWER;    // 0x00A0 Output Write Enable Write-only 
   unsigned OWDR;    // 0x00A4 Output Write Disable Write-only 
   unsigned OWSR;    // 0x00A8 Output Write Status Register Read-only 0x00000000
   unsigned RES2;    // 0x00AC Reserved
   unsigned AIMER;   // 0x00B0 Additional Interrupt Modes Enable Register Write-Only 
   unsigned AIMDR;   // 0x00B4 Additional Interrupt Modes Disables Register Write-Only 
   unsigned AIMMR;   // 0x00B8 Additional Interrupt Modes Mask Register Read-Only 0x00000000
   unsigned RES3;    // 0x00BC Reserved
   unsigned ESR;     // 0x00C0 Edge Select Register Write-Only 
   unsigned LSR;     // 0x00C4 Level Select Register Write-Only 
   unsigned ELSR;    // 0x00C8 Edge/Level Status Register Read-Only 0x00000000
   unsigned RES4;    // 0x00CC Reserved 
   unsigned FELLSR;  // 0x00D0 Falling Edge/Low Level Select Register Write-Only 
   unsigned REHLSR;  // 0x00D4 Rising Edge/ High Level Select Register Write-Only 
   unsigned FRLHSR;  // 0x00D8 Fall/Rise - Low/High Status Register Read-Only 0x00000000
   unsigned RES5;    // 0x00DC Reserved 
   unsigned LOCKSR;  // 0x00E0 Lock Status Read-Only 0x00000000
   unsigned WPMR;    // 0x00E4 Write Protect Mode Register Read-write 0x0
   unsigned WPSR;    // 0x00E8 Write Protect Status Register Read-only 0x0 
//some helpful methods
   enum Function {IN,OUT,PERIPH_A,PERIPH_B};
   void set(Function f,unsigned pins) volatile;
  };
  
  extern volatile PIO PIOA,PIOB,PIOC,PIOD,PIOE,PIOF; //see layout.ld
 }
}
