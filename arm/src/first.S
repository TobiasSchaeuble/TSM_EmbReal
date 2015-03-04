/*--------------------------
first
 - testing and configuring qemu
 - setting up the Makefile 
 - PIC position independent code

 - see [RealViewEmulationBaseboard] 
   4.23 UART
 - see [UART_PL011] 
   3.0 Programmer's Model
 
 - see ../tools/run.sh for qemu  
(c) H.Buchmann FHNW 2012 
TODO: why SYS_LED dont works ?
$Id$
--------------------------*/
	ldr r0,UART0   
	mov r1,#'0'	            /* char to be printed */

0:	ldr r2,[r0,#0x18]                /* flag register */
	ands r2,r2,#(1<<3)                       /* busy  */
	bne 0b
	str r1,[r0]
	b 0b
	
UART0:	 .word 0x10009000

