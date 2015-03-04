/*-----------------------
  mmu 
   - a pointer exercise 
   - a bit ops exercise
  (c) H.Buchmann FHNW 2013
 ------------------------*/
#define TRANSLATION_TABLE_BASE 0x0;
/*----------------------------------------- 
the bits of v-addr   
  +------+--------+--------+---------------+ 
  | k0   |   k1   |   k2   |   k3          |
  +------+--------+--------+---------------+ 
     4   |    9   |    9   |    10         |  n_i
       28|      19|      10|              0|  shift_i
      0xf|   0x1ff|   0x1ff|           0x3f|  mask_i   	    


--------------------------------------------*/ 



typedef unsigned* P_ADDR;
typedef P_ADDR    LEVEL2;
typedef LEVEL2*   LEVEL1;
typedef LEVEL1*   LEVEL0;

LEVEL0* root=(LEVEL0*)TRANSLATION_TABLE_BASE;

P_ADDR p_addrA(unsigned v_addr) /* step by step */
{
 unsigned k0=0x00f&(v_addr>>28);
 unsigned k1=0x1ff&(v_addr>>19);
 unsigned k2=0x1ff&(v_addr>>10);
 unsigned k3=0x03f&(v_addr>> 0);
 LEVEL0* l0;
 LEVEL1* l1=l0[k0];
 LEVEL2* l2=l1[k1];
 return l2[k2]+k3;
}

P_ADDR p_addrB(unsigned v_addr)  /* all in one */
{
 /* your work */
}

