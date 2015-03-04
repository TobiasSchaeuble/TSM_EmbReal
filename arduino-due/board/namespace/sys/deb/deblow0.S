/*------------------------
  deblow0 
  (c) H.Buchmann FHNW 2014
 -------------------------*/
	.syntax unified
.text
.global _ZN3sys3deb4waitEj,sys_deb_wait

/* sys::deb::wait(unsigned count) */
.thumb
.cpu cortex-m3

.thumb_func
_ZN3sys3deb4waitEj:
sys_deb_wait:
0:	subs r0,r0,#1
	bne 0b
	mov pc,lr

/* elementary hex 
 r0 val
*/	
UART=0x400E0800

.global hex
.thumb_func
hex:
	mov r1,#8  	            /* number of nibbles */
	ldr r2,=UART
0:	ror r0,#28
        and r3,r0,#0xf                       /* 0<=r3<16 */
	cmp r3,#10
	blt 1f                                  /* r3<10 */
	add r3,#('a'-10)		   /*10<=r3 < 16 */
	b 2f  
1:	add r3,#'0'

2:	ldr r4,[r2,0x14]	              /* UART_SR */
	tst r4,#(1<<1)
	beq 2b
	str r3,[r2,0x1c]
	sub r1,#1
	cmp r1,#0
	bne 0b
3:	b 3b

