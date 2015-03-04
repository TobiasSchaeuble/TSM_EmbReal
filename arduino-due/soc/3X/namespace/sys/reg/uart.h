#pragma once
//--------------------------
//uart
//(c) H.Buchmann FHNW 2015
//--------------------------
INTERFACE(sys_reg_uart,$Id$)
#include "sys/reg/uart0.h"
namespace sys
{
 namespace reg
 {
  extern volatile UART0 UART;
 }//namespace reg
}//namespace sys
