//--------------------------
//Double
//(c) H.Buchmann FHNW 2010
//$Id: double.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//see util::float-conv.h
//--------------------------
#pragma once
INTERFACE(math_double,$Revision$)

//TODO check #define __VFP_FP__ 1

namespace math
{
 class Double
 {
  public:
   typedef long long unsigned Bits;
   typedef long long unsigned Significant;
   static_assert(sizeof(double)<=sizeof(Double::Bits),
                "Bits too short");
   static const Bits          MSB  = (1llu<<52);
   static const Bits          Frac = MSB-1;
   static const Bits          Sign = (1llu<<63);
   static const Bits          Exp  = ((1llu<<11)-1)<<52;

   Double(double v);
   bool isZero()     const{return zero;}
   bool isNeg()	     const{return neg;}
   bool isNaN()      const{return nan;}
   bool infPos()     const{return inf&&!neg;}
   bool infNeg()     const{return inf&& neg;}
   int  exp()        const{return exp_-1022;}   // m*2^exp 0.5<=m<1 
   double mantissa() const;

  private:
   union Dbl
   {
    double v;
    Dbl(double v):v(v){}
    struct 
    {
#ifdef ARM_fpa 
     unsigned hi; //bits  0..31
     unsigned lo; //bits 32..63 
#else
     unsigned lo; //bits  0..31
     unsigned hi; //bits 32..63 
#endif      
    };

#ifdef ARM_fpa 
    Dbl(Bits bits):hi(bits>>32),lo(bits){}
#else
    Dbl(Bits bits):lo(bits),hi(bits>>32){}
#endif     
   };

   const Dbl    val;
   const int    exp_;
   const Bits   frac; 
   const bool   neg;
   const bool   zero;
   const bool   nan;
   const bool   inf;
 };
 
 inline Double::Double(double v)
 :val(v)
 ,exp_((val.hi>>20)&((1<<11)-1)) 
 ,frac((((Bits)val.hi<<32)|((Bits)val.lo))&Frac)
 ,neg((val.hi&(1<<31))!=0) //subnormal zero too
 ,zero(exp_==0)
 ,nan((exp_==0x7ff)&&(frac!=0))
 ,inf((exp_==0x7ff)&&(frac==0))
 {
#if 0 
  sys::deb::hex("lo=",val.lo);
  sys::deb::hex("hi=",val.hi);
#endif
 }

 inline double Double::mantissa() const
 {
  return Dbl((1022llu<<52)|frac).v;
 }
}//namespace math
