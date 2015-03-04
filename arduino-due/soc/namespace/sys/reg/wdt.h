#pragma once
//----------------------
//wdt watch dog timer
//(c) H.Buchmann FHNW 2014
//----------------------
INTERFACE(sys_reg_wdt,$Id$)
namespace sys
{
 namespace reg
 {
  extern volatile struct
  {
   unsigned CR;
   unsigned MR;
   unsigned SR;
  } WDT;
 }
}
