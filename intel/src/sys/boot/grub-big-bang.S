/*----------------------
  grub-big-bang
  (c) H.Buchmann FHNW 2011
  $Id$
  http://www.gnu.org/software/grub/manual/multiboot/html_node/index.html
  TODO: make it with C
------------------------*/
/*------------------------------------------- constants */
#define MAGIC      0x1badb002
#define FLAGS      (1<<0)|(1<<16)
#define CHECKSUM  -(MAGIC+FLAGS)

/*------------------------------------ multiboot header */
.section .header	           /* see linker script */
.MBH:	.long MAGIC
	.long FLAGS
	.long CHECKSUM
	.long .MBH
	.long load_start
	.long load_end
	.long bss_end
	.long _start

