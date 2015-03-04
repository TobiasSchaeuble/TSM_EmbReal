//-----------------------------
//scs system control space
//(c) H.Buchmann FHNW 2013
//[1] superfluous/eo3s/arm/doc/DDI0403D_arm_architecture_v7m_reference_manual_errata_markup_1_0.pdf
//-----------------------------
IMPLEMENTATION(sys_reg_scs,$Id$)
#include "sys/reg/scs.h"
//#define SYS_REG_SCS_TEST
//#include "sys/deb/deb.h"
namespace sys
{
 namespace reg
 {
 }//namespace reg
}//namespace sys

#ifdef SYS_REG_SCS_TEST
class Tester
{
 static Tester tester;
 Tester();
};
Tester Tester::tester;

#define REG(name) \
sys::deb::hex(#name"\t",(void*)&sys::reg::SCS.name)

Tester::Tester()
{
 REG(MCR);
 REG(TICK);
 REG(NVIC);
 REG(SCB.CPUID);
 REG(SCB.ICSR);
 REG(SCB.CPACR);
 REG(MPU);
 REG(STIR);
 REG(CID[0]);
}
#endif
