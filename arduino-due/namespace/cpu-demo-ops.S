/*---------------------------
 cpu-demo-ops
 (c) H.Buchmann FHNW 2015
 ----------------------------*/
.text

/* TODO: look for the TODO's in the other cpu-demo-ops.S files */
/* unsigned Demo::op(unsigned int, unsigned int)
   r0                r0            r1

use:
   ../tc/bin/arm-none-linux-gnueabi-nm cpu-demo.o
to figure out the real name   
*/
.global _ZN4Demo2opEjj
_ZN4Demo2opEjj:
/* your work */
	mov pc,lr


/* void Demo::swap(unsigned int&, unsigned int&)
                   r0->           r1->
*/
.global _ZN4Demo4swapERjS0_
_ZN4Demo4swapERjS0_:
/* your work */

/* Demo::copy(unsigned int&, unsigned int&) 
*/
/* your work */
