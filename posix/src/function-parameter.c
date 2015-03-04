/*---------------------
 function-parameter
 (c) H.Buchmann FHNW 2011
 $Id$
-----------------------*/
#include <stdio.h>

/* two callees
  different names
  *but*
   - the same *signature* e.g.
    same return type
    same parameters
*/
int calleeA(int arg)  
{
 return arg+2; 
}
 
int calleeB(int arg)  
{
 return arg+4; 
}

/* the quite cryptic: 

  int (*func)(int) 
  
  means:
  the parameter func is a function with the signature
  int aName(int)
*/
 
void theCallerA(int (*func)(int))
{
 int value=8;
 /* call it */
 printf("func(%d)=%d\n",value,func(value));
}

/* another possibilty for declaring function parameters */
typedef int (*Func)(int);               /* the type Func */

void theCallerB(Func f)
{
 int value=9;
 /* call it */
 printf("f(%d)=%d\n",value,f(value));
}

int main(int argc,char** args)
{
 theCallerA(calleeA); /* calleeA as parameter */
 theCallerB(calleeB); /* calleeB as parameter */
 return 0;
}
 
 
