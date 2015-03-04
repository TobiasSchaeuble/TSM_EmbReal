/*-----------------------
 pit-demo pit programmable interval timer
 (c) H.Buchmann FHNW 2009
 $Id$
 see: 82C54 CHMOS PROGRAMMABLE INTERVAL TIMER
-------------------------*/
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/sys.h"
#include "io/kbd.h"
/* port 0x40-0x43 timer0
   port 0x50-0x53 timer1
*/

#define TIMER0 0x40

static void configure(unsigned counter,         /* 0,1,2 */
                      unsigned short cnt,
		      unsigned mode)      /* 0 1 2 3 4 5 */
{
 /* no BCD */
 sys_outb( ((0x7&mode)   <<1)|
           ( 0x3         <<4)| /* LSB MSB */
	   ((0x3&counter)<<6), 
	  TIMER0+3);
 sys_outb((unsigned char)(cnt>>0),TIMER0+counter); /* LSB */
 sys_outb((unsigned char)(cnt>>8),TIMER0+counter); /* MSB */	  
}

static unsigned getCount(unsigned counter) /* 0,1,2 */
{
 sys_outb(((0x3&counter)<<6), /* latch */
          TIMER0+3);
/* make it in two statements because of proper ordering */
/* dont works with -O3 */
/* but with -O0 */
 unsigned v=sys_inb(TIMER0+counter);
 return v|(((unsigned)sys_inb(TIMER0+counter))<<8);
}

static unsigned getStatus(unsigned counter)  /* 0,1,2 */
{
 sys_outb( ((1<<counter)<<1)| /* select counter */
                      (1<<5)|        /* COUNT=0 */
		    (0x3<<6)|
		          0,
            TIMER0+3);
 return sys_inb(TIMER0+counter);
}

int main()
{
 configure(0,0x0ffff,2); //mode 2
 while(1)
 {
  if (getStatus(0)&0x80)
     {
      ascii_string(Screen,"t");      
     }
 }
 return 0;
}
