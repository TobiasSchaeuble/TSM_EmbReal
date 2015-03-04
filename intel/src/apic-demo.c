/*------------------
 apic-demo
 (c) H.Buchmann FHNW 2009
 $Id$
--------------------*/
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/sys.h"

int main()
{
 unsigned data=0x12345678;
 unsigned* APIC_VERSION=(unsigned*)0xfee00030;
 volatile MSR msr=sys_read_msr(0x1b);
 ascii_printf(Screen,"VERSION=%x\n"
                     "msr    =%x%x\n"
              ,*APIC_VERSION,(unsigned)(msr>>32),(unsigned)msr);
 return 0;
} 
