//--------------------------
//tc 
//(c) H.Buchmann FHNW 2014
//[1] doc/at91sam3x.pdf
//--------------------------
IMPLEMENTATION(sys_reg_tc,$Id$)
#include "sys/reg/tc.h"
#include "sys/deb/deb.h"
//#define SYS_REG_TC_TEST
namespace sys
{
 namespace reg
 {
 }
}//namespace sys

#ifdef SYS_REG_TC_TEST
#define REG(name) \
sys::deb::out(#name"\t");\
sys::deb::hex((void*)&sys::reg::TC0.name);\
sys::deb::out(" ");\
sys::deb::hex(sys::reg::TC0.name);\
sys::deb::newln()

class Tester
{
 static Tester tester;
 Tester();
};

Tester Tester::tester;

Tester::Tester()
{
 REG(channel[0].IMR);
 REG(channel[1].IMR);
 REG(channel[2].IMR);
 REG(FMR);
}
#endif
