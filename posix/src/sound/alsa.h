#pragma once
//-----------------------
//alsa
//(c) H.Buchmann FHNW 2015
// see http://www.alsa-project.org/alsa-doc/alsa-lib/examples.html
//     http://www.alsa-project.org/main/index.php/Main_Page
//-----------------------
#include "samples.h"
#include <alsa/asoundlib.h>
namespace sound
{
//a Player for the soundcard
 class Alsa:public Player
 {
  public:
   Alsa(unsigned fs,unsigned bufferSize);
   ~Alsa();
   void sample(double v);

  private:
   snd_pcm_t*      pcm=0;
   typedef short int Sample;
   const unsigned  bS;         //bufferSize
   Sample*         buffer;     //TODO sample type as template
   unsigned        sI=0;       //the current sample
   void play();                //the buffer
   snd_async_handler_t* handler;
   static void listener(snd_async_handler_t*);
 };
}
