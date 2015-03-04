/*-------------------------
  mouse-demo
  (c) H.Buchmann FHNW 2012
  $Id$
 --------------------------*/
#include "stdio.h"
#include "io/mouse.h"

void onMouse(int x,int y,unsigned button)
{
 static const char* Buttons[]={ /* LMR       mrl */ 
                             "---",  /* 000 */
			     "L--",  /* 001 */
			     "--R",  /* 010 */
			     "L-R",  /* 011 */
			     "-M-",  /* 100 */
			     "LM-",  /* 101 */
			     "-MR",  /* 110 */
			     "LMR"   /* 111 */
                         };
 printf("%s\t%d\t%d\n",Buttons[button],x,y);
}

int main()
{
 mouse_register(onMouse);
 mouse_enable(); 
}  
