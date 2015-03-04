//--------------------------
//startup-1
//(c) H.Buchmann FHSO 2003
//$Id: startup-1.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//--------------------------
IMPLEMENTATION(test_startup_1,$Revision: 1.4 $)
#include "sys/msg.h"
#include "sys/deb/deb.h"
//#include "test/module.h"
//#include "sys/host.h"
namespace test
{
 class Startup
 {
  private:
   static Startup startup;
   Startup();
   ~Startup();
 };
 
 
 Startup Startup::startup;
 
 
 Startup::Startup()
 {
  sys::msg<<"\n"<<__PRETTY_FUNCTION__<<"\n";
  const  sys::BuildID& id=sys::buildId();
  sys::deb::out(id.name);
  sys::deb::out(':');
  for(unsigned i=0;i<id.descN;++i) sys::msg.hex(id.desc[i]);
  sys::deb::newln();
  sys::deb::waitForKey('s');
  sys::msg<<"good bye\n";
//  sys::exit(1);
 }

 Startup::~Startup()
 {
  sys::msg<<__PRETTY_FUNCTION__<<"\n";
 }

}
