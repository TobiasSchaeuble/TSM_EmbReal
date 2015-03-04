//-----------------------
//system wide messages (cerr)
//(c) H.Buchmann FHSO 2003
//$Id: msg.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//-----------------------
IMPLEMENTATION(sys_msg,$Revision: 160 $)
#include "sys/msg.h"
#include "sys/deb/deb.h"
namespace sys
{
 Msg::Msg(io::ascii::Output& out)
 :io::ascii::Writer(out)
 {
 }

 void Msg::onEoL(io::ascii::Output&)
 {
  halt();
 }

 Msg& Msg::error()
 {
  *this<<"**** error: ";
  setEoLListener(*this);
  return *this;
 }
 
 Msg& Msg::warning()
 {
  *this<<"**** warning: ";
  return *this;
 }
 
 void Msg::halt()
 {
  *this<<"**** system halts ****";
  sys::deb::halt();
 }
 
 Msg& Msg::debug()
 {
  sys::deb::enter();
  return *this;
 }
 
}
