//-----------------------
//alsa
//(c) H.Buchmann FHNW 2015
//-----------------------
/* 
 
*/
#include "alsa.h"
#include <iostream>
namespace sound
{

#define SND(call) \
{unsigned res=snd_##call; \
 if (res<0)\
    {std::cerr<<snd_strerror(res)<<" "<<__LINE__<<"\n";\
    }\
}

 Alsa::Alsa(unsigned fs,unsigned bufferSize)
 :Player(fs)
 ,bS(bufferSize)
 ,buffer(new Sample[bS])
 {
  static const unsigned LATENCY=10;//250000;//TODO try other values 
  SND(pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, SND_PCM_ASYNC));
  SND(pcm_set_params(pcm,
	             SND_PCM_FORMAT_S16_LE,
		     SND_PCM_ACCESS_RW_INTERLEAVED,
	             1,
	             fs,
	             0,
		     LATENCY)); //latency
  SND(async_add_pcm_handler(&handler,pcm,&Alsa::listener,0));
 }

 Alsa::~Alsa()
 {
  std::cerr<<"~Alsa\n";
  play(); //the rest of the buffer
  snd_pcm_close(pcm);
  delete [] buffer;
 }

 void Alsa::listener(snd_async_handler_t*)
 {
  std::cerr<<"listener\n";
 }
 
 void Alsa::sample(double v)
 {
  buffer[sI++]=(Sample)(0x7fff*v); //scale
  if (sI==bS) play();
 }

 void Alsa::play()
 {
//  snd_pcm_state_t state=snd_pcm_state(pcm);
//  std::cerr<<state<<"\n";
  snd_pcm_sframes_t f=snd_pcm_writei(pcm,buffer,sI);
  while(f<0)
  {
   f=snd_pcm_recover(pcm,f,1);
  }
#if 0
  if (f<0)
     {
      std::cerr<<"err="<<snd_strerror(f)<<"\n";
     }
     else
     {
      std::cerr<<"f="<<f<<"\n";
     }
#endif
  sI=0;
 }
}
