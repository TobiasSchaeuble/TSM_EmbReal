/*-----------------------------
  deb0
  (c) H.Buchmann FHNW 2013
 ------------------------------*/
.text 

/* 
 unsigned  r0, r1, r2, r3,
           r4, r5, r6, r7,
	   r8, r9,r10,r11,
	  r12,
	  sp,
	  lr,
	  pc;
*/
.global deb_register
deb_register:
	sub sp,sp,#4*16
	stm sp,{r0-r15}
	mov r0,sp
	push {lr}
	bl deb_showregister
	pop {lr}
	add sp,sp,#4*16
	bx lr
	
