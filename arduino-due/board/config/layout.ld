/*
---------------------------
layout no memory map
(c) H.Buchmann FHNW 2014
[1] at91sam3x.pdf
     22.5
---------------------------
FLASH 2 x 256 KiB mapped to 0

--------- 0x00080000 
 256 KiB
--------- 0x000c0000 
 256 KiB
--------- 0000100000

--------- 0x20000000
 64 KiB
--------- 0x20010000


--------- 0x20080000
 32 KiB
--------- 0x20088000 

SRAM  64 + 32 KiB
NFC SRAM 4KiB

*/

SECTIONS
{
/*---------------------------------------- text */ 
 .text 0x0 : {
 	  *(.boot) /* must be first */
	  *(.glue_7)
	  *(.glue_7t)
          *(.text.startup .text .text.*)
	  *(.rodata)
	  *(.rodata.*)
	  *(.module)
	  *(.gnu.linkonce.*)
 . = ALIGN(4);
__GLOBAL__CONSTRUCTORS = .;
__GLOBAL__CONSTRUCTORS_BEG = . ;
          *(.init_array)
__GLOBAL__CONSTRUCTORS_END = . ;
	  LONG(0)    /* terminates global constructor list */  
 . = ALIGN(4);
 
__BUILD_ID = . ;
	*(.note.gnu.build-id)

_text_end = .;
	     }
 .ARM.extab :
 {
 	*(.ARM.extab*)
 }
 .ARM.exidx :
 {
 __exidx_start = . ;
	  *(.ARM.exidx*)
 __exidx_end = . ;
 }

/*---------------------------------------- data */ 
 .data 0x20000000: AT(ADDR(.text)+SIZEOF(.text)+SIZEOF(.ARM.exidx)+SIZEOF(.ARM.extab))
 {
_data_beg = .;
          *(.data)
. = ALIGN(4);
_data_end   = .;
 }




_ZN3sys5Flash4BASEE = 0x00080000;
_ZN3sys5Flash4FREEE = 0x00080000+SIZEOF(.text)+SIZEOF(.data);


/*---------------------------------------- bss */ 
 .bss : {
. = ALIGN(4);
_bss_beg = .; 
          *(.bss)
. = ALIGN(4);
_bss_end   = .;
 	}

STACK_TOP=0x20088000;

/DISCARD/ : {
  *(.v4_bx)
  *(.vfp11_veneer)
}

}

/*------------------------- see memory-mapped-extern 
[1] Section 8 */

pioA  = 0x400e0e00 ;
pioB  = 0x400e1000 ;
/*---------------------------------------------------*/


/*------------------------- see memory-mapped-extern 
[1] 12.21.5 */
VTOR = 0xE000ED08 ;
ICSR = 0xE000ED04 ; 
_ZN3sys3reg4NVICE = 0xE000E100 ;
/*---------------------------------------------------*/

PIOA  = 0x400e0e00 ;
PIOB  = 0x400e1000 ;
PIOC  = 0x400e1200 ;
PIOD  = 0x400e1400 ;
PMC  = 0x400e0600 ;
_ZN3sys3reg3PMCE = PMC ;
UART  = 0x400e0800 ;
EEFC0 = 0x400e0a00 ;
EEFC1 = 0x400e0c00 ;
TICK  = 0xe000e010 ;
_ZN3sys3reg4TICKE = TICK ;
_ZN3sys7CortexM4VTORE = 0xe000ed08 ;
_ZN3sys5Board9STACK_TOPE = STACK_TOP ;
_ZN3sys3reg3WDTE = 0x400e1a50 ;
_ZN3sys3reg3PMCE = PMC ;
_ZN3sys3reg4PIOAE = PIOA ;
_ZN3sys3reg4UARTE = UART ;
_ZN3sys3reg5EEFC0E = EEFC0 ;
_ZN3sys3reg5EEFC1E = EEFC1 ;
_ZN3sys3reg3SCSE = 0xe000e000 ;
_ZN3sys3reg4TRNGE =0x400BC000 ;
_ZN3sys3reg6UOTGHSE = 0x400AC000;
_ZN3sys3reg4PIOBE   = PIOB ;
_ZN3sys3reg4PIOCE   = PIOC ;
_ZN3usb6Device4POOLE = 0x20180000 ;

_ZN3sys3SOC5PIO_AE =0x400e0e00;
_ZN3sys3SOC5PIO_BE =0x400e1000;
_ZN3sys3SOC5PIO_CE =0x400e1200;
_ZN3sys3SOC5PIO_DE =0x400e1400;
_ZN3sys3SOC5PIO_EE =0x400e1600; 
_ZN3sys3SOC5PIO_FE =0x400e1800;

_ZN3sys3reg4EEFC4EFC0E = 0x400e0a00;
_ZN3sys3reg4EEFC4EFC1E = 0x400e0c00;
_ZN3sys3reg6CHIPIDE    = 0x400e0940;

_ZN3sys3reg3ADCE = 0x400C0000;

_ZN3sys3reg4SPI0E = 0x40008000;
_ZN3sys3reg4SPI1E = 0x4000C000; 

_ZN3sys3reg3DMAE  = 0x400c4000;

_ZN3sys3reg3RTCE  = 0x400E1A60;
_ZN3sys3reg3TC0E  = 0x40080000;
_ZN3sys3reg3TC1E  = 0x40084000;

_ZN3sys3reg3RTTE  = 0x400E1A30;
