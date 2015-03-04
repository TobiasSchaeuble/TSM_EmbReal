/*-----------------------
  clock.c
  (c) H.Buchmann FHNW 2013
 ------------------------*/
#include "clock.h"
#include "sys/deb.h"


/* #define CLOCK_TEST */ /* uncomment for testing */

static const unsigned SEG_LEN=90;
static const unsigned SEG_D  =10;

static unsigned wi;
static unsigned he;

                                                   /* draw horizontal segment */
/*
   /----------------------\
  /                        \
  \                        /
   \----------------------/
*/
static void hSegment(Pixel    p,  
                     Color    col)
{
 Pixel pp=p;
 for(unsigned x=0;x<SEG_LEN;++x) *pp++=col;
 Pixel up0  =p;
 Pixel down0=p;
 unsigned l=SEG_LEN;
 for(unsigned y=1;y<SEG_D;++y)
 {
  down0+=(1+wi);
  up0  +=(1-wi); 
  Pixel up  =up0;
  Pixel down=down0;
  l-=2;
  for(unsigned x=0;x<l;++x)
  {
   *up  ++=col;
   *down++=col;
  }
 }
}

                                                     /* draw vertical segment */
static void vSegment(Pixel    p,
                     Color    col)
{
 unsigned l=1;
 unsigned y=0;
 for(;y<SEG_D;++y)
 {
  Pixel pp=p;
  for(unsigned x=0;x<l;++x)
  {
   *pp++=col;
  }
  p+=(wi-1);
  l+=2;
 }
 for(;y<SEG_LEN-SEG_D;++y)
 {
  Pixel pp=p;
  for(unsigned x=0;x<l;++x)
  {
   *pp++=col;
  }
  p+=wi;
 }
 for(;y<SEG_LEN;++y)
 {
  Pixel pp=p;
  for(unsigned x=0;x<l;++x)
  {
   *pp++=col;
  }
  p+=(wi+1);
  l-=2;
 }
}		     

/*----------------------
 
  --0--
 |     |
 5     1
 |     |
  --6--
 |     |
 4     2
 |     |
  --3--  
------------------------*/
static const unsigned Num2Dig[]= /* an exercise in bits */

{
  /*  6543210 */
    0b0111111,   /* 0 */ 
    0b0000110,   /* 1 */
    0b1011011,   /* 2 */
    0b1001111,   /* 3 */
    0b1100110,   /* 4 */
    0b1101101,   /* 5 */
    0b1111101,   /* 6 */
    0b0000111,   /* 7 */
    0b1111111,   /* 8 */
    0b1101111    /* 9 */
};

typedef void (*Seg)(Pixel,Color);
/* dont works with 
static const void (*Segment[])(Pixel,Color,unsigned,unsigned)
       -----
*/
static void (*Segment[])(Pixel,Color)=
{
 hSegment,
 vSegment,
 vSegment,
 hSegment,
 vSegment,
 vSegment,
 hSegment
};


static Pixel digit_init(Pixel at,Digit* d)
{
 for(unsigned i=0;i<7;++i)d->color[i]=BLACK;
 Pixel p=at;
 unsigned h=SEG_LEN*wi;
 d->pos[0]=p;
 d->pos[5]=p;
 p+=h;
 d->pos[4]=p;
 d->pos[6]=p;
 p+=h;
 d->pos[3]=p; 
 at=at+SEG_LEN;
 p=at;
 d->pos[1]=p;
 p+=h;
 d->pos[2]=p;
 return at+5*SEG_D/2;  
}

static void digit_draw(unsigned v, /* assuming 0<=v<10 */
                       Digit* d)
{
 if (v>9) v=8;
 unsigned pattern=Num2Dig[v];
 for(unsigned i=0;i<7;++i)
 {
  Color c=(pattern&1)?WHITE:BLACK;
  if (d->color[i]!=c)
     {
      d->color[i]=c;
      Segment[i](d->pos[i],c);
     }
  pattern>>=1;   
 }
}

void clock_init()
{
 lcd_init();
 lcd_dimension(&wi,&he);
}

void clock_create(Clock*const      clock,
                  const Time*const time,
                  unsigned x,unsigned y)  /* position on screen */
{
 clock->time=*time; /* copy */
 Pixel pos=lcd_pixel(x,y);
 pos=digit_init(pos,clock->hh+0);
 pos=digit_init(pos,clock->hh+1);
 pos+=SEG_D;
 pos=digit_init(pos,clock->mm+0);
 pos=digit_init(pos,clock->mm+1);
 pos+=SEG_D;
 pos=digit_init(pos,clock->ss+0);
 pos=digit_init(pos,clock->ss+1);
}

static unsigned digits(unsigned v, /* 0<=v<60 */
                       Digit*const d) 
{
 static const unsigned Map[][2]=
 {
  {0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},{0,9},
  {1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{1,9},
  {2,0},{2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{2,7},{2,8},{2,9},
  {3,0},{3,1},{3,2},{3,3},{3,4},{3,5},{3,6},{3,7},{3,8},{3,9},
  {4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},{4,8},{4,9},
  {5,0},{5,1},{5,2},{5,3},{5,4},{5,5},{5,6},{5,7},{5,8},{5,9}
 };
 const unsigned* dd=Map[v];
 digit_draw(dd[0],d+0);
 digit_draw(dd[1],d+1);
}



void clock_display(Clock*const clock)
{
 digits(clock->time.hh,clock->hh);
 digits(clock->time.mm,clock->mm);
 digits(clock->time.ss,clock->ss);
}

void clock_tick(Clock*const clock)
{
 Time*const t=&clock->time;
 ++t->ss;
 if (t->ss<60) return;
 t->ss=0;
 ++t->mm;
 if (t->mm<60) return;
 t->mm=0;
 ++t->hh;
 if (t->hh<24) return;
 t->hh=0;
}


#ifdef CLOCK_TEST
Time t={07,56,29};
Clock clock;

int main()
{
 clock_init();
 clock_create(&clock,&t,50,50);
 clock_display(&clock);
}
#endif
