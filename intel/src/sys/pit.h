#ifndef SYS_PIT_H
#define SYS_PIT_H
/*--------------------
 pit.h programmage interval timer 
 (c) H.Buchmann FHNW 2009
 $Id$
 see: 82C54 CHMOS PROGRAMMABLE INTERVAL TIMER
 see pit-demo.c Version 36
----------------------*/
        	   /* not very robust parameter checks */
	                               /* TODO make it */
extern void pit_configure(unsigned counter,          /* 0,1,2 */
        		  unsigned short cnt,
			  unsigned mode);      /* 0,1,2,3,4,5 */

extern unsigned pit_getCount(unsigned counter);
extern unsigned pit_getStatus(unsigned counter);

static inline unsigned pit_eoc(unsigned counter)
       {return (pit_getStatus(counter)&0x80)!=0;}
#endif
