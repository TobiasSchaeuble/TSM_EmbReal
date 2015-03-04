/*----------------
 iso-big-bang 
 (c) H.Buchmann FHNW 2010
 $Id$
 literature:
 [1] Intel 64 and IA-32 Architectures
     Software Developer's Manual
     Volume 3A:
 [2] http://www.ctyme.com/ 
 ----------------*/

#define SCREEN         0xb8000 
#define ERR_CDROM_SPEC 0x1111
#define ERR_SECTOR     0x2222
#define ADR(val) (val-(1<<20)+0x7c00)

/*----------------------------- macro for hexadecimal output */
#define HEX \
	mov $SCREEN+2,%edi;                /* upper left +1 */\
	mov %eax,%edx;	                     /* save in edx */\
	mov $32,%ecx;	                /* count: 4 nibbles */\
0:	sub $4,%ecx;	                     /* next nibble */\
1:	jc 1b;		          /*  all done loop forever */\
	mov %edx,%eax;	                        /*  restore */\
	shr %cl,%eax;\
	and $0xf,%eax;  /*  bits 0..3 digit value 0..9 a..f */\
	cmp $10,%eax;	                     /*  %ax-10 < 0 */\
	jc 2f;\
	add $('a'-10),%eax;              /*  digit 'a'..'f' */\
	jmp 3f; \
2:	add $'0',%eax;\
3:	mov $0x07,%ah;                    /*  char out attr */\
	mov %ax,(%edi);\
	add $2,%edi;\
	jmp 0b		                    /*  next nibble */


.section .big_bang                /* see iso.ld linker script */
.code16
/*---------------------------------------- entry 0x0000:0x7c00 */
/* real mode */
big_bang:	                             /* called by bios */
	cli                       /* clear interrupts for sure */
	jmp 0f		                       /* relative jmp */ 
/*------------------------------------- filled by for mkisofs  */
	. = big_bang+0x08
.bi_pvd:	.long 0	
.bi_file:	.long 0
.bi_length:	.long 0
.bi_csum:	.long 0

	. = big_bang+0x40            
/*------------------------------------------------------ start */	
0:	xor %ax,%ax
	mov %ax,%ds                       /* data segment zero */

/*------------------------------------ write 'R' to the screen */
	mov $0x07,%ah
	mov $'R',%al

/*------------------------------------------- read .CDROM_SPEC */
	mov $0x4b01,%ax
	mov $0x80,  %dl
	mov $ADR(.CDROM_SPEC),%esi
	int $0x13
	jnc .copy
	mov $ERR_CDROM_SPEC,%ax   /* error */
	jmp hex16

.copy:
/*------------------------------------- copy .bi_file to .DAP */
	mov $ADR(.bi_file),%esi
	mov (%esi),%eax
	mov $ADR(.DAP),%esi
	mov %eax,8(%esi)

.read_sector:
/*----------------------------------------------- read sector */
	mov $0x42,%ah
	mov $ADR(.CDROM_SPEC),%esi
	mov 2(%si),%dl
	mov $ADR(.DAP),%esi
	int $0x13
	jnc 0f
	mov $ERR_SECTOR,%ax
	jmp hex16

/*----------------------------------------------- copy sector */
0:	mov $ADR(sector),%esi  /* src */
	mov $ADR(.dst),%edi   
	mov (%edi),%edi
	mov $0x800,%cx	       /* size of block */

1:	mov %ds:(%esi),%eax
	mov %eax,%ds:(%edi)

	add $4,%esi
	add $4,%edi
	sub $4,%cx
	jnz 1b

	mov $ADR(.dst),%esi
	mov %edi,(%esi)             /* save .dst */
	
        mov $ADR(.DAP),%esi
	add $1,8(%esi)               /* next LBA */

	mov $ADR(.bi_length),%esi
	mov (%esi),%eax
	sub $0x800,%eax      /* .bi_length-0x800 */
	mov %eax,(%esi)	              /* save it */	
	jg .read_sector	
	jmp .protected

/*------------------------------------------ data */
	.align 4
.CDROM_SPEC:	 /*  [2] Int 13/AH=4Ah */
	.byte 0	 /* 0: size of packet in bytes 0x13*/
	.byte 0	 /* 1: boot media type */
	.byte 0	 /* 2: drive number */
	.byte 0	 /* 3: CD-ROM controller number */
 	.long 0	 /* 4: Logical Block Address of disk image to emulate */
	.word 0  /* 8: device specification */
	.fill 16 /* seems to be longer than written in [2] */

	.align 4
.DAP:	/* disk ddress packet */
	.byte 0x10         /*  0: size .DAP */
	.byte 0            /*  1: unused */
	.word 1            /*  2: number of sectors */
	.long ADR(sector)  /*  4: offset:segment */
	.long 0            /*  8: LBA  see .copy */
	.long 0	           /* 12:       */

.dst:	.long big_bang    


/*------------------------------------------ debug */
.code16
hex16:	HEX  /* see macro HEX */

/*------------------------------------ enter protected mode */
                                    /* [1] Fig 2.6 CR0 bits */
#define PE_BIT (1<<0)
#define CS 0x08
#define DS 0x10
.protected:
	cli	                                /* for sure */
	xorw	%ax, %ax
	movw	%ax, %ds
	DATA32 ADDR32 lgdt gdt
	movl %cr0, %eax	               /* set PE bit of CR0 */
	orl  $PE_BIT, %eax
	movl %eax, %cr0
	DATA32 ljmp $CS,$0f

/*-------------------------------- we are in protected mode */
.code32	 
0:	mov $DS,%ax
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%fs
	mov %ax,%gs
	mov %ax,%ss
		

/*---------------------------------- write 'P' to the screen */
	mov $0x7,%ah
	mov $'P',%al
	mov %ax,SCREEN
		
/*---------------------setup stack see iso.ld linker script */
	mov $stack,%esp
	call start 
	mov last,%eax
	jmp hex32
	
	.global hex32
hex32:	HEX  /* see macro HEX */
	
/*--------------------------------- global descriptor table */
/* [1] Fig.4.1 */
/* flat memory */
#define CS_TYPE  (0x9a<<8)|(0xcf<<16) 
#define DS_TYPE  (0x92<<8)|(0xcf<<16)
	.align 8	/* GDT descriptors  8 byte boundary */
0:	.long 0,0                            /* nil segment */
	                           
	.long 0x0000ffff	         /* 8: code segment */
	.long CS_TYPE 

	.long 0x0000ffff	         /*10: data segment */
	.long DS_TYPE 

gdt:	.word 3*8-1
	.long 0b

/*---------------------------------------------------- data */
	.align 4
sector:	.fill 0x800
last:
	.word 0xabcd
