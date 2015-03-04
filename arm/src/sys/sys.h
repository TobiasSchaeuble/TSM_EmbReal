#pragma once
/*-----------------------------
 reg status and system control registers
 see [RealViewEmulationBaseboard] 4.3
 (c) H.Buchmann FHNW 2012
 $Id$
 ------------------------------*/
#include <sys/def-register.h>

extern volatile 
struct
{
VAR(ID             ,0x10000000,RO,-);/*System Identity. See ID Register  SYS_ID on page 4-13. */
VAR(SW             ,0x10000004,RO,-);/*Bits [7:0] map to S6 (user switches). See Switch Register  SYS_SW on page 4-14.*/ 
VAR(LED            ,0x10000008,RW,-);/*Bits [7:0] map to user LEDs (located next to S6). See LED Register  SYS_LED on page 4-15.*/ 
VAR(OSC[5]         ,0x1000000C,RW,-);/*Settings for the ICS307 programmable oscillator chip Lockable OSC0. See Oscillator registers  SYS_OSCx on page 4-15.*/ 
VAR(LOCK           ,0x10000020,RW,-);/*Write 0xA05F to unlock. See Lock Register, SYS_LOCK on page 4-16.*/ 
VAR(_100HZ         ,0x10000024,RO,-);/*100Hz counter. See 100Hz Counter, SYS_100HZ on page 4-17. */
VAR(CONFIGDATA[2]  ,0x10000028,RW,-);/*This region is reserved for registers that are used to
                                    configure the clocks and clock dividers on the attached
                                    Core Tiles. The location and function of the registers
                                    depends on the tile fitted and the FPGA image. See
                                    SYS_CONFIGDATAx on page 4-17.*/ 

union{
VAR(FLAGS          ,0x10000030,RO,-);/*General-purpose flags (reset by any reset). See Flag registers, SYS_FLAGx and SYS_NVFLAGx on page 4-19.*/ 
VAR(FLAGSSET       ,0x10000030,WO,-);/*Set bits in general-purpose flags.*/ 
};
VAR(FLAGSCLR       ,0x10000034,WO,-);/*Clear bits in general-purpose flags.*/ 
union{
VAR(NVFLAGS        ,0x10000038,RO,-);/*General-purpose nonvolatile flags (reset only on power up).*/ 
VAR(NVFLAGSSET     ,0x10000038,WO,-);/*Set bits in general-purpose nonvolatile flags.*/ 
};
VAR(NVFLAGSCLR     ,0x1000003C,WO,-);/*Clear bits in general-purpose nonvolatile flags.*/ 
VAR(Res            ,0x10000040,RO,-); /* not documented */
VAR(PCICTL         ,0x10000044,RW,-);/*Read returns a HIGH in bit [0] if a PCI board is present in
                                    the expansion backplane. See PCI Control Register,
                                    SYS_PCICTL on page 4-20.*/ 
VAR(MCI            ,0x10000048,RO,-);/*This was the register for the \u201ccard present\u201d and \u201cwrite
                                    enabled\u201d status for the MCI card on the PB926EJ-S
                                    development board and is retained for compatibility.
                                    Use GPIO 2 to read the status of these signals on the
                                    baseboard.*/ 
VAR(FLASH          ,0x1000004C,RW,-);/*Controls write protection of flash devices. See Flash
                                    Control Register, SYS_FLASH on page 4-21.*/ 
VAR(CLCD           ,0x10000050,RW,-);/*Controls LCD power and multiplexing. See CLCD Control
                                    Register, SYS_CLCD on page 4-22.*/ 
VAR(CLCDSER        ,0x10000054,RW,-);/*Control interface to activate the 2.2 inch display on the
                                    LCD adaptor. See 2.2 inch LCD Control Register
                                    SYS_CLCDSER on page 4-23.*/ 
VAR(BOOTCS         ,0x10000058,RO,-);/*Read register returns the current switch settings of switch
                                    S8. See Boot select switch, SYS_BOOTCS on page 4-24.*/ 
VAR(_24MHZ         ,0x1000005C,RO,-);/*32-bit counter clocked at 24MHz. See 24MHz Counter,
                                    SYS_24MHZ on page 4-24.*/ 
VAR(MISC           ,0x10000060,RO,-);/*Miscellaneous control flags. See Miscellaneous flags,
                                    SYS_MISC on page 4-24.*/ 
VAR(DMAPSR0        ,0x10000064,RW,-);/*Selection control for remapping DMA from external
                                    peripherals to DMA channel 0. See DMA peripheral map
                                    registers, SYS_DMAPSRx on page 4-25.*/ 
VAR(DMAPSR1        ,0x10000068,RW,-);/*Selection control for remapping DMA from external
                                    peripherals to DMA channel 1.*/ 
VAR(DMAPSR2        ,0x1000006C,RW,-);/*Selection control for remapping DMA from external
                                    peripherals to DMA channel 2.*/ 
VAR(IOSEL          ,0x10000070,RW,-);/*Selects internal or tile peripheral signals for routing to the
                                    peripheral I/O pins. See Peripheral I/O select, SYS_IOSEL
                                    on page 4-26.*/ 
VAR(PLDCTL[2]      ,0x10000074,RW,-);/*These registers are to configure the attached Core Tiles
                                    (See SYS_PLDCTL[2:1] on page 4-30.).
                                    See the application note for the specific combination of
                                    baseboard and Core Tile for details of these registers */
VAR(Reserved        ,0x1000007C,RO,-); /* Reserved. */
VAR(BUSID           ,0x10000080,RO,-); /* Responds with the AXI/AHB bus ID. This enables
                                          multiprocessor platforms to determine the primary boot
                                          processor. See Bus ID register, SYS_BUSID on page 4-31. */
VAR(PROCID[2]       ,0x10000084,RO,- ); /* Read returns a description for the Core Tile present in tile
                    ,0x10000088,site See Processor ID registers, SYS_PROCID[1:0] on
                            page 4-31. */
VAR(OSCRESET[5]     ,0x1000008C,RW,-); /* Value to load into the SYS_OSC[4:0] registers on a manual
                    ,0x1000009C,reset.
                              At power-on reset, the SYS_OSCRESET[4:0] registers are
                             loaded with the same default value as used for
                            SYS_OSC[4:0].*/
#if 0
Core Tile configuration 0x100000A0,RW,-, This region can contain registers that are used for power
(SYS_VOLTAGE[7:0]) ,0x100000BC,management and voltage monitoring of the attached Core
                             Tiles. The location and function of the registers depends on
                            the tile fitted and the FPGA image. See
                           SYS_VOLTAGE[7:0] on page 4-33.
                          See the application note for the specific combination of
                         baseboard and Core Tile for details of these registers.
SYS_TEST_OSC[4:0]  0x100000C0,u2013 RO 32-bit counter clocked from ICS307 oscillators. See
                   0x100000D0,Oscillator test registers, SYS_TEST_OSCx on page 4-34.


#endif
} SYS; 

extern void sys_undef();            /* executes undef instruction */

#if 0
/* TODO make it working change architecture */
inline void sys_irq_enable()
{
 asm
 (
  "\t cpsie i\n" 
  :
  :
 );
}

inline  void sys_fiq_enable()
{
 asm
 (
  "\t cpsie f\n" 
  :
  :
 );
}
#endif



