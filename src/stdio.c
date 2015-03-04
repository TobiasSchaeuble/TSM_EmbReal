/*------------------------------
  minimal stdio
  (c) H.Buchmann FHNW 2011
  demonstrates -variable parameters
  TODO more specifiers 
  see manual page va_list 
  $Id$
  ------------------------------*/
#include <stdarg.h>    /* from compiler include *not* posix */
#include "stdio.h" 
#include "io/ascii.h"
#include "stdout.h"

/* TODO why the DONT_WORK section dont work */ 

/* #define DONT_WORK */

int printf(const char* fmt,...)  
{
#ifdef DONT_WORK
 va_list lst; 
 va_start(lst,fmt); 
 ascii_printf(stdout,fmt,lst); /* delegates to ascii_printf */
 va_end(lst); 
#else
 va_list lst;
 va_start(lst,fmt);                     /* see man va_start */
 unsigned i=0;
 unsigned status=0; 
 while(1)
 {
  char ch=fmt[i++];
  if (ch=='\0') break;
  switch(status)
  {
   case 0:
    if (ch=='%'){status=1;break;}
    ascii_put(stdout,ch);
   break; 
   
   case 1:
    switch(ch)
    {
     case 's':
      ascii_string(stdout,va_arg(lst,char*));
     break;
     case 'd':
      ascii_int_dec(stdout,va_arg(lst,int));
     break;
     case 'x':
      ascii_put(stdout,'0');ascii_put(stdout,'x');
      ascii_unsigned_hex(stdout,va_arg(lst,unsigned));
     break;
     case 'c':/* character */
      ascii_put(stdout,va_arg(lst,unsigned));
     break;
     
     case 'p':/* pointer */
      ascii_put(stdout,'0');ascii_put(stdout,'x');
      ascii_unsigned_hex(stdout,va_arg(lst,unsigned));
     break;
     
     case '%':stdout->put('%');break;
    }
    status=0; 
   break;
  }
 }
 va_end(lst);
#endif
 return 0;
}

int putchar(int c)
{
 ascii_put(stdout,(char)c);
 return 0;
}

int puts(const char* s)
{
 ascii_string(stdout,s);
 stdout->newln();
 return 0;
}
