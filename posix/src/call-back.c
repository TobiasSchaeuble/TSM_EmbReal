/*--------------------
  call-back.c
  (c) H.Buchmann FHNW 2009
  $Id$
----------------------*/
#include <stdio.h>
#include <ctype.h>
typedef unsigned (*CallBack)(char);         /* the declaration */  

typedef int (*Conversion)(int);                /* another type */
                                  /* describes toupper tolower */
unsigned myCall1(char ch)               /* is of type CallBack */
{
 printf("myCall1 ch=%c\n",ch);
 return toupper(ch);
}

unsigned myCall2(char ch)            /* is of type CallBack too*/
{
 printf("myCall2 ch=%d\n",ch);
 return tolower(ch);
}

static CallBack   callBack[]={myCall1,myCall2};
static Conversion conv[]={toupper,tolower};    /* from ctype */

char callIt(unsigned idx,char parameter)
{
 /* indirect call */
 return callBack[idx](parameter);
}

int main(int argc,char** args)
{
 /* direct call */
 myCall1('a');
 myCall2('A');
 {/* nested block */
  char ch0=callIt(0,'b');
  char ch1=callIt(0,'B');
  printf("callIt: ch0='%c' ch1='%c'\n",
         ch0,ch1);
 }

 {/* nested block */
  char ch0='c';
  char ch1='C';
  printf("conv[0](%c)=%c\n"
         "conv[1](%c)=%c\n",
         ch0,conv[0](ch0),
	 ch1,conv[1](ch1));
 }
 return 0;
}

