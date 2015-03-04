/*
---------------------------
layout no memory map
(c) H.Buchmann FHNW 2014
see: superfluous/eo3s/soc/AT91SAM/3X/doc/at91sam3x.pdf
     22.5
---------------------------
*/

SECTIONS
{
/*---------------------------------------- text */ 
 .text 0x0 : {
	 }


/*---------------------------------------- data */ 
. = ALIGN(4);
 .data : { 
         }

/*---------------------------------------- bss */ 
 .bss : {
 	}

STACK_TOP=0x20080000;

/DISCARD/ : {
  *(.v4_bx)
  *(.vfp11_veneer)
}

}
