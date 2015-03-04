#pragma once
/*----------------------
 uart-base for uart-polling and uart-irq 
 (c) H.Buchmann FHNW 2011
 see [1] literature/realview_emulation_basebord_ug.pdf 
     [2] literature/pl011-UART.pdf
 -----------------------*/
typedef volatile struct                             /* see [2] 3.2 */
{
       unsigned DR;                              /* Data register */ 
       unsigned SR;                             /* Receive status */
       unsigned res0[4];                              /* reserved */
 const unsigned FR;                                       /* Flag */
       unsigned res1[1]; 
       unsigned ILPR;          /* IrDA low-power counter register */
       unsigned IBRD;               /* Integer baud rate register */
       unsigned FBRD;            /* Fractional baud rate register */
       unsigned LCR_H;                  /* Line control register, */
       unsigned CR;                           /* Control register */
       unsigned IFLS;    /* Interrupt FIFO level select register, */
       unsigned IMSC;        /* Interrupt mask set/clear register */
 const unsigned RIS;             /* Raw interrupt status register */
 const unsigned MIS;          /* Masked interrupt status register */
       unsigned ICR;                  /* Interrupt clear register */
} UART;                                   /* the device registers */


/*--------------------------------------------------------- flags */
#define RXFE (1<<4) /* see [2] 3.3.3  */
#define RXIM (1<<4) /* see [2] 3.3.10 */
#define RXIC (1<<4) /* see [2] 3.3.13 */
#define BUSY (1<<3)

extern UART UART0;
extern UART UART1;
extern UART UART2;
extern UART UART3;
