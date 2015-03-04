#pragma once
/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 -----------------------*/
#include "io/uart-base.h" 
extern void uart_poll_init();
extern void uart_poll_out(char ch); 
extern char uart_poll_in();                             /* waits until ready */
extern unsigned uart_poll_avail();         /* returns true if char available */
