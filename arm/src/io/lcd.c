/*---------------------------
 lcd
 (c) H.Buchmann FHNW 2012
 $Id$
 see [1] literature/realview_emulation_basebord_ug.pdf
     [2] literature/pl111-Color-LCD-Controller.pdf
     and
     lcd-demo-0 
-----------------------------*/
#include "sys/sys.h"
#include "sys/def-register.h"
#include "sys/mmu.h"
#include "io/lcd.h"

extern volatile struct
{
VAR(Timing[4]   ,0x000      ,RW,0x00000000);/* Horizontal Axis Panel Control Register on page 3-5); */
VAR(UPBASE      ,0x010      ,RW,0x00000000);/* Upper and Lower Panel Frame Base Address Registers on page 3-10); */
VAR(LPBASE      ,0x014      ,RW,0x00000000);/* Upper and Lower Panel Frame Base Address Registers on page 3-10); */
VAR(Control     ,0x018      ,RW,0x0000    );/* LCD Control Register on page 3-12); */
VAR(IMSC        ,0x01C      ,RW,0x0       );/* Interrupt Mask Set/Clear Register on page 3-14); */
VAR(RIS         ,0x020      ,RO,0x0       );/* Raw Interrupt Status Register on page 3-15); */
VAR(MIS         ,0x024      ,RO,0x0       );/* Masked Interrupt Status Register on page 3-16); */
VAR(ICR         ,0x028      ,WO,0x0       );/* LCD Interrupt Clear Register on page 3-17); */
VAR(UPCURR      ,0x02C      ,RO,0x00000000);/* LCD Upper and Lower Panel Current Address Value Registers on page 3-18); */
VAR(LPCURR      ,0x030      ,RO,0x00000000);/* LCD Upper and Lower Panel Current Address Value Registers on page 3-18); */
ARR(RES1        ,0x034,0x1FC,RO,0x0       );/* Reserved); */
ARR(Palette     ,0x200,0x3FC,RW,0x00000000);/* 256x16-bit Color Palette Registers on page 3-19); */
ARR(RES2        ,0x400,0x7FC,RO,0x0       );/* Reserved); */
ARR(CursorImage ,0x800,0xBFC,RW,0x00000000);/* Cursor Image RAM Register on page 3-20); */
VAR(CrsrCtrl    ,0xC00      ,RW,0x00      );/* Cursor Control Register on page 3-20); */
VAR(CrsrConfig  ,0xC04      ,RW,0x0       );/* Cursor Configuration Register on page 3-21); */
VAR(CrsrPalette0,0xC08      ,RW,0x000000  );/* Cursor Palette Registers on page 3-22); */
VAR(CrsrPalette1,0xC0C      ,RW,0x000000  );/* Cursor Palette Registers on page 3-22); */
VAR(CrsrXY      ,0xC10      ,RW,0x00000000);/* Cursor XY Position Register on page 3-23); */
VAR(CrsrClip    ,0xC14      ,RW,0x0000    );/* Cursor Clip Position Register on page 3-24); */
ARR(RES3        ,0xC18,0xC1C,RO,- -       );/* Reserved); */
VAR(CrsrIMSC    ,0xC20      ,RW,0x0       );/* Cursor Interrupt Mask Set/Clear Register on page 3-25); */
VAR(CrsrICR     ,0xC24      ,WO,0x0       );/* Cursor Interrupt Clear Register on page 3-25); */
VAR(CrsrRIS     ,0xC28      ,RO,0x0       );/* Cursor Raw Interrupt Status Register on page 3-26); */
VAR(CrsrMIS     ,0xC2C      ,RO,0x0       );/* Cursor Masked Interrupt Status Register on page 3-26); */
ARR(RES4        ,0xC30,0xEFC,RO,0         );/* Reserved); */
ARR(RES5        ,0xF00,0xF08,RO,0         );/* Chapter 4 Programmers Model for Test); */
ARR(RES6        ,0xF0C,0xFDC,RO,0         );/* Reserved); */
VAR(PeriphID0   ,0xFE0      ,RO,0x11      );/* Peripheral Identification Register 0 on page 3-28); */
VAR(PeriphID1   ,0xFE4      ,RO,0x11      );/* Peripheral Identification Register 1 on page 3-28); */
VAR(PeriphID2   ,0xFE8      ,RO,0x-4      );/* Peripheral Identification Register 2 on page 3-29); */
VAR(PeriphID3   ,0xFEC      ,RO,0x00      );/* Peripheral Identification Register 3 on page 3-30); */
VAR(PCellID0    ,0xFF0      ,RO,0x0D      );/* PrimeCell Identification Register 0 on page 3-31); */
VAR(PCellID1    ,0xFF4      ,RO,0xF0      );/* PrimeCell Identification Register 1 on page 3-31); */
VAR(PCellID2    ,0xFF8      ,RO,0x05      );/* PrimeCell Identification Register 2 on page 3-32); */
VAR(PCellID3    ,0xFFC      ,RO,0xB1      );/* PrimeCell Identification Register 3 on page 3-32); */
} CLCDC; /* see [2] 3.2 ram.ld for location */

