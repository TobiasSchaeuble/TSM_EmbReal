//--------------------------
//soc system on chip
//(c) H.Buchmann FHNW 2014
// [1] superfluous/eo3s/soc/AT91SAM/3X/doc/at91sam3x.pdf
//--------------------------
IMPLEMENTATION(sys_soc,$Id$)
#include "sys/soc.h"
#include "sys/reg/pmc.h"
namespace sys
{
 decltype(SOC::TheVector) SOC::TheVector=
 {
   0,               	//stack pointer
   trapIt,		//  RESET         = 1,
   trapIt, 		//NMI           = 2,
   trapIt, 		//HARD_FAULT    = 3,
   trapIt, 		//MEM_MANAGE    = 4,
   trapIt, 		//BUS_FAULT     = 5,
   trapIt, 		//USAGE_FAULT   = 6,
   trapIt, trapIt,trapIt,trapIt,//reserved    7-10
   trapIt, //SV_CALL       =11,
   trapIt, //DEBUG_MONITOR =12,
   trapIt, //reserved      =13
   trapIt, //PEND_SV       =14,
   trapIt, //SYS_TICK      =15,

   trapIt, //SUPC   = 0, // Supply Controller =SUPC, 
   trapIt, //RSTC   = 1, // Reset Controller =RSTC, 
   trapIt, //RTC    = 2, // Real Time Clock =RTC, 
   trapIt, //RTT    = 3, // Real Time Timer =RTT, 
   trapIt, //WDT    = 4, // Watchdog Timer =WDT, 
   trapIt, //PMC    = 5, // Power Management Controller =PMC, 
   trapIt, //EEFC0  = 6, // Enhanced Flash Controller 0 =EFC0, 
   trapIt, //EEFC1  = 7, // Enhanced Flash Controller 1 =EFC1, 
   trapIt, //UART   = 8, // Universal Asynchronous Receiver Transceiver =UART, 
   trapIt, //SMC    = 9, // Static Memory Controller =SMC, 
   trapIt, //SDRAMC =10, //Synchronous Dynamic RAM Controller
   trapIt, //PIOA   =11, // Parallel I/O Controller A, =PIOA, 
   trapIt, //PIOB   =12, // Parallel I/O Controller B =PIOB, 
   trapIt, //PIOC   =13, // Parallel I/O Controller C =PIOC, 
   trapIt, //PIOD   =14, // Parallel I/O Controller D =PIOD, 
   trapIt, //PIOE   =15, // Parallel I/O Controller E =PIOE,
   trapIt, //PIOF   =16, // Parallel I/O Controller F =PIOF,
   trapIt, //USART0 =17, // USART 0 =USART0, 
   trapIt, //USART1 =18, // USART 1 =USART1, 
   trapIt, //USART2 =19, // USART 2 =USART2, 
   trapIt, //USART3 =20, // USART 3 =USART3, 
   trapIt, //HSMCI  =21, // Multimedia Card Interface =HSMCI, 
   trapIt, //TWI0   =22, // Two-Wire Interface 0 =TWI0, 
   trapIt, //TWI1   =23, // Two-Wire Interface 1 =TWI1, 
   trapIt, //SPI0   =24, // Serial Peripheral Interface =SPI0, 
   trapIt, //SPI1   =25, // Serial Peripheral Interface =SPI1, 
   trapIt, //SSC    =26, // Synchronous Serial Controller =SSC, 
   trapIt, //TC0    =27, // Timer Counter 0 =TC0, 
   trapIt, //TC1    =28, // Timer Counter 1 =TC1, 
   trapIt, //TC2    =29, // Timer Counter 2 =TC2, 
   trapIt, //TC3    =30, // Timer Counter 3 =TC3, 
   trapIt, //TC4    =31, // Timer Counter 4 =TC4, 
   trapIt, //TC5    =32, // Timer Counter 5 =TC5, 
   trapIt, //TC6    =33, // Timer Counter 6 =TC6, 
   trapIt, //TC7    =34, // Timer Counter 7 =TC7, 
   trapIt, //TC8    =35, // Timer Counter 8 =TC8, 
   trapIt, //PWM    =36, // Pulse Width Modulation Controller =PWM, 
   trapIt, //ADC    =37, // ADC Controller =ADC, 
   trapIt, //DACC   =38, // DAC Controller =DACC, 
   trapIt, //DMAC   =39, // DMA Controller =DMAC, 
   trapIt, //UOTGHS =40, // USB OTG High Speed =UOTGHS, 
   trapIt, //TRNG   =41, // True Random Number Generator =TRNG, 
   trapIt, //EMAC   =42, // Ethernet MAC =EMAC, 
   trapIt, //CAN0   =43, // CAN Controller 0 =CAN0, 
   trapIt, //CAN1   =44, // CAN Controller 1 =CAN1, 
 };

 void SOC::clockEnable(PID id)
 {
  if (id<32) reg::PMC.PCER0=(1<<id);
     else    reg::PMC.PCER1=(1<<(id-32));
 }
 
 void SOC::clockDisable(PID id)
 {
  if (id<32) reg::PMC.PCDR0=(1<<id);
     else    reg::PMC.PCDR1=(1<<(id-32));
 }

 void SOC::arm()
 {
  CortexM::cpsIE_i();
  CortexM::cpsIE_f();
 }
 
 void SOC::disarm()
 {
  CortexM::cpsID_i();
  CortexM::cpsID_f();
 }
 

}


