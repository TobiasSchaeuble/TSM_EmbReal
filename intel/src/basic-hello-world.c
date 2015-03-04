/*---------------------
 hello-world
 (c) H.Buchmann FHNW 2009
 $Id$
-----------------------*/
/* the video ram */
volatile unsigned short* video=(volatile unsigned short*)0xb8000;
#define WIDTH 80    /* of screen */  
#define HEIGHT 25   /* of screen */

int start()                    /* will be called from big-bang */
{
 unsigned char ch='A';
 while(1)
 { 
  unsigned short attr=0;
  volatile unsigned short* v=video;
  for(unsigned r=0;r<HEIGHT;r++)
  {
   for(unsigned c=0;c<WIDTH;c++)
   {
    *v++=attr|ch;  
    if (ch=='Z') ch='A';
       else      ++ch;
    attr+=0x100;   
   }         /* for c<WIDTH */
  }          /* for r<HEIGHT */
 }/* while */
}

