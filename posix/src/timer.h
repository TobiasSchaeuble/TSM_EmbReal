#pragma once
//----------------------------
//timer 
//(c) H.Buchmann FHNW 2015
// see: int clock_gettime(clockid_t clk_id, struct timespec *tp);
//----------------------------
#include <time.h>
class Timer
{
 public:
   Timer(); //<----------------- start
  ~Timer(); //<----------------- stops and display elapsed time 
 private:
  timespec cpu;
  timespec tim;
  static double diff(const timespec& from,const timespec& to);
};
