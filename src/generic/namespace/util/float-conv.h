#pragma once
//-------------------------------------
//float-conv basics 
// basics for floating point conversion
//(c) H.Buchmann FHNW 2006
//$Id: float-conv.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//-------------------------------------
INTERFACE(util_float_conv,$Revision$)
#ifndef NO_FLOATS
#include "math/double.h"
namespace util
{
 class Double
 {
  public:
   class Format;
   static double pow10(int p); //convenience method

  private:
   static const int    POW_RANGE =23; //+/- 10^23 Avogadro number
                                      //for a reasonable range  
   static const double POW10[2*POW_RANGE+1];
   static const double*const POW10_0;
   static double pow10(double pwr0,int p);
                              //p>0  
 };  

 class Double::Format:public math::Double
 {
  public:
   Format(double val,unsigned sig);
   int    getMSD()const{return msd;}
   int    getSig()const{return sig;}
   const char*const getDig() const {return digs;}
            //0<i<getSig() valid digits
   static void criticalNumbers();
   static void test();
   
  private:
   static const unsigned WIDTH=3+(301*8*sizeof(Significant))/1000;
   static const unsigned SIG=18;
   const int  sig;              //the number of significant decimal digits
   char       digs[WIDTH];      //digits
   int        msd;              //most significant digit
   int  estimateMSD();
   void convert(Significant s); 
   void zero();
   void nan(); //not a number
 };
}//namespace util
#endif //NO_FLOATS
