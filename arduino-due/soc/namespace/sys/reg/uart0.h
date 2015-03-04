#pragma once
//-------------------
//uart common 
//(c) H.Buchmann FHNW 2014
//common
//see doc/at91sam3x.pdf 35.6
//see doc/sam9260.pdf   32.7
//--------------------------
INTERFACE(sys_reg_uart0,$Id$)
namespace sys
{
 namespace reg
 {
  struct UART0
  {
   unsigned CR;   // 0x0000 Control Register UART_CR Write-only 
   unsigned MR;   // 0x0004 Mode Register UART_MR Read-write 0x0
   unsigned IER;  // 0x0008 Interrupt Enable Register UART_IER Write-only 
   unsigned IDR;  // 0x000C Interrupt Disable Register UART_IDR Write-only 
   unsigned IMR;  // 0x0010 Interrupt Mask Register UART_IMR Read-only 0x0
   unsigned SR;   // 0x0014 Status Register UART_SR Read-only \u2013
   unsigned RHR;  // 0x0018 Receive Holding Register UART_RHR Read-only 0x0
   unsigned THR;  // 0x001C Transmit Holding Register UART_THR Write-only 
   unsigned BRGR; // 0x0020 Baud Rate Generator Register UART_BRGR Read-write 0x0  
  };
 }
}
