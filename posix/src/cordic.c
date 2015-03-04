/*----------------------
  cordic
  see [CORDIC]
  (c) H.Buchmann FHNW 2011
  $Id$
------------------------*/
#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>

#define BITS (8*sizeof(unsigned))
const unsigned PI =(1<<(BITS-1)); /* (2^BITS)/2 */
const unsigned PI2=(1<<(BITS-2));
const unsigned PI4=(1<<(BITS-3)); 
const int ONE=__INT_MAX__;
#define SIZE (11)
                                  /* tan(Alfa)=2^-i */
const int Alfa[SIZE]={536870912,  
		      316933406,
		      167458907,
		       85004756,
		       42667331,
		       21354465,
		       10679838,
			5340245,
			2670163,
			1335087,
			 667544};

const int COS=1844227466; /* prod(cos(alfa[i]) 0<i<SIZE */

void cordic(int alfa, /* [0,PI4 ) */
            int* cos, /* [-ONE,ONE] */
	    int* sin) /* [-ONE,ONE] */
{
 int x=COS;
 int y=0;
 for(unsigned i=1;i<SIZE;++i)
 {
  if (alfa>0)
     {
      alfa-=Alfa[i];
      int x1=    x - (y>>i);
          y =(x>>i)+  y;
      x=x1;	  
     } 
     else
     {
      alfa+=Alfa[i];
      int x1=     x + (y>>i);
          y =-(x>>i)+  y;
      x=x1;	  
     }
 }
 *cos=x;
 *sin=y;
}

void cossin(unsigned alfa, /* [0,2Pi) ->[0,2*PI) size typ. 32 */
            int* cos,      /* -1: -max 1:max */
	    int* sin)
{
 if (alfa<=PI4) 
    {
     cordic(alfa,cos,sin);
     return;
    }
 /* PI4<alfa  */
 if (alfa<=PI2)
    {
     cordic(PI2-alfa,sin,cos);
     return;
    }
 /* PI2<alfa  */
 if (alfa<=PI) 
    {
     cossin(PI-alfa,cos,sin);
     *cos=-*cos;
     return;
    }
 /* PI<alfa<2*PI */
 cossin(alfa-PI,cos,sin);
 *cos=-*cos;
 *sin=-*sin;
}

int main(int argc,char** args)
{
 unsigned alfa=0;
 unsigned dAlfa=PI/32;
 for(unsigned i=0;i<64;++i)
 {
  int cos_=0;
  int sin_=0;
  cossin(alfa,&cos_,&sin_);
  printf("%f\t%f\t%f\n",alfa*M_PI/PI,(double)cos_/ONE,(double)sin_/ONE);
  alfa+=dAlfa;
 }
}

