/*------------------------
  bigBang
  (c) H.Buchmann FHNW 2011
  demonstrates .booting
               .outline of an image
  see ram.ld linker script	       
  $Id$
  [1] literature/ARM-Architecture-Reference-Manual.pdf
  TODO: make a demo for .onSWI
        make an informative message for the unimplemented exceptions
	set the different stacks properly
	do the basic exception handling sys/sys.{h,c}
------------------------*/
.section .boot  /* see [1] A2.6 */
/* one word per entry
  ldr pc,=address_of_handler
*/                                 /*offset description */
	ldr pc,=.onReset           /*  0x00 A2.6.2 */
	ldr pc,  onUndef           /*  0x04 A2.6.3 notice the notation */
	ldr pc,=.onSWI             /*  0x08 A2.6.4 */
	ldr pc,=.onPrefetchAbort   /*  0x0c A2.6.5 */
	ldr pc,=.onData            /*  0x10 A2.6.6 */
	ldr pc,=.onReserved        /*  0x14  should never be called */
	ldr pc,=.onIRQ             /*  0x18 A2.6.8 */
	ldr pc,=.onFIQ             /*  0x1c A2.6.9 */

.global onUndef                   /* global label */
onUndef:	.word .onUndef    /* filled with .onUndef */

/*------------------------------------------ text */
.text
.onReset:
	bl .setStack
	bl _start      /* call _start a C routine */ 
	b .do_reset

	
/*--------------------------------- the unimplemented traps */
.onSWI:
.onPrefetchAbort:
.onData:
.onReserved:
.onIRQ:
.onFIQ:
	b deb_signal0

/*------------------------------------------ the undef trap */
.onUndef:
	mov r0,lr                      /* lr return address */
	bl deb_hex
	b deb_signal1
	
/*--------------------------------- some internal functions */
.setStack:
	ldr sp,=.stack_top
	mov pc,lr

.do_reset:	                            /* make a reset */
	ldr r0,=0x1000000c
	orr r1,r1,#(1<<3)
	str r1,[r0]   /* reset */
	
/*--------------------------------------------------- stack */
.section .stack	
	.space 4*IRQ_STACK_SIZE_WORD
.irq_stack_top:
	.space 4*STACK_SIZE_WORD
.stack_top:
