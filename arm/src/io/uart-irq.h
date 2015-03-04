#pragma once
/*----------------------
 uart-irq only valid for UART0
 (c) H.Buchmann FHNW 2011
 $Id$
 -----------------------*/

extern void uart_irq_init();
extern void uart_irq_install(void (*li)(char));                  /* the trap */
extern void uart_irq_start();                          /* with traps enabled */


extern void uart_irq_out(char ch);              /* TODO make it asynchronous */
extern char uart_irq_in();                      /* wait until char available */
extern unsigned uart_irq_avail();
