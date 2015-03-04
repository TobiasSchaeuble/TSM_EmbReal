/*-------------------------------------
 hex prints hex value  
 (c) H.Buchmann FHNW 2009
 demonstrates  .addressing 
               .numeric labels
               .shifting
 $Id$
 --------------------------------------*/

/*----------------------------------------------- constants */
#define MAGIC      0x1badb002
#define FLAGS      (1<<0)|(1<<16)
#define CHECKSUM  -(MAGIC+FLAGS)
#define VIDEO_RAM  0xb8000

/*---------------------------------------- multiboot header */
.section .header	               /* see linker script */
MBH:	.long MAGIC
	.long FLAGS
	.long CHECKSUM
	.long MBH
	.long load_start
	.long load_end
	.long bss_end
	.long start

/*--------------------------------------------------------- */
start:	mov $0x9abcdef0,%eax
	call hex
	

/*----------------------------------------------------- hex */
/* %eax number to */
/* never leaves */
.text
.global hex                        /* must be known outside */ 
hex:   	xor %edi,%edi                  /* upper left corner */
	mov $8,%ecx                         /* nibble count */
0:	jecxz 3f	          /* ecx=0 all nibbles done */

	ror $28,%eax
	mov %eax,%ebx
	and $0xf,%ebx	            /* 0<=ebx<16 the nibble */
	cmp $10,%ebx	
	jl 1f	                               /* 0<=ebx<10 */
	add $('a'-10),%ebx     /* 10<=ebx<16 ebx=ebx-10+'a' */
	jmp 2f

1:	add $'0',%ebx
2:	or $0x700,%ebx	                  /* set attributes */
	mov %bx,VIDEO_RAM(,%edi,2)    /* transfer to screen */
	inc %edi
	dec %ecx
	jmp 0b
		
3:	jmp 3b	                            /* loop forever */
