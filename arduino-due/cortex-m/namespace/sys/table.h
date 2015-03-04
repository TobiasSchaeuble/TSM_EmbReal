#pragma once
//-----------------------
//table
//(c) H.Buchmann FHNW 2014
//-----------------------
INTERFACE(sys_table,$Id$)
namespace sys
{
 typedef void (*Trap)();

 extern void defaultTrap();
 
 struct Table 
 {
  unsigned stackTop;
  Trap     traps[2];
  constexpr Table()
  :stackTop(0x20088000)
  ,traps{defaultTrap,defaultTrap}
  {
  }
 };
}
