#pragma once
/*----------------------------
 out a simple demo module 
  writing to the screen
 the public part
 (c) H.Buchmann FHNW 2010
 $Id$
 -----------------------------*/
extern void out_init(); 
                   /* *must* be called prior to all other out calls */

extern void out_char(char ch); 
                      /* prints a character on the current position */

extern void out_string(const char* s);
                         /* prints a string on the current position */
