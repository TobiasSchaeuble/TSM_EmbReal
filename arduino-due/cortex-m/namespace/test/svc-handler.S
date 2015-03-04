/*-------------------
  svc-handler
 (c) H.Buchmann FHNW 2014
 --------------------*/
PIOB=0x400e1000 
LED =1<<27
PIO_PER=0
PIO_OER=0x10
PIO_SODR=0x30
PIO_CODR=0x34
CNT=0x400000
.thumb
.cpu cortex-m3

.text
  
.thumb_func
.global on_svc

on_svc:
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
