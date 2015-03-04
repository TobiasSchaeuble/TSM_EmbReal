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
	.file	"memory-mapped-pointer-4.cc"
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
	.text
	.align	2
	.global	_ZN4Demo4initEv
	.thumb
	.thumb_func
	.type	_ZN4Demo4initEv, %function
_ZN4Demo4initEv:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	ldr	r3, .L7
	mov	r2, #2097152
	str	r2, [r3]
	movs	r0, #12
	str	r2, [r3, #16]
	bl	_ZN3sys3SOC11clockEnableENS0_3PIDE
	ldr	r3, .L7+4
	mov	r2, #33554432
	str	r2, [r3]
	str	r2, [r3, #20]
	pop	{r3, pc}
.L8:
	.align	2
.L7:
	.word	1074662912
	.word	1074663424
	.size	_ZN4Demo4initEv, .-_ZN4Demo4initEv
	.align	2
	.global	_ZN4Demo4readEv
	.thumb
	.thumb_func
	.type	_ZN4Demo4readEv, %function
_ZN4Demo4readEv:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	ldr	r3, .L15
	ldr	r6, .L15+4
	ldr	r7, [r3]
	ldr	r5, [r6, #60]
	add	r8, r7, #32
	and	r5, r5, #33554432
	mov	r1, r5
	str	r8, [r7, #60]
	mov	r0, r7
	bl	_ZN2io5ascii6Writer3putEj
	ldr	r1, .L15+8
	bl	_ZN2io5ascii6Writer3putEPKc
.L10:
	ldr	r4, [r6, #60]            @ pioB->PDSR
	and	r4, r4, #33554432        @ and
	cmp	r4, r5                   @ inp1!=inp
	beq	.L10
	mov	r1, r4
	str	r8, [r7, #60]
	mov	r0, r7
	bl	_ZN2io5ascii6Writer3putEj
	ldr	r1, .L15+8
	mov	r5, r4
	bl	_ZN2io5ascii6Writer3putEPKc
	b	.L10
.L16:
	.align	2
.L15:
	.word	_ZN3sys3msgE
	.word	1074663424
	.word	.LC0
	.size	_ZN4Demo4readEv, .-_ZN4Demo4readEv
	.align	2
	.global	_ZN4Demo4menuEv
	.thumb
	.thumb_func
	.type	_ZN4Demo4menuEv, %function
_ZN4Demo4menuEv:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r6, r0
	push	{r3, lr}
	ldr	r3, .L28
	ldr	r5, .L28+4
	ldr	r4, [r3]
.L19:
	ldr	r1, .L28+8
	mov	r0, r4
	bl	_ZN2io5ascii6Writer3putEPKc
	bl	_ZN3sys3deb3getEv
	subs	r0, r0, #48
	cmp	r0, #3
	bhi	.L19
	tbb	[pc, r0]
.L21:
	.byte	(.L20-.L21)/2
	.byte	(.L22-.L21)/2
	.byte	(.L23-.L21)/2
	.byte	(.L24-.L21)/2
	.p2align 1
.L24:
	mov	r0, r6
	bl	_ZN4Demo4readEv
.L23:
	mov	r0, r4
	ldr	r1, .L28+12
	bl	_ZN2io5ascii6Writer3putEPKc
	b	.L19
.L22:
	mov	r3, #2097152
	str	r3, [r5, #52]
	b	.L19
.L20:
	mov	r3, #2097152
	str	r3, [r5, #48]
	b	.L19
.L29:
	.align	2
.L28:
	.word	_ZN3sys3msgE
	.word	1074662912
	.word	.LC1
	.word	.LC2
	.size	_ZN4Demo4menuEv, .-_ZN4Demo4menuEv
	.align	2
	.global	_ZN4DemoC2Ev
	.thumb
	.thumb_func
	.type	_ZN4DemoC2Ev, %function
_ZN4DemoC2Ev:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r4, r0
	push	{r3, lr}
	ldr	r3, .L32
	mov	r2, #2097152
	str	r2, [r3]
	movs	r0, #12
	str	r2, [r3, #16]
	bl	_ZN3sys3SOC11clockEnableENS0_3PIDE
	ldr	r3, .L32+4
	mov	r2, #33554432
	str	r2, [r3]
	mov	r0, r4
	str	r2, [r3, #20]
	bl	_ZN4Demo4menuEv
.L33:
	.align	2
.L32:
	.word	1074662912
	.word	1074663424
	.size	_ZN4DemoC2Ev, .-_ZN4DemoC2Ev
	.global	_ZN4DemoC1Ev
	.thumb_set _ZN4DemoC1Ev,_ZN4DemoC2Ev
	.section	.text.startup,"ax",%progbits
	.align	2
	.thumb
	.thumb_func
	.type	_GLOBAL__sub_I__ZN4Demo4demoE, %function
_GLOBAL__sub_I__ZN4Demo4demoE:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	ldr	r0, .L36
	bl	_ZN4DemoC2Ev
.L37:
	.align	2
.L36:
	.word	.LANCHOR0
	.size	_GLOBAL__sub_I__ZN4Demo4demoE, .-_GLOBAL__sub_I__ZN4Demo4demoE
	.section	.init_array,"aw",%init_array
	.align	2
	.word	_GLOBAL__sub_I__ZN4Demo4demoE(target1)
	.global	_ZN4Demo4pioBE
	.global	_ZN4Demo4pioAE
	.global	_ZN4Demo4demoE
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"\012\000"
	.space	2
.LC1:
	.ascii	"memory-mapped-pointer\012            0: set   led\012"
	.ascii	"            1: clear led\012            2: toggle l"
	.ascii	"ed\012            3: read input\012your choice:\000"
	.space	3
.LC2:
	.ascii	"TODO\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	_ZN4Demo4demoE, %object
	.size	_ZN4Demo4demoE, 1
_ZN4Demo4demoE:
	.space	1
	.ident	"GCC: (GNU) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
