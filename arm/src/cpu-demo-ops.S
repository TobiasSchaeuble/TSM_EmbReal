/*----------------------
  cpu-demo-ops
  (c) H.Buchmann FHNW 2011
  $Id$
  see [ARMABI] literature/IHI0042D_aapcs-2.pdf
------------------------*/

/*assembler format:
  mnem dst,src  mnem: mnemonic 
                data flow right to left
  mnem z,x,y    z<-x mnem y	
  
   important instructions
  
  mov dst,src
  -----------
      reg->reg
       mov reg,reg

      reg->memory
       str reg,[reg)

      memory->reg
       ldr reg,[reg]
 
  res= arg1 op arg2
  ----------------
  op res,arg1,arg2
    		
  calling conventions:
   see [1] Procedure Call Standard for the ARM Architecture
	   THE BASE PROCEDURE CALL STANDARD 
	   Table 2
   use 
     objdump -d file 
   for disassembly
 	
*/

/*
TODO 
  - multiplication division 	
  - void op(unsigned x,unsigned y,unsigned* res);
*/

/*--------------------------------- 
  unsigned op(unsigned x,unsigned y)
  x:r0
  y:r1
  return r0<-r0 op r1
-----------------------------------*/  
.global op
op:/* your work */
	mov pc,lr


/*--------------------------------- 
  void copy(unsigned* dst,unsigned* src)
  dst:r0  
  src:r1
  register r2 used as scratch

         unsigned 
	 +---------+
  r0---->|         |
         +---------+

         unsigned 
	 +---------+
  r1---->|         |
         +---------+
  	 
-----------------------------------*/  
.global copy
copy:	/* your work */
 
 

/*--------------------------------- 
  void swap(unsigned* x,unsigned* x)
  x:r0  
  y:r1
  register r2/r3 used as scratch

         unsigned 
	 +---------+
  r0---->|         |
         +---------+

         unsigned 
	 +---------+
  r1---->|         |
         +---------+
*/
.global swap
swap:/* your work */
 
 
 
 
