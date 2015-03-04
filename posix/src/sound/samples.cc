//---------------------
// samples.cc
// (c) H.Buchmann FHNW 2015
//--------------------- 
#include "samples.h"
#include <random>
namespace sound
{
 Player::Player(unsigned  fs)
 :fs(fs) //init list
 {
 }

 Generator::Generator(Player& p)
 :p(p)
 ,dt(1.0/p.fs)
 //  |---------------.0 essential because fs unsigned 
 {
 }


 Stream::Stream(unsigned fs,std::ostream& out)
 :Player(fs)
 ,out(out)
 {
 }

 void Stream::sample(double v)
 {
  union
  {
   Sample out;
   char   bytes[0];
  } s;

  s.out=0x7fff*v;
  out.write(s.bytes,sizeof(s));
 }

 Sine::Sine(Player& p,double f_Hz,double dur_Sec)
 :Generator(p)
 {
  double sin_,cos_;
  sincos(2*PI*f_Hz/p.fs,&sin_,&cos_);            //calculated only once
  double x0=0.875;
  double y0=0.0;
  for(double t=0;t<=dur_Sec;t+=dt)
  {   
   p.sample(x0);
   double x1=x0*cos_ - y0*sin_;               //next sample 
   double y1=x0*sin_ + y0*cos_;
   x0=x1;
   y0=y1;
  }
 }

 Noise::Noise(Player& p,double dur_Sec)
 :Generator(p)
 {
  std::random_device dev;  //too slow
//  std::default_random_engine dev;
  std::uniform_real_distribution<double> random(-0.5,0.5);
  for(double t=0;t<dur_Sec;t+=dt)
  {
   p.sample(random(dev));
  }
 }
}//namespace sound
