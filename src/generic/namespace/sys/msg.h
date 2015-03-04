#pragma once
INTERFACE(sys_msg,$Revision: 160 $)
//-----------------------
//system wide messages (cerr)
//(c) H.Buchmann FHSO 2003
//$Id: msg.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//-----------------------
#include "io/ascii/out.h"
#include "io/ascii/write.h"
namespace sys
{
 class Msg:public io::ascii::Writer,
	   private io::ascii::Writer::EoLListener
 {
  private:
   Msg(const Msg&);
   Msg& operator=(const Msg&);
   void onEoL(io::ascii::Output&);
   void halt();    //display halt and halts

  protected:
   Msg(io::ascii::Output& out);
  
  public:
   Msg& error();   //display error prefix   **** error: and halts after eol 
   Msg& warning(); //display warning prefix **** warning:
   Msg& debug();   //enter debug call of sys::deb::enter
 };
 
 extern Msg& msg;
}
