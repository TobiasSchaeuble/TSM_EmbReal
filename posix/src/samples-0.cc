/*---------------------
  samples.cc
  TODO reading parameter 
       sine/cos generated with cordic
       see [CORDIC]
       make appropriate error handling
       try sys/times.h
  (c) H.Buchmann FHNW 2013
  see http://www.alsa-project.org/alsa-doc/alsa-lib/examples.html
-----------------------*/
#include <cmath>
#include <iostream>
#include <alsa/asoundlib.h>
#include <time.h>

class Time 
{
 public:
  Time();
  void showDiff(const Time& to) const;
 private:
  timespec cpu;
  timespec tim;
  static double diff(const timespec& from,const timespec& to);
};

Time::Time()
{
 clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&cpu);
 clock_gettime(CLOCK_MONOTONIC,         &tim);
}

void Time::showDiff(const Time& to)const
{
 std::cerr<<"cpu="<<diff(cpu,to.cpu)<<"\n"
            "tim="<<diff(tim,to.tim)<<"\n";
}

double Time::diff(const timespec& from,const timespec& to)
{
 static const long TONANO=1000000000lu;
 
 return ((double)((to.tv_sec -from.tv_sec)*TONANO+
                 (to.tv_nsec-from.tv_nsec)))/TONANO;
}

class Player
{
 public:
  Player(unsigned fs,               //sampling frequency 
         unsigned bSize);           //buffer size
  ~Player();
  
  void sample(double v);         // -1<=v<1 
  unsigned samplingFrequency(){return fs;}
 
 private:
  snd_pcm_t* pcm;
  unsigned fs; 
  unsigned bSize;
  short int* b;                  // the buffer 
  unsigned bI;                   // index in b
  unsigned long sN;              // the number of samples
  unsigned pN;                   //the number of times play was called
  void play();                   // the buffer 
};


Player::Player(unsigned fs,unsigned bSize)
:pcm(0)
,fs(fs)
,bSize(bSize)
,b(new short int[bSize])
,bI(0)
,sN(0)
,pN(0)
{
 static const unsigned LATENCY=10;//250000;//TODO try other values 
 snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0);
 snd_pcm_set_params(pcm,
	            SND_PCM_FORMAT_S16_LE,
	            SND_PCM_ACCESS_RW_INTERLEAVED,
	            1,
	            fs,
	            0,
		    LATENCY); //latency
}

Player::~Player()
{
 play();           //the rest of the buffer 
 snd_pcm_close(pcm);
 delete [] b;
 std::cerr<<"pN="<<pN<<"\n"
          <<"sN="<<sN<<" "<<((double)sN)/fs<<" sec\n";
 
}

void Player::sample(double v)
{
 ++sN;
 b[bI++]=(short int)(0x7fff*v);
 if (bI==bSize) play();
 
}

void Player::play()
{
 snd_pcm_writei(pcm,b,bI);
 bI=0;
 ++pN;
}


class Generator //of samples
{
 public:
  Generator(Player& player,    //player outside
            double amp,        //amplitude -1<=amp<1
            double f,          //frequency Hz
	    double dur);       //duration im sec
};


Generator::Generator(Player& player,
                     double amp,double f,double dur)
{
 unsigned fs=player.samplingFrequency();
 double dt=1.0/fs; 
        //  |---------------.0 essential because fs unsigned 
 double sin_,cos_;
 sincos(2*M_PI*f/fs,&sin_,&cos_);            //calculated only once
 double x0=0.875;
 double y0=0.0;
 for(double t=0;t<=dur;t+=dt)
 {   
  player.sample(x0);
  double x1=x0*cos_ - y0*sin_;               //next sample 
  double y1=x0*sin_ + y0*cos_;
  x0=x1;
  y0=y1;
#if 0
  for(unsigned i=0;i<4000;++i)
  {
   volatile unsigned v=i;
  }
#endif
 }
}


int main(int argc,char** args)
{
 Player p(48000,1024);
 Time start;
 Generator gen(p,0.875,880,2);
// Time end;
 start.showDiff(Time());
}

