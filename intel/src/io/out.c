/*----------------------------
 out a simple demo module 
  writing to the screen
 the public part
 (c) H.Buchmann FHNW 2010
 $Id$
 -----------------------------*/
#include "io/out.h"       /* the public part */
typedef struct
{
 char ch;        /* the char */
 char attr; /* the attribute */
} __attribute__((packed)) Char;

#define COLS 80
#define ROWS 25

static volatile Char* video=    /* the video ram */
     (volatile Char*)0xb8000;

/* status */
static unsigned pos; /* the current pos */

void out_init()
{
 pos=0;
 /* TODO the rest */
}

void out_char(char ch)
{
 video[pos++].ch=ch;
}

void out_string(const char* s)
{
 for(unsigned i=0;s[i];++i) out_char(s[i]);
}

