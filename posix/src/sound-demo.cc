//----------------------
//samples-demo
//(c) H.Buchmann FHNW 2015
// for play see http://sox.sourceforge.net/
//----------------------
#include "sound/alsa.h"
#include "sound/samples.h"
#include "timer.h"
#include <thread>
#include <chrono>
#include <iostream>

//retard a sample
class Wait:public sound::Player
{
 public:
  Wait(sound::Player& p,unsigned retard);
  ~Wait();
  void sample(double v);
 private:
  unsigned retard;
  Player& p; //the delegate
};

Wait::Wait(sound::Player& p,unsigned retard)
:Player(p.fs)
,retard(retard)
,p(p)
{
}

Wait::~Wait()
{
}

void Wait::sample(double v)
{
 for(unsigned i=0;i<retard;++i)
 {
  volatile unsigned c=i;
 }
 p.sample(v);
}


// ./sound-demo | play -e signed-integer -q -r 44000 -b 16 -t raw -
void noise2stdout()
{
 sound::Stream pl(44000,std::cout);
 sound::Noise(pl,1);               //for one second
}


int main(int argc,char** args)
{
 Timer t;
 sound::Alsa   pl0(44000,4*4096);
 Wait pl(pl0,0);//1<<20);
 sound::Noise(pl,2);
// noise2stdout(); 
//<--------------------------- destructor of Timer 
 return 0;
}
