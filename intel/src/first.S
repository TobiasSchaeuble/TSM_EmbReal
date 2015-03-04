/*----------------------
  first
  (c) H.Buchmann FHNW 2011
  $Id$
  http://www.gnu.org/software/grub/manual/multiboot/html_node/index.html
------------------------*/
/* format 
   mov src,dst
   op  a1,a2:   a2 <- a2 op a1
*/
/*------------------------------------------- constants */
#define MAGIC      0x1badb002
#define FLAGS      (1<<0)|(1<<16)
#define CHECKSUM  -(MAGIC+FLAGS)

#define VIDEO_RAM  0xb8000
#define ROW 25                    /* the number of rows */
#define COL 80                    /* the number of cols */

/*------------------------------------ multiboot header */
.section .header	           /* see linker script */
MBH:	                            /* multiboot header */
	.long MAGIC
	.long FLAGS
	.long CHECKSUM
	.long MBH
	.long load_start
	.long load_end
	.long bss_end
	.long start

.text
start:	mov $VIDEO_RAM,%ebx               /* Video base */
	xor %edi,%edi             /* index in video ram */
0:	movw $0x0730,(%ebx,%edi,2)  /* ebx[edi]=0x730   */ 
	           /* typical CISC command const -> mem */
		   /* %ebx+2*%edi  */
	inc %edi
	cmp $(ROW*COL),%edi
	jne 0b
1:	jmp 1b