#define SVGA_800x600 4
#define SVGA_WIDTH (800)
#define SVGA_HEIGHT (600)

#define WI SVGA_WIDTH
#define HE SVGA_HEIGHT

const Color WHITE=0xffff;
const Color BLACK=0x0000;

static const struct 
{
 unsigned OSC4;      /* value of SYS.OSC4 */
 unsigned Timing[4]; /* values of CLCDC.Timing */
} Init[]= { /* see [1] 4.6.1 */
           {0x2c77,{0xC7A7BF38, 0x595B613F, 0x04eF1800,0}}, /* QVGA_240x320 */
           {0x2c77,{0x9F7FBF4C, 0x818360eF, 0x053F1800,0}}, /* QVGA_320x240 */
           {0x2c77,{0xe7C7BF28, 0x8B8D60DB, 0x04AF1800,0}}, /* QCIF_176x220 */
	   {0x2c77,{0x3F1F3F9C, 0x090B61DF, 0x067F1800,0}}, /* VGA_640x480  */
           {0x2cac,{0x1313A4C4, 0x0505F657, 0x071F1800,0}}  /* SVGA_800x600 */
          };

static unsigned font_he;
static unsigned short pixelV[WI*HE];               /* in the virtual memory */
static volatile unsigned short* pixel; /* in physical memory as required by
                                                             LCD controller */
void lcd_init()
{
 static unsigned initialized=0;
 if (initialized) return;
 ++initialized;
 pixel=(volatile unsigned short*)mmu_pAddr(pixelV);
 font_init();
 font_he=font_height();
 SYS.OSC[4]    =Init[SVGA_800x600].OSC4;
 for(unsigned i=0;i<4;++i)CLCDC.Timing[i]=Init[SVGA_800x600].Timing[i];
 CLCDC.UPBASE=(unsigned)pixel;
 CLCDC.LPBASE=(unsigned)pixel;
 CLCDC.Control=(1<< 0)
              |(1<<11)
	      |(1<< 5) 
	      |(6<< 1);  /* 4: 16 bpp       ok both
	                    5: 24 bpp TFT   ok both
			    6: 16 bpp 5:6:5 ok both
			    7: 12 bbp 4:4:4 ok mine qemu-devel
	                  */
 for(unsigned i=0;i<WI*HE;++i) pixel[i]=0;
}
void lcd_dimension(unsigned* wi_pix,
                   unsigned* he_pix)
{
 *wi_pix=WI;
 *he_pix=HE;
}		   

Pixel lcd_pixel(unsigned x,unsigned y)
{
 if ((x>WI)||(y>HE)) return 0;
 return pixel+y*WI+x;
}

/*
 pixel  0 1 2 3 4 5 
 bit    0 1 2 3 4 5 
*/

unsigned lcd_glyph(Pixel pix,Color c,const Glyph*const g)
{
 unsigned i=0; /* index in g->pix */
 unsigned mask=1;
 unsigned p=g->pix[i++];
 for(unsigned yy=0;yy<font_he;++yy)
 {
  volatile unsigned short* row=pix;
  for(unsigned xx=0;xx<g->wi_pix;++xx)
  {
   *row++=(p&mask)?c:0;
   mask<<=1;
   if (mask==0)
      {
       mask=1;
       p=g->pix[i++];
      }
  }
  pix+=WI;
 }
 return g->wi_pix;
}


unsigned  lcd_char(Pixel pix,Color c,char ch)
{
 Glyph g;
 font_glyph(ch,&g);
 return lcd_glyph(pix,c,&g);
}
