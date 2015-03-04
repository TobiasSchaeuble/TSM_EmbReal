#pragma once
//---------------------------
//pio0 common part of AT91
//(c) H.Buchmann FHNW 2014
//common
//see doc/at91sam3x.pdf 32.7
//see doc/sam9260.pdf   29.6
//---------------------------
INTERFACE(sys_reg_pio0,$Id$)
namespace sys
{
 namespace reg
 {
  struct PIO0
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
 }
}
