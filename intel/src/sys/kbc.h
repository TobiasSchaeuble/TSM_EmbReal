#ifndef SYS_KBC_H
#define SYS_KBC_H
/*-----------------
 kbc keyboard controller
 (c) H.Buchmann FHNW 2009
 $Id$
-------------------*/
typedef void (*kbc_Listener)(unsigned);

extern void kbc_init();
extern void kbc_setListener(kbc_Listener li);
#endif
