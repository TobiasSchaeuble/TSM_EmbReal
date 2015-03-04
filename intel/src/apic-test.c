/*-------------------
 apic-test
 (c) H.Buchmann FHNW 2009
 $Id$
---------------------*/
#include "sys/apic.h"
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/sys.h"

static unsigned hh =0; /* 0<=hh<24  */
static unsigned min=0; /* 0<=min<60 */
static unsigned sec=0; /* 0<=sec<60 */

static char* Digits[]=
{
 "00","01","02","03","04","05","06","07","08","09",
 "10","11","12","13","14","15","16","17","18","19",
 "20","21","22","23","24","25","26","27","28","29",
 "30","31","32","33","34","35","36","37","38","39",
 "40","41","42","43","44","45","46","47","48","49",
 "50","51","52","53","54","55","56","57","58","59"
};

static void inc()
{
 ++sec;
 if (sec<60) return;
 sec=0;
 ++min;
 if (min<60) return;
 min=0;
 ++hh;
 if (hh<24) return;
 hh=0;
}

static void tick(unsigned id)
{
 inc();
 ascii_printf(Screen,"%s:%s:%s\n",Digits[hh],Digits[min],Digits[sec]);
}

static void init()
{
 apic_init();
 apic_timer(0x10000000/16,tick); /* runs faster than one sec */
 apic_timer_enable();
 sys_sti();
}

int main()
{
 init();
 while(1)
 {
 }
 return 0;
} 
