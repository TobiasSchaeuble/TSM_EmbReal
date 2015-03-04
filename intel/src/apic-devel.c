/*-------------------
 apic-devel
 (c) H.Buchmann FHNW 2009
 $Id$
---------------------*/
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/sys.h"
#include "io/kbd.h"
#include "sys/trap.h"
#include "sys/pic.h"

typedef unsigned Entry[4];

volatile Entry* APIC_BASE=0;

void tick()
{
 ascii_printf(Screen,"tick\n");
 APIC_BASE[0xb][0]=0;
}

int main()
{
 pic_init(); 
 
 trap_install(0x20,tick);
 MSR msr=sys_read_msr(0x1b);
 unsigned flags=sys_getFlags();
 APIC_BASE=(Entry*)(msr&~((1<<12)-1));
 APIC_BASE[0x0f][0]|=(1<<8); /* enable */
 APIC_BASE[0x38][0]=0x80000000;
 APIC_BASE[0x32][0]=(0x20 |
                   (1<<17)); 

 sys_sti();
 while(1)
 {
  ascii_printf(Screen,"         EFLAGS=%x\n"
                      "      MSR[0x1b]=%x\n"
                      " VERSION[0x030]=%x\n"
                      "      ID[0x020]=%x\n"
                      "Spurious[0x0f0]=%x\n"
		      "   Timer[0x320]=%x\n"
		      "    LVT0[0x350]=%x\n"
		      "    LVT1[0x360]=%x\n"
		      "  LVTERR[0x370]=%x\n"
		      "  T_INIT[0x380]=%x\n"
		      "   T_CUR[0x390]=%x\n"
		      "   T_CFG[0x3e0]=%x\n"
		      "     ESR[0x280]=%x\n"
		      "\n",
		      flags,
		      (unsigned)msr,
		      APIC_BASE[0x03][0],
		      APIC_BASE[0x02][0],
		      APIC_BASE[0x0f][0],
		      
		      APIC_BASE[0x32][0],
		      APIC_BASE[0x35][0],
		      APIC_BASE[0x36][0],
		      APIC_BASE[0x37][0],
		      
		      APIC_BASE[0x38][0],
		      APIC_BASE[0x39][0],
		      APIC_BASE[0x3e][0],
		      APIC_BASE[0x28][0]
		      );
  
  if (kbd_get()=='r') 
     {
      APIC_BASE[0x38][0]=0x10000000;
     }
 }
 return 0;
} 
