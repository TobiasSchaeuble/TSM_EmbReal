#pragma once
/*------------------------------
  minimal stdio
  (c) H.Buchmann FHNW 2011
  demonstrates -variable parameters
  
  $Id$
  ------------------------------*/
#include <stdarg.h>
extern int printf(const char* fmt,...);
  
extern int putchar(int c);
extern int puts(const char* s);
