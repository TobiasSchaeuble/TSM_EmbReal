/*
 mix assembler/C 
 see:  http://gcc.gnu.org/onlinedocs/gcc-4.8.1/gcc/Extended-Asm.html#Extended-Asm
*/
#include "sys/deb.h"
#include "sys/arm.h"
#include <stdio.h>

#if 0
void deb_register(){
     int register0;
     int register1;
     asm(
      "mov %[result],r0\n\t"
      :[result] "=r" (register0)
      :
     );
     asm(
      "mov %[result],r1\n\t"
      :[result] "=r" (register1)
      :
     );

#if 0     
     asm("CPY register0, r0\n" /* real assembler code */

         "CPY register1, r1"
     );
#endif
     deb_hex(register0);
     deb_newln();
     deb_hex(register1);
     deb_newln();
}
#endif
volatile unsigned x=0x1234;
void main()
{
 printf("sp=%x\n",arm_get_sp());
 x=0x5678;
 deb_register();
 printf("sp=%x\n",arm_get_sp());
}

