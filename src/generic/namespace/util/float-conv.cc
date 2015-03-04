//-------------------------------------
//float-conv basics 
// basics for floating point conversion
//(c) H.Buchmann FHNW 2006
//$Id: float-conv.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//__fixunsdfdi
//-------------------------------------
IMPLEMENTATION(util_float_conv,$Revision$)
#include "util/float-conv.h"
#ifndef NO_FLOATS
#include "sys/deb/deb.h"
//#include <stdio.h> // for test only 
//#include <cmath>

namespace util
{
 const double Double::POW10[2*POW_RANGE+1]=
 {
                                            1E-23,1E-22,1E-21,
  1E-20,1E-19,1E-18,1E-17,1E-16,1E-15,1E-14,1E-13,1E-12,1E-11,
  1E-10,1E-09,1E-08,1E-07,1E-06,1E-05,1E-04,1E-03,1E-02,1E-01,
  1E+0,
  1E+01,1E+02,1E+03,1E+04,1E+05,1E+06,1E+07,1E+08,1E+09,1E+10,
  1E+11,1E+12,1E+13,1E+14,1E+15,1E+16,1E+17,1E+18,1E+19,1E+20,
  1E+21,1E+22,1E+23
 };

  
 const double*const Double::POW10_0=POW10+POW_RANGE;
 
 double Double::pow10(double pwr,int p)
 {
  double r=1;
  while(p>0)
  {
   if (p&1) r*=pwr;
   pwr*=pwr;   //10^
   p>>=1;
  }
    
  return r**(POW10_0+p);
 }

 double Double::pow10(int p)
 {
  if (p<-POW_RANGE) return pow10(0.1,-p);
  if (p<=POW_RANGE) return *(POW10_0+p); //the fast path
  return pow10(10,p);
 }

 void Double::Format::convert(math::Double::Significant s)
 {
  static const char  Digits[]="0123456789";
  int dig[WIDTH]; //the digits as integer reversed order
  int r=0; 
  do
  {
   dig[r++]=s%10;    //0<=dig[]<10 
   s/=10;
  }while(s);  
  dig[r]=0;   // d0,d1,  ,d_(r-1),0 
              // r==sig   -> msd=msd0-1
	      // r==sig+1 -> msd=msd0
  if (r==sig) 
     {
      --msd; //adjust
     }
     else
     { //round
      int i=0;
      int carry=(dig[i++]>4);
      while(carry)
      {
       int d=dig[i]+1;
       carry=(d>=10);
       dig[i++]=(carry)?0:d;
      }
      if (i>r) 
         {
	  ++msd;
	  r=i;
	 }
     }
  //copy dig reversed to digs
  //reverse  
//  printf(" r=%d msd=%d\n",r,msd);  	      
  unsigned i=0;
  do
  {
   digs[i++]=Digits[dig[--r]];
  }while(r>0);
  digs[i]='\0';
 }

 void Double::Format::zero()
 {
  for(int i=0;i<sig;++i) digs[i]='0';
  digs[sig]='\0';
  msd=0;
 }

 void Double::Format::nan()
 { //sig>=3
  int i=0;
  for(;i<(sig-3)/2;++i) digs[i]=' ';
  digs[i++]='n';
  digs[i++]='a';
  digs[i++]='n';
  for(;i<sig;++i) digs[i]=' ';
  digs[i]='\0';
 }

 int Double::Format::estimateMSD()
 {
  const static double LOG2=0.301029995663981;
                         //LOG2*exp is never a natural number
  int e=exp();
  int msd=(int)(e*LOG2);  //floor
  return (e<0)?msd-1:msd;
 }

/*
 most significant digit
 msd = floor(log10(val))
 val = m*2^exp  0.5<=m < 1
 msd0= floor(log10(2)*exp) 

 msd=floor(log10(m)+log10(2)*exp)  -log10(2)<=log10(m)<0
    =floor(log10(m)+msd0+eps)       eps<=0<1
 upper limit log10(m)=0 
     msd=msd0
 lower limit log10(m)=-log10(2) eps=0
     msd=msd0-1

 msd0-1<=msd<=msd0 
 
 10 shifting 
                -->decreasing
  |    |   |   |   |   |       sig+1 
  msd0              msd0-sig
  
  shift and rounded shift=-(msd0-sig) 
  |    |   |   |   |
   sig           0
  
  case msd=msd0  
  
  | x  | x  | x  | ... | y  |  round
   sig                   0  

  case msd=msd0-1
  | 0  | x  | x  | ... | x  |  already rounded
  
*/

 Double::Format::Format(double val,unsigned sig)
 :math::Double(val)
 ,sig( (sig<3)?3
              :((sig<=SIG)?sig:SIG)
     ) //3<=sig<=SIG 3 for writing nan (not a number) 
 {
  if (isNaN()) {nan();return;}
  if (isZero()){zero();return;}
  //val!=0
  if (isNeg()) val=-val;
  msd=estimateMSD();
//  printf("val=%f isNeg=%d\nmsd0=%d\n",val,isNeg(),msd);
  int shift=sig-msd;
  Significant s=(Significant)(0.5+val*pow10(shift));
  convert(s);
//  printf("s=%llu digs=%s msd=%d exp=%d\n",s,digs,msd,exp());
 }

 void Double::Format::criticalNumbers()
 {
#if 0
  double r=0.49;
  for(int sig=0;sig<15;++sig)
  {
   double val=10*(1-pow10(-sig)*r);
//   printf("%30.20f msd0=%d\n",val,estimateMSD(val));
  }
#endif
 }

 void Double::Format::test()
 {
 }
}//namespace util
#endif //NO_FLOATS
