#ifndef IO_KBD_H
#define IO_KBD_H
//--------------------------
//kbd
//(c) H.Buchmann FHNW 2009
//$Id$
//--------------------------
extern void kbd_init();   /* initialize must be called first */
extern char kbd_get();            /* waits until key pressed */
                                                  /* polling */
#endif
