#pragma once
/*--------------------
 deb(ug)
 (c) H.Buchmann FHNW 2009
 $Id$
----------------------*/
extern void deb_signal0() __attribute__((noreturn)); 
                                    /* writes signal at and returns */
extern void deb_signal1() __attribute__((noreturn)); 
extern void deb_msg(const char*const msg) __attribute__((noreturn));
 /* message msg and halt */
extern void deb_reset() __attribute__((noreturn)); 
extern void deb_out(char ch);
extern void deb_string(const char*const msg);
extern void deb_hex(unsigned val); /* position idependent deb_hex */
                                   /* see hex.S */
extern char deb_in(); /* waits until char read */
extern void deb_newln();

inline void deb_key_val(const char*const key,unsigned val)
{
 deb_string(key);deb_out('\t');deb_hex(val);deb_newln();
}

inline void deb_pointer(const void*const p)
{
 deb_hex((unsigned)p);
}

extern void deb_register();
