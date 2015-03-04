/*--------------------
 deb(ug)
 (c) H.Buchmann FHNW 2011
 $Id$
 see [RealViewEmulationBaseboard] [UART]
 compile with at least O2
----------------------*/
#include "sys/deb.h"
static const char*const RegisterNames[]=
{
"r0", "r1", "r2", "r3",
"r4", "r5", "r6", "r7",
"r8", "r9", "r10","r11",
"r12",
"sp",
"lr",
"pc"
};

typedef struct 
{
  unsigned reg[16];
}Register;


void deb_showregister(Register*r)
{
// deb_key_val("r",(unsigned)r);
#if 1
 for(unsigned i=0;i<16;++i)
 {
  deb_key_val(RegisterNames[i],r->reg[i]);
 }
#endif
}

#if 0
void deb_register()
{
 Register r;
 deb_register0(&r);
 for(unsigned i=0;i<16;++i)
 {
  deb_key_val(RegisterNames[i],r.reg[i]);
 }
}
#endif
 
extern volatile struct 
{
 unsigned DR;                         /*Data register */ 
 unsigned SR;                       /* Receive status */
 unsigned res[4];                         /* reserved */
 unsigned FR;                                 /* Flag */  
} UART0;                                /* see ram.ld */

void deb_out(char ch)
{
 while(UART0.FR&(1<<3)){} /* wait until busys cleared */
 UART0.DR=ch;
}

char deb_in()
{
 while(UART0.FR&(1<<4)){}
 return UART0.DR;
}

static void deb_out_string(const char*const s)
{
 for(unsigned i=0;s[i];++i)deb_out(s[i]);
}

void deb_string(const char*const msg)
{
 deb_out_string(msg);
}

void deb_msg(const char*const msg)
{
 deb_out_string(msg);
 while(1){} /* wait */
}

static volatile unsigned* CM_CTRL=(unsigned*)0x1000000c;
 /* only known in this file */

void deb_reset()
{
 *CM_CTRL|=(1<<3);                /* reset */
 while(1){}            /* for the compiler */
}

void deb_signal0()
{
 deb_out_string("\n\nSignal0\n");
 deb_reset();
}
void deb_signal1()
{
 deb_out_string("\n\nSignal1\n");
 deb_reset();
}

void deb_hex(unsigned val)
{
 unsigned bit=8*sizeof(val);
 while(bit>0)
 {
  bit-=4;
  unsigned nibble=0xf&(val>>bit);
  deb_out((nibble<10)?'0'+nibble:'a'+(nibble-10));
 }
}

void deb_newln()
{
 deb_out('\n');
}
