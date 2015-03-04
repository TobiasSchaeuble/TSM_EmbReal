#pragma once
/*---------------------------
 lcd fast access
 (c) H.Buchmann FHNW 2012
 $Id$
-----------------------------*/
#include "io/font.h"

typedef unsigned short Color;
/* color scheme 5 6 5
bit  0.. 4 RED
bit  5..10 GREEN
bit 11..15 BLUE
*/
extern const Color WHITE;
extern const Color BLACK;

typedef volatile Color* Pixel;

extern void lcd_init();
extern void lcd_dimension(unsigned* wi_pix,
                          unsigned* he_pix);

extern Pixel lcd_pixel(unsigned x,unsigned y);

/* TODO more graphic primitives */
/* pix upper left corner */
extern unsigned lcd_glyph(Pixel pix,
                          Color c,
			  const Glyph*const g); 
 
extern unsigned lcd_char(Pixel pix,Color c,char ch);
/* returns witdh of character in pixel */
