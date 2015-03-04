/*----------------------
  big-bang.S
  (c) H.Buchmann FHNW 2014
 -----------------------*/
WDT_MR=0x400e1a54
PIOB=0x400e1000 
LED =1<<27
PIO_PER=0
PIO_OER=0x10
PIO_SODR=0x30
PIO_CODR=0x34
CNT=0x40000
 
.thumb
.cpu cortex-m3
.section .boot, "x" 
0:	.word	STACK_TOP                      /* see linker script */
	.word   _ZN3sys5Board7bigBangEv      /* bit 0 set for thumb */
	.word   0                                  /* set by linker */
	            /*    |---------------thumb bit */ 

#if 0
.text
.thumb_func
.reset:                         /*watch dog enabled */
 	cpsid i		      /* disable interrupts */
	cpsid f                   /* disable faults */
	bl .disable_watchdog  
	b _ZN3sys4boot5startEv
	
.disable_watchdog:
 	ldr r0,=WDT_MR
	ldr r1,=(1<<15)        /* disable watch dog */
	str r1,[r0]
	mov pc,lr
	
#if 0
.blink:
	ldr r0,=PIOB
	ldr r1,=LED
	str r1,[r0,#PIO_PER] 
	str r1,[r0,#PIO_OER]
	ldr r2,=CNT

1:	str r1,[r0,#PIO_CODR] /* clear */
	
	mov r3,r2
2:	sub r3,#1
	bne 2b
	
	str r1,[r0,#PIO_SODR] /* set */
	mov r3,r2
3:	sub r3,#1
	bne 3b
	b 1b
#endif
#endif
