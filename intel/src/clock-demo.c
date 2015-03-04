/*------------------
  clock-demo 
  demonstrates 
   pit: programmable interval timer
   pic: programmable interrupt controller 
  (c) H.Buchmann FHNW 2009
--------------------*/
#include "io/screen.h"                       /* for output on screen */  
#include "io/ascii.h"                             /* for ascii output */
#include "sys/pit.h"               /* the programmable interval timer */
#include "sys/pic.h"     /* for the programmable interrupt controller */
#include "sys/sys.h"                                       /* for sti */
#include "io/kbd.h"                                   /* the keyboard */
#include "sys/deb.h"

#include "stdio.h"

#define FREQ_HZ (1193180)                                /* per count */
#define CNT (20)                                      /* for a second */

static unsigned cnt=0;
static unsigned sec=0;
static unsigned min=0;
static unsigned hh =0;

static const char* Numbers[]=
{
"00","01","02","03","04","05","06","07","08","09",
"10","11","12","13","14","15","16","17","18","19",
"20","21","22","23","24","25","26","27","28","29",
"30","31","32","33","34","35","36","37","38","39",
"40","41","42","43","44","45","46","47","48","49",
"50","51","52","53","54","55","56","57","58","59"
};

static void tick(unsigned id)
{
 ++cnt;
 if (cnt==CNT)
    {
     ascii_printf(Screen,
                 "%s:%s:%s\n",
		 Numbers[hh],Numbers[min],Numbers[sec]
                        );
     cnt=0;
     ++sec;
     if (sec==60)
        {
	 sec=0;
	 ++min;
	 if (min==60)
	   {
	    min=0;
	    ++hh;
	    if (hh==24)
	      {
	       hh=0;
	      }
	   }
	}
    }
}
 
int main()
{
 pic_init();
 pic_install(0,tick);
 pic_enable(0);
 pit_configure(0,                   /* the counter */
               FREQ_HZ/20,    /* smaller than 2^16 */
	       2);                /* mode 2 reload */
 sys_sti();
 while(1)
 {
  kbd_get();
 }
 return 0;
}
