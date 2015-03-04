/*--------------------
 pit.h programmage interval timer 
 (c) H.Buchmann FHNW 2009
 $Id$
 see: 82C54 CHMOS PROGRAMMABLE INTERVAL TIMER
 see pit-demo.c Version 36
----------------------*/
#include "sys/pit.h"
#include "sys/sys.h"

/* port 0x40-0x43 timer0
   port 0x50-0x53 timer1
*/

#define TIMER0 0x40 /* our timer */

void pit_configure(unsigned counter,
        	   unsigned short cnt,
		   unsigned mode)
{
 sys_outb( ((0x7&mode)   <<1)|
           ( 0x3         <<4)| /* LSB MSB */
	   ((0x3&counter)<<6), 
	  TIMER0+3);
 sys_outb((unsigned char)(cnt>>0),TIMER0+counter); /* LSB */
 sys_outb((unsigned char)(cnt>>8),TIMER0+counter); /* MSB */	  
}
		   
unsigned pit_getCount(unsigned counter)
{
 sys_outb(((0x3&counter)<<6), /* latch */
          TIMER0+3);
/* make it in two statements because of proper ordering */
 unsigned v=sys_inb(TIMER0+counter);
 return v|(((unsigned)sys_inb(TIMER0+counter))<<8);
}

unsigned pit_getStatus(unsigned counter)
{
 sys_outb( ((1<<counter)<<1)| /* select counter */
                      (1<<5)|        /* COUNT=0 */
		    (0x3<<6)|
		          0,
            TIMER0+3);
 return sys_inb(TIMER0+counter);
}

