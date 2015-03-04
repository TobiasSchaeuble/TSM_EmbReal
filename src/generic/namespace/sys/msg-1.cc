//------------------------
//msg-1 the default
//(c) H.Buchmann 2005
//$Id: msg-1.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//-----------------------
IMPLEMENTATION(sys_msg_1,$Revision: 160 $)
#include "sys/msg.h"
#include "io/ascii/out.h"
#include "sys/deb/deb.h"

namespace sys
{
 class Msg_1:public Msg
            ,private io::ascii::Output
 {
  private:
   using io::ascii::Output::put;
   void put(char ch){deb::out(ch);}
   Msg_1();
  public: 
   static Msg_1 msg;
 };
 
 
 Msg_1 Msg_1::msg;
 
 Msg& msg=Msg_1::msg;
 
 Msg_1::Msg_1()
 :Msg((io::ascii::Output&)*this)
 {
 }
}
