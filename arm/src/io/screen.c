/*------------------------
 screen the basic output
 (c) H.Buchmann FHNW 2012
 $Id$
--------------------------*/
#include "io/screen.h"
#include "io/lcd.h"
#include <stdio.h>

/* current position */
static unsigned wi_screen;
static unsigned he_screen;
static unsigned line_step;
static unsigned yStep;
static Color    Col=0xffff;
static unsigned xP,yP;
static Pixel    row,col;

void screen_init()
{
 lcd_init();
 lcd_dimension(&wi_screen,&he_screen);
 row=lcd_pixel(0,0);
 xP=0;
 col=row;
 yP=xP;
 yStep=font_height();
 line_step=yStep*wi_screen;
}
/* TODO */
static void scroll()
{
}

static void put(char ch)
{
 Glyph g;
 font_glyph(ch,&g);
 unsigned w=g.wi_pix;
 xP+=w;
 if (xP>=wi_screen)
    {
     xP=w;
     yP+=yStep;
     row+=line_step;
     col=row;
    }
 col+=lcd_glyph(col,Col,&g);
}

static void newln()
{
 xP=0;
 yP+=yStep;
 row+=line_step;
 col=row;
}

static void tab()
{
}

Out* Screen=&(Out){put,newln,tab};

