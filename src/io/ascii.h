#pragma once
/*-----------------------
 ascii.h output
 (c) H.Buchmann FHNW 2009
 demonstrates call back
 $Id$
------------------------*/
typedef struct /* the basic call backs */
{
 void (*put)(char ch); /* one char out */
 void (*newln)();           /* newline */
 void (*tab)();           /* tabulator */
    /* TODO more special char handling */
} Out;

void ascii_put(Out* out,char ch);
static inline void ascii_newln(Out* out){out->newln();}

void ascii_string(Out* out,const char s[]);
void ascii_unsigned_dec(Out* out,unsigned v);
void ascii_unsigned_hex(Out* out,unsigned v);
void ascii_int_dec(Out* out,int v);
/*TODO long types too */

/*TODO more type and safer */
void ascii_printf(Out* out,const char* fmt,...);

