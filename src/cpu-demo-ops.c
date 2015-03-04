/*-------------------------
 cpu-demo-ops.c 
 (c) H.Buchmann FHNW 2011
 $Id$
 the c language implementation 
---------------------------*/
#include "cpu-demo-ops.h" /* how the functions look like */

/* the c language works for every architecture
   therefore this file is located in this src
   for disassembly use
   objdump -d cpu-demo-ops.o
*/
/* the implememtation */
unsigned op(unsigned x,unsigned y)
{
 return x+y;
}

void copy(unsigned* dst,unsigned* src)
{
 *dst=*src;
}

void swap(unsigned* x,unsigned* y)
{
 unsigned v=*x;
 *x=*y;
 *y=v;
}
