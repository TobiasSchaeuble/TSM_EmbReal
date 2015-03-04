/*-----------------------------
 reg status and system control registers
 see [RealViewEmulationBaseboard] 4.3
 (c) H.Buchmann FHNW 2012
 $Id$
 [1] literature/ARM-Architecture-Reference-Manual.pdf
 ------------------------------*/
#include "sys/sys.h"

/* compile with 
 arm-xxxxxxx-gcc -S -O2 -o sys/sys.s ../src/sys/sys.c
 to see the generated machine code
*/
void sys_undef() /* example of inline assembler */
{
 asm volatile  /* see [1] A3.1 */
 (      /* fedcba9876543210fedcba9876543210 */
        /* cccc00110x00xxxxxxxxxxxxxxxxxxxx */
        /* 1110 always */
  ".word 0b11100011000011111111111111111111\n\t"   
  :
  :
 );
}
 

/* test */
#if 0
#include "stdio.h"
int main()
{
 printf("MCI        =%x\n"
        "CONFIGDATA =%x\n"
	"FLAGS      =%x FLAGSSET =%x\n"
        "OSCRESET   =%x\n"
        "PLDCTL     =%x\n"
        ,&SYS.MCI
	,SYS.CONFIGDATA
	,&SYS.FLAGS,&SYS.FLAGSSET
	,SYS.OSCRESET
	,SYS.PLDCTL);
 return 0;
}
#endif

