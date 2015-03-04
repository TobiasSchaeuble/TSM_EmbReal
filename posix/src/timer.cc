//----------------------------
//time
//(c) H.Buchmann FHNW 2015
//----------------------------
#include "timer.h"
#include <iostream>

//uncomment for test
//#define TIM_TEST

Timer::Timer()
{
 clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&cpu);
 clock_gettime(CLOCK_MONOTONIC,         &tim);
}

Timer::~Timer()
{
 timespec cpu1;
 timespec tim1;
 clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&cpu1);
 clock_gettime(CLOCK_MONOTONIC,         &tim1);
 std::cerr<<"cpu="<<diff(cpu,cpu1)<<"\n"
            "tim="<<diff(tim,tim1)<<"\n";
}


double Timer::diff(const timespec& from,const timespec& to)
{
 static const long TONANO=1000000000lu;
 
 return ((double)((to.tv_sec -from.tv_sec)*TONANO+
                  (to.tv_nsec-from.tv_nsec)))/TONANO;
}

#ifdef TIM_TEST
int main(int argc,char** args)
{
 Timer t0;
 char ch;
 std::cin>>ch;
 return 0;
}
#endif
