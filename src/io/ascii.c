/*-----------------------
 ascii.h output
 (c) H.Buchmann FHNW 2009
 $Id$
------------------------*/
#include "io/ascii.h"
#include <stdarg.h>    /* from compiler include *not* posix */

void ascii_put(Out* out,char ch)
{
 switch(ch)
 {
  case '\0':return;
  case '\n':out->newln();return;
  case '\t':out->tab();return;
 }
 out->put(ch);
}

void ascii_string(Out* out,const char s[])
{
 for(unsigned i=0;s[i];++i) ascii_put(out,s[i]);
}

void ascii_unsigned_dec(Out* out,unsigned v)
{
 static const char Digits[]="0123456789";
 char rev[3*8*sizeof(unsigned)/10+2];
                   /* 0.3*bits number of decimal digits */
 unsigned i=0;     /* index in rev */
 do
 {
  rev[i++]=Digits[v%10];
  v/=10;
 }while(v!=0);
 while(i>0) out->put(rev[--i]);
}

void ascii_int_dec(Out* out,int v)
{
 if (v<0) 
    {
     out->put('-');
     v=-v;
    }
 ascii_unsigned_dec(out,v);
}

void ascii_unsigned_hex(Out* out,unsigned v)
{
 static const char Digits[]="0123456789abcdef";
 unsigned bits=8*sizeof(unsigned);
 while(bits>0)
 {
  bits-=4;
  out->put(Digits[0xf&(v>>bits)]);
 }
}

/*TODO more elaborate printf */
void ascii_printf(Out* out,const char* fmt,...)
{
 va_list lst; 
 va_start(lst,fmt);                  /* see man va_start */
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
    ascii_put(out,ch);
   break; 
   
   case 1:
    switch(ch)
    {
     case 's':
      ascii_string(out,va_arg(lst,char*));
     break;
     case 'd':
      ascii_int_dec(out,va_arg(lst,int));
     break;
     case 'x':
      ascii_put(out,'0');ascii_put(out,'x');
      ascii_unsigned_hex(out,va_arg(lst,unsigned));
     break;
     case 'c':/* character */
      ascii_put(out,va_arg(lst,unsigned));
     break;
     
     case 'p':/* pointer */
      ascii_put(out,'0');ascii_put(out,'x');
      ascii_unsigned_hex(out,va_arg(lst,unsigned));
     break;
     
     case '%':out->put('%');break;
    }
    status=0; 
   break;
  }
 }
 va_end(lst);
}

