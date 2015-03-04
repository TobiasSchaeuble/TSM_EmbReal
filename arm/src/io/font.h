#pragma once
/*------------------------------------
  font.h
  (c) H.Buchmann FHNW 2012
  $Id$
  generated with font/Font.java
--------------------------------------*/
typedef struct
{
 unsigned wi_pix; /* width in pixel  */
 const unsigned* pix; 
} Glyph;

extern unsigned font_height();
extern void font_init();
extern void font_glyph(char ch,Glyph* g);
