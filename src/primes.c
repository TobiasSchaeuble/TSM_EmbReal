/*---------------------------
 primes calculates the 
 first N  prime numbers
 (c) H.Buchmann FHNW 2012
 $Id$
 TODO 
   proof that this algorithm *really* calculates
   *all* first N primes 
 ----------------------------*/
#include <stdio.h>
#define N 10
#define bool unsigned

static unsigned thePrimes[N];   /* space for  the first N prime numbers */
static unsigned pN=0;                    /* the number of primes so far */
                                                               /* pN<=N */
static bool isPrime(unsigned v)        /* returns true iff v is a prime */
{
 unsigned pi=0;                                   /* index in thePrimes */
 while(1)
 {
  unsigned p=thePrimes[pi++]; /* the current prime p<v */
  /* v=n*p+r */
  unsigned n=v/p;
  unsigned r=v%p;
  if (r==0) return 0;
  if (n<p) return 1;     /* why */
 }
}

static void primes() 
{
 thePrimes[pN++]=2;                                  /* the first prime */
 unsigned   v=3;                             /* the number to be tested */
 while(pN<N)
 {
  if (isPrime(v))
     {
      thePrimes[pN++]=v;
     }
  ++v;                                         /* v+=2 works too why */
 }
}

static void show() /* TODO make a better show */
{
 for(unsigned i=0;i<pN;++i)
 {
  printf("%d\n",thePrimes[i]);
 } 
}

int main(int argc,char** args)
{
 primes();
 show();
}
 
