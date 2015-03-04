/*-------------------------
 cpu-demo-ops.h 
 (c) H.Buchmann FHNW 2011
 $Id$
---------------------------*/
extern unsigned op(unsigned x,unsigned y);        /* return x op y */

                                     /* typical pointer operations */
extern void copy(unsigned* dst,unsigned* src);        /* *dst=*src */
extern void swap(unsigned* x,unsigned* y);   
