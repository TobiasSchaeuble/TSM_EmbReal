#pragma once
/*-------------------
 sys 
 (c) H.Buchmann FHNW 2009
 $Id$
 for understanding asm volatile use -std=gnu99
---------------------*/
/*all inline volatile keyword important */
static inline unsigned char sys_inb(unsigned short port)
{
 unsigned char v;
 asm volatile(
  "#------------- inb\n\t"
//  "inb %w1"
  "inb %[port]"         /* works too */
  :[v] "=a" (v)
  :[port]"Nd" (port)
 );
 return v;
}

/* TODO robust programming 
        sys_outb(value,port) ok
	sys_outb(port,value) ok too but semantically wrong */
static inline void sys_outb(unsigned char v,
                            unsigned short port)
{
 asm volatile
 (
  "#------------- outb\n\t"
  "outb %w1"
  :
  :[v] "a" (v)
  ,[port]"Nd" (port)
 );
}
/*TODO inb/outb for unsigned short fastcall: parameter in ecx*/
typedef long long unsigned MSR;
__attribute__((fastcall)) static inline MSR sys_read_msr(unsigned id)
{
 unsigned lo;
 unsigned hi;
 asm volatile
 (
  "#------------------ sys_read_msr\n\t"
  "rdmsr\n"
  :[lo] "=a" (lo)   /* output */
  ,[hi] "=d" (hi)
  :[id]"c" (id)     /* input */
 );
 return (MSR)lo|(MSR)hi<<32;
}

static inline unsigned sys_getFlags()
{
 unsigned f;
 asm volatile
 (
  "#------------------getFlags\n\t"
  "pushf\n\t"
  "pop %[f]\n\t"
  :[f] "=a" (f)   /* output */
  :
 );
 return f;
}

static inline void sys_sti()
{
 asm volatile
 (
  "#------------------sti\n\t"
  "sti\n\t"
  : /* output */
  : /* input  */
 );
}

static inline void sys_cli()
{
 asm volatile
 (
  "#------------------cli\n\t"
  "cli\n\t"
  : /* output */
  : /* input  */
 );
}

__attribute__((fastcall)) static inline void sys_wait(unsigned cnt)
{
 if (cnt==0) return;
 /* cnt>0 */
 asm volatile
 (
  "#------------------sys_wait\n\t"
  "0:	sub $1,%[cnt]\n"
  "	jne 0b\n"
  :[cnt] "+r" (cnt)
  :/* input  */
 );
}
