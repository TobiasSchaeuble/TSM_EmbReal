#pragma once
/*----------------------------
  mmu.h
  (c) H.Buchmann FHNW 2012
  $Id$
------------------------------*/
#if __ASSEMBLER__ == 1
.global mmu_enable
#else

typedef struct
{
 unsigned v_mem;   /* MByte aligned */
 unsigned p_mem;   /* MByte aligned */
 unsigned sizeMB;  /* in MBytes */ 
 unsigned flags;   
} MMU_Desc; /* sizeMB== 0 terminates list */

extern volatile unsigned* mmu_init(unsigned disp); /* disp=p-mem-v-mem */
 /* returns p-addr of ttb */
extern void* mmu_pAddr(void* vAddr);		                       
#endif
