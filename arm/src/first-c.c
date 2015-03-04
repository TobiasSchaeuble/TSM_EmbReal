/*----------------------
  first-c.c
  (c) H.Buchmann FHNW 2011
  demonstrates .Makefile
               .booting /bigBang 
  see [UART]
  TODO using sos/io/ascii
  $Id$
-----------------------*/
volatile struct
{
 unsigned DR;     /* Data register, UARTDR */
 unsigned RSR;    /* Receive status register/error clear register */
 unsigned RES[4]; /* reserved */
 unsigned FG;     /* Flag register */
}* UART = 0x16000000;


static void uart_char(char ch)
{
 while(UART->FG&(1<<3)){} /* wait until ready */
 UART->DR=ch;
}

static void uart_string(const char s[])
{
 for(unsigned i=0;s[i]!='\0';++i) uart_char(s[i]);
}

void _start() /* called from sys/bigBang */
{
 uart_string("Hello World\n");
}
  
