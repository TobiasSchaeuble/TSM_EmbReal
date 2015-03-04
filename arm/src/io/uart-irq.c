/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 see [1] literature/realview_emulation_basebord_ug.pdf 
     [2] literature/pl011-UART.pdf
 TODO realize txQueue    
 -----------------------*/
#include "io/uart-base.h"
#include "io/uart-irq.h"

#include "sys/gic.h"
#include "sys/thread.h"



/*--------------------------------------- foreground - background */
static volatile WaitQueue rxWait;   /* threads waiting for a char */

#define FIFO 4
static volatile struct  
{        /* chars read from hardware not yet consumed by a thread */
 char pool[1<<FIFO];
 unsigned put;
 unsigned get;
 unsigned size;
} charFifo = {put:0,get:0,size:0};

static void fifo_put(char ch)                     /* foreground */
{
 charFifo.pool[charFifo.put++]=ch;
 charFifo.put&=((1<<FIFO)-1); /* fast modulo */
/*<<<<<<<<<<<<<<<< critical */
  if (charFifo.size<(1<<FIFO)) ++charFifo.size;
/*>>>>>>>>>>>>>>>> critical */
 thread_ready_from(&rxWait);

}

char uart_irq_in() /* assuming size>0 */
{
 thread_wait_at(&rxWait);
 if (charFifo.size==0) return 0;
/*<<<<<<<<<<<<<<<< critical */
  --charFifo.size;
/*>>>>>>>>>>>>>>>> critical */
 char ch=charFifo.pool[charFifo.get++];
 charFifo.get&=((1<<FIFO)-1); /* fast modulo */
 return ch;
}

/* TODO make it asynchronous */
void uart_irq_out(char ch) 
{
 while(UART0.FR & BUSY ){}             /* wait until busy cleared */
 UART0.DR=ch;
}

unsigned uart_irq_avail()
{
/*<<<<<<<<<<<<<<<< critical */
 return charFifo.size;
/*>>>>>>>>>>>>>>>> critical */
}


#define UART0_ID 44 /* [1] 4.12.2  */
static void (*listener)(char) = fifo_put; /*the default handler */

static void onRX() /* a character is available */
{
 if (listener)
    {
     listener(UART0.DR);
    }
 UART0.ICR=RXIC;
}


void uart_irq_start()
{
 uart_irq_init();
 gic_init();
 gic_install(UART0_ID,onRX);
 gic_enable(UART0_ID);
 UART0.IMSC|=RXIM;   /* enable interrupt */
}

void uart_irq_install(void (*li)(char))
{
 listener=li;
}

void uart_irq_init()
{
 static unsigned initalized=0;
 if (initalized) return;
 ++initalized;
 /* TODO initialize it */
  while(uart_irq_avail()) /* empty rx buffer */
 {
  uart_irq_in();
 }
 thread_wait_init(&rxWait,0,0);
}


