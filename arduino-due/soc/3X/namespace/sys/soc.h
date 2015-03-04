#pragma once
//--------------------------
//soc system on chip
//(c) H.Buchmann FHNW 2014
// [1] superfluous/eo3s/soc/AT91SAM/3X/doc/at91sam3x.pdf
//--------------------------
INTERFACE(sys_soc,$Id$)
#include "sys/cortex-m.h"
#include "sys/trap.h"
#include "sys/reg/pio.h"

namespace sys
{
 class SOC:public CortexM
 {
  public:
   enum PID  //peripherals identifiers [1] 11
   {
    SUPC   = 0, // Supply Controller =SUPC, 
    RSTC   = 1, // Reset Controller =RSTC, 
    RTC    = 2, // Real Time Clock =RTC, 
    RTT    = 3, // Real Time Timer =RTT, 
    WDT    = 4, // Watchdog Timer =WDT, 
    PMC    = 5, // Power Management Controller =PMC, 
    EEFC0  = 6, // Enhanced Flash Controller 0 =EFC0, 
    EEFC1  = 7, // Enhanced Flash Controller 1 =EFC1, 
    UART   = 8, // Universal Asynchronous Receiver Transceiver =UART, 
    SMC    = 9, // Static Memory Controller =SMC, 
    SDRAMC =10, // Synchronous Dynamic RAM Controller
    PIOA   =11, // Parallel I/O Controller A, =PIOA, 
    PIOB   =12, // Parallel I/O Controller B =PIOB, 
    PIOC   =13, // Parallel I/O Controller C =PIOC, 
    PIOD   =14, // Parallel I/O Controller D =PIOD, 
    PIOE   =15, // Parallel I/O Controller E =PIOE,
    PIOF   =16, // Parallel I/O Controller F =PIOF,
    USART0 =17, // USART 0 =USART0, 
    USART1 =18, // USART 1 =USART1, 
    USART2 =19, // USART 2 =USART2, 
    USART3 =20, // USART 3 =USART3, 
    HSMCI  =21, // Multimedia Card Interface =HSMCI, 
    TWI0   =22, // Two-Wire Interface 0 =TWI0, 
    TWI1   =23, // Two-Wire Interface 1 =TWI1, 
    SPI0   =24, // Serial Peripheral Interface =SPI0, 
    SPI1   =25, // Serial Peripheral Interface =SPI1, 
    SSC    =26, // Synchronous Serial Controller =SSC, 

                // sys::reg::tc TC0
    TC0    =27, // Timer Counter 0 =TC0, 
    TC1    =28, // Timer Counter 1 =TC1, 
    TC2    =29, // Timer Counter 2 =TC2, 
                // sys::reg::tc TC1
    TC3    =30, // Timer Counter 3 =TC3, 
    TC4    =31, // Timer Counter 4 =TC4, 
    TC5    =32, // Timer Counter 5 =TC5, 
                // sys::reg::tc TC2
    TC6    =33, // Timer Counter 6 =TC6, 
    TC7    =34, // Timer Counter 7 =TC7, 
    TC8    =35, // Timer Counter 8 =TC8, 

//other notation for TC0,1,2
    TC0_0  =27,
    TC0_1  =28,
    TC0_2  =29,

    TC1_0  =30,
    TC1_1  =31,
    TC1_2  =32,

    TC2_0  =33,
    TC2_1  =34,
    TC2_2  =35,
     
    PWM    =36, // Pulse Width Modulation Controller =PWM, 
    ADC    =37, // ADC Controller =ADC, 
    DACC   =38, // DAC Controller =DACC, 
    DMAC   =39, // DMA Controller =DMAC, 
    UOTGHS =40, // USB OTG High Speed =UOTGHS, 
    TRNG   =41, // True Random Number Generator =TRNG, 
    EMAC   =42, // Ethernet MAC =EMAC, 
    CAN0   =43, // CAN Controller 0 =CAN0, 
    CAN1   =44, // CAN Controller 1 =CAN1, 
    PID_COUNT =45, // Number of peripheral IDs 
   };

   static void clockEnable(PID id);
   static void clockDisable(PID id);

   static void arm();    //the interrupt system
   static void disarm(); //the interrupt system
   static bool isArmed();
   static void install(PID id,sys::Trap*const trap){CortexM::install(id+16,trap);}
                         
   static void arm(PID id){CortexM::arm(id);}
   static void disarm(PID id){CortexM::disarm(id);}
   

//the PIO's
   static volatile reg::PIO PIO_A;
   static volatile reg::PIO PIO_B;
   static volatile reg::PIO PIO_C;
   static volatile reg::PIO PIO_D;
   static volatile reg::PIO PIO_E;
   static volatile reg::PIO PIO_F;
   
  protected:
   SOC():CortexM(TheVector.trap,TheVector.SIZE,trap) 
   {
    arm();
   } 

  private:
   static const VTable::Vector<PID_COUNT>  TheVector;
   sys::Trap* trap[TheVector.SIZE];
 };
}

