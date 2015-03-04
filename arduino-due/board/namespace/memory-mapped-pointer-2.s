	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"memory-mapped-pointer-2.cc"
	.section	.text._ZNK2io5ascii3hex4doItERNS0_6WriterE,"axG",%progbits,_ZNK2io5ascii3hex4doItERNS0_6WriterE,comdat
	.align	2
	.weak	_ZNK2io5ascii3hex4doItERNS0_6WriterE
	.thumb
	.thumb_func
	.type	_ZNK2io5ascii3hex4doItERNS0_6WriterE, %function
_ZNK2io5ascii3hex4doItERNS0_6WriterE:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	add	r3, r1, #32
	str	r3, [r1, #60]
	mov	r0, r1
	bx	lr
	.size	_ZNK2io5ascii3hex4doItERNS0_6WriterE, .-_ZNK2io5ascii3hex4doItERNS0_6WriterE
	.section	.text._ZN2io5ascii3hexD2Ev,"axG",%progbits,_ZN2io5ascii3hexD5Ev,comdat
	.align	2
	.weak	_ZN2io5ascii3hexD2Ev
	.thumb
	.thumb_func
	.type	_ZN2io5ascii3hexD2Ev, %function
_ZN2io5ascii3hexD2Ev:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	_ZN2io5ascii3hexD2Ev, .-_ZN2io5ascii3hexD2Ev
	.weak	_ZN2io5ascii3hexD1Ev
	.thumb_set _ZN2io5ascii3hexD1Ev,_ZN2io5ascii3hexD2Ev
	.section	.text._ZN2io5ascii3hexD0Ev,"axG",%progbits,_ZN2io5ascii3hexD5Ev,comdat
	.align	2
	.weak	_ZN2io5ascii3hexD0Ev
	.thumb
	.thumb_func
	.type	_ZN2io5ascii3hexD0Ev, %function
_ZN2io5ascii3hexD0Ev:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r4, r0
	bl	_ZdlPv
	mov	r0, r4
	pop	{r4, pc}
	.size	_ZN2io5ascii3hexD0Ev, .-_ZN2io5ascii3hexD0Ev
	.section	.text._ZN2io5ascii6WriterlsEPKc,"axG",%progbits,_ZN2io5ascii6WriterlsEPKc,comdat
	.align	2
	.weak	_ZN2io5ascii6WriterlsEPKc
	.thumb
	.thumb_func
	.type	_ZN2io5ascii6WriterlsEPKc, %function
_ZN2io5ascii6WriterlsEPKc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	_ZN2io5ascii6Writer3putEPKc
	.size	_ZN2io5ascii6WriterlsEPKc, .-_ZN2io5ascii6WriterlsEPKc
	.section	.text._ZN2io5ascii6WriterlsEj,"axG",%progbits,_ZN2io5ascii6WriterlsEj,comdat
	.align	2
	.weak	_ZN2io5ascii6WriterlsEj
	.thumb
	.thumb_func
	.type	_ZN2io5ascii6WriterlsEj, %function
_ZN2io5ascii6WriterlsEj:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	_ZN2io5ascii6Writer3putEj
	.size	_ZN2io5ascii6WriterlsEj, .-_ZN2io5ascii6WriterlsEj
	.section	.text._ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE,"axG",%progbits,_ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE,comdat
	.align	2
	.weak	_ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE
	.thumb
	.thumb_func
	.type	_ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE, %function
_ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r1
	ldr	r2, [r3]
	mov	r1, r0
	ldr	r2, [r2]
	mov	r0, r3
	bx	r2
	.size	_ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE, .-_ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE
	.section	.text._ZN2io5ascii3hexC2Ev,"axG",%progbits,_ZN2io5ascii3hexC5Ev,comdat
	.align	2
	.weak	_ZN2io5ascii3hexC2Ev
	.thumb
	.thumb_func
	.type	_ZN2io5ascii3hexC2Ev, %function
_ZN2io5ascii3hexC2Ev:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L9
	str	r3, [r0]
	bx	lr
.L10:
	.align	2
.L9:
	.word	_ZTVN2io5ascii3hexE+8
	.size	_ZN2io5ascii3hexC2Ev, .-_ZN2io5ascii3hexC2Ev
	.weak	_ZN2io5ascii3hexC1Ev
	.thumb_set _ZN2io5ascii3hexC1Ev,_ZN2io5ascii3hexC2Ev
	.text
	.align	2
	.global	_ZN4Demo4initEv
	.thumb
	.thumb_func
	.type	_ZN4Demo4initEv, %function
_ZN4Demo4initEv:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, .L12
	mov	r2, #2097152
	str	r2, [r3]
	ldr	r3, .L12
	mov	r2, #2097152
	str	r2, [r3, #16]
	movs	r0, #12
	bl	_ZN3sys3SOC11clockEnableENS0_3PIDE
	ldr	r3, .L12+4
	mov	r2, #33554432
	str	r2, [r3]
	ldr	r3, .L12+4
	mov	r2, #33554432
	str	r2, [r3, #20]
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L13:
	.align	2
.L12:
	.word	1074662912
	.word	1074663424
	.size	_ZN4Demo4initEv, .-_ZN4Demo4initEv
	.section	.rodata
	.align	2
.LC0:
	.ascii	"\012\000"
	.text
	.align	2
	.global	_ZN4Demo4readEv
	.thumb
	.thumb_func
	.type	_ZN4Demo4readEv, %function
_ZN4Demo4readEv:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r7, lr}
	sub	sp, sp, #28
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, .L17
	ldr	r3, [r3, #60]
	and	r3, r3, #33554432
	str	r3, [r7, #20]
	ldr	r3, .L17+4
	ldr	r3, [r3]
	mov	r4, r3
	add	r3, r7, #8
	mov	r0, r3
	bl	_ZN2io5ascii3hexC1Ev
	add	r3, r7, #8
	mov	r0, r4
	mov	r1, r3
	bl	_ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE
	mov	r3, r0
	mov	r0, r3
	ldr	r1, [r7, #20]
	bl	_ZN2io5ascii6WriterlsEj
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L17+8
	bl	_ZN2io5ascii6WriterlsEPKc
.L16:
	ldr	r3, .L17
	ldr	r3, [r3, #60]                @ r3=pioB->PDSR
	and	r3, r3, #33554432            @ 33554432=1<<25 INPUT
	str	r3, [r7, #16]
	ldr	r2, [r7, #16]
	ldr	r3, [r7, #20]
	cmp	r2, r3                       @ inp1!=inp
	beq	.L15
	ldr	r3, [r7, #16]
	str	r3, [r7, #20]
	ldr	r3, .L17+4
	ldr	r3, [r3]
	mov	r4, r3
	add	r3, r7, #12
	mov	r0, r3
	bl	_ZN2io5ascii3hexC1Ev
	add	r3, r7, #12
	mov	r0, r4
	mov	r1, r3
	bl	_ZN2io5asciilsERNS0_6WriterERKNS0_9FormatterE
	mov	r3, r0
	mov	r0, r3
	ldr	r1, [r7, #20]
	bl	_ZN2io5ascii6WriterlsEj
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L17+8
	bl	_ZN2io5ascii6WriterlsEPKc
.L15:
	b	.L16
.L18:
	.align	2
.L17:
	.word	1074663424
	.word	_ZN3sys3msgE
	.word	.LC0
	.size	_ZN4Demo4readEv, .-_ZN4Demo4readEv
	.section	.rodata
	.align	2
.LC1:
	.ascii	"memory-mapped-pointer\012            0: set   led\012"
	.ascii	"            1: clear led\012            2: toggle l"
	.ascii	"ed\012            3: read input\012your choice:\000"
	.align	2
.LC2:
	.ascii	"TODO\012\000"
	.text
	.align	2
	.global	_ZN4Demo4menuEv
	.thumb
	.thumb_func
	.type	_ZN4Demo4menuEv, %function
_ZN4Demo4menuEv:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
.L26:
	ldr	r3, .L27
	ldr	r3, [r3]
	mov	r0, r3
	ldr	r1, .L27+4
	bl	_ZN2io5ascii6WriterlsEPKc
	bl	_ZN3sys3deb3getEv
	mov	r3, r0
	subs	r3, r3, #48
	cmp	r3, #3
	bhi	.L26
	adr	r2, .L22
	ldr	pc, [r2, r3, lsl #2]
	.p2align 2
.L22:
	.word	.L21+1
	.word	.L23+1
	.word	.L24+1
	.word	.L25+1
	.p2align 1
.L21:
	ldr	r3, .L27+8
	mov	r2, #2097152
	str	r2, [r3, #48]
	b	.L20
.L23:
	ldr	r3, .L27+8
	mov	r2, #2097152
	str	r2, [r3, #52]
	b	.L20
.L24:
	ldr	r3, .L27
	ldr	r3, [r3]
	mov	r0, r3
	ldr	r1, .L27+12
	bl	_ZN2io5ascii6WriterlsEPKc
	b	.L20
.L25:
	ldr	r0, [r7, #4]
	bl	_ZN4Demo4readEv
	nop
.L20:
	b	.L26
.L28:
	.align	2
.L27:
	.word	_ZN3sys3msgE
	.word	.LC1
	.word	1074662912
	.word	.LC2
	.size	_ZN4Demo4menuEv, .-_ZN4Demo4menuEv
	.align	2
	.global	_ZN4DemoC2Ev
	.thumb
	.thumb_func
	.type	_ZN4DemoC2Ev, %function
_ZN4DemoC2Ev:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r0, [r7, #4]
	bl	_ZN4Demo4initEv
	ldr	r0, [r7, #4]
	bl	_ZN4Demo4menuEv
	ldr	r3, [r7, #4]
	mov	r0, r3
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	_ZN4DemoC2Ev, .-_ZN4DemoC2Ev
	.global	_ZN4DemoC1Ev
	.thumb_set _ZN4DemoC1Ev,_ZN4DemoC2Ev
	.section	.text.startup,"ax",%progbits
	.align	2
	.thumb
	.thumb_func
	.type	_GLOBAL__sub_I__ZN4Demo4demoE, %function
_GLOBAL__sub_I__ZN4Demo4demoE:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r0, .L33
	b	_ZN4DemoC2Ev
.L34:
	.align	2
.L33:
	.word	_ZN4Demo4demoE
	.size	_GLOBAL__sub_I__ZN4Demo4demoE, .-_GLOBAL__sub_I__ZN4Demo4demoE
	.section	.init_array,"aw",%init_array
	.align	2
	.word	_GLOBAL__sub_I__ZN4Demo4demoE(target1)
	.weak	_ZTVN2io5ascii3hexE
	.section	.rodata._ZTVN2io5ascii3hexE,"aG",%progbits,_ZTVN2io5ascii3hexE,comdat
	.align	3
	.type	_ZTVN2io5ascii3hexE, %object
	.size	_ZTVN2io5ascii3hexE, 20
_ZTVN2io5ascii3hexE:
	.word	0
	.word	0
	.word	_ZNK2io5ascii3hex4doItERNS0_6WriterE
	.word	_ZN2io5ascii3hexD1Ev
	.word	_ZN2io5ascii3hexD0Ev
	.global	_ZN4Demo4pioBE
	.global	_ZN4Demo4pioAE
	.global	_ZN4Demo4demoE
	.bss
	.align	2
	.type	_ZN4Demo4demoE, %object
	.size	_ZN4Demo4demoE, 1
_ZN4Demo4demoE:
	.space	1
	.section	.rodata
	.align	2
	.type	_ZN4Demo4pioBE, %object
	.size	_ZN4Demo4pioBE, 4
_ZN4Demo4pioBE:
	.word	1074663424
	.type	_ZN4Demo4pioAE, %object
	.size	_ZN4Demo4pioAE, 4
_ZN4Demo4pioAE:
	.word	1074662912
	.ident	"GCC: (GNU) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
