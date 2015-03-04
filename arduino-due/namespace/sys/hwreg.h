#pragma once
//--------------------------
//hwreg common templates for hardware register definitions
//(c) H.Buchmann FHNW 2013
//--------------------------
INTERFACE(sys_hwreg,$Id$)
namespace sys
{
//reserved space
 template<typename T,unsigned FROM,unsigned TO>
 struct Res
 {
  static_assert(FROM<=TO,"FROM>TO");
  T r[(TO-FROM)/sizeof(T)];
 }; 

//works only in C11 
 template<unsigned FROM,unsigned TO> using ResW=Res<unsigned,FROM,TO>; 
}//namespace sys
