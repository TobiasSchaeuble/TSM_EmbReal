/*---------------------
linker script
(c) H.Buchmann FHNW 2009
$Id: ld.script 97 2009-05-20 09:12:48Z hans.buchmann $
see multiboot specs:
http://www.gnu.org/software/grub/manual/multiboot/html_node/index.html
---------------------*/

/* OUTPUT_FORMAT(binary)   dont works on cygwin obj files PE format */
                                         /* should work with Cygwin */
/* OUTPUT_ARCH(elf64-x86-64) */
SECTIONS
{
 . = (1<<20);  /* 1MByte */
 .text :
 {
/*----------------------------*/
 load_start   = .;
_load_start   = .; 
/*----------------------------*/
  *(.header)
  *(.start)                      /* see grub-image */
  *(.text)    
  *(.rodata*)                  /* dont forget this */
  *(.iplt)
  *(.rela.iplt)
  *(.note.gnu.build*) 
 }	                     /* fill gap with nops */
 .data :
 {
  *(.data)
 }
 load_end = .;
_load_end = .;
 bss_start = .;
_bss_start = .; 
 .bss :
 {
  *(.bss)
 }
 bss_end = .;
_bss_end = .;
 stack = . + 0x10000;
_stack = . + 0x10000;
}
