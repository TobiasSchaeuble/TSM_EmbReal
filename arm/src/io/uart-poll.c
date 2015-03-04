/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 see [1] literature/realview_emulation_basebord_ug.pdf 
     [2] literature/pl011-UART.pdf
 TODO realize txQueue    
 -----------------------*/
#include"io/uart-poll.h"
void uart_poll_init()
{
}

void uart_poll_out(char ch)
{
 while(UART0.FR & BUSY ){}             /* wait until busy cleared */
 UART0.DR=ch;
}

char uart_poll_in()
{
 while(UART0.FR & RXFE){}                 /* wait until rx ready */
 return UART0.DR;
}

unsigned uart_poll_avail()
{
 return (UART0.FR & RXFE)==0;
}
