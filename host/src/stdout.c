/*-------------------------
 stdout
 (c) H.Buchmann FHNW 2011
 $Id$
 --------------------------*/
#include "stdout.h"
extern int putchar(int c); /* we dont want to include stdio */
extern int puts(const char *s);
static void put(char ch)
{
 putchar(ch);
}

static void newln()
{
 putchar('\n');
}

static void tab()
{
  putchar('\t');
}

void stdout_init()
{
}

static Out stdout_={put,newln,tab};
Out* stdout=&stdout_;
