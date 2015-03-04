/*-------------------------
start for non posix systems
(c) H.Buchmann FHNW 2009
$Id$
see big-bang
---------------------------*/
#include "stdout.h"
extern int main();

extern unsigned bss_start[];                 /* see linker script */
extern unsigned bss_end[];

void _start()                             /* called from bigBang */
{
/* ---------------------- init bss */
 for(unsigned* v=bss_start;v!=bss_end;v++)*v=0;
/* ---------------------- initialize */
 stdout_init();
 main();                                            /* call main */
}
