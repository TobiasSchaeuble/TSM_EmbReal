#ifndef SYS_TRAP_H
#define SYS_TRAP_H
/*---------------------
 trap
 (c) H.Buchmann FHNW 2009
 $Id$
-----------------------*/
typedef void (*Trap)(unsigned id); /* the call back */

extern void trap_init();
/* TODO ensure proper disabling/enabling */
extern void trap_install(unsigned id,Trap t);
extern void trap_show();
#endif
