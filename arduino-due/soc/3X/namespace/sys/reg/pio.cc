//---------------------------
//pio
//(c) H.Buchmann FHNW 2014
//see doc/at91sam3x.pdf 32.7
//---------------------------
IMPLEMENTATION(sys_reg_pio,$Id$)
#include "sys/reg/pio.h"

namespace sys
{
 namespace reg
 {
  void PIO::set(Function f,unsigned pins) volatile
  {
   switch(f)
   {
    case IN:
     ODR=pins;
     PER=pins;
    break;

    case OUT:
     OER=pins;
     PER=pins;
    break;

    case PERIPH_A:
     ABSR&=~pins;
     PDR=pins;
    break;

    case PERIPH_B:
     ABSR|=pins;
     PDR=pins;
    break;
   }
  }
 }//namespace reg
}//namespace sys

