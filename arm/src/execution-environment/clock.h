#pragma once
/*-----------------------
  clock.h
  (c) H.Buchmann FHNW 2013
 ------------------------*/
#include "io/lcd.h"

typedef struct
{
 unsigned hh,mm,ss;
} Time;

typedef struct
{
 Color color[7];
 Pixel pos[7];
} Digit;


typedef struct
{
 Time   time;
 Digit  hh[2];
 Digit  mm[2];
 Digit  ss[2];
} Clock;

extern void clock_init();

extern void clock_create(Clock*const       clock,
                         const Time*const  time,
                         unsigned x,unsigned y);  /* position on screen */

extern void clock_display(Clock*const clock);
extern void clock_tick(Clock*const clock);
