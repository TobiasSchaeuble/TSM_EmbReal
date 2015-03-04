/*--------------------
 deb(ug)
 (c) H.Buchmann FHNW 2009
 $Id$
----------------------*/
#include "sys/deb.h"

static volatile unsigned short* Video=
 (volatile unsigned short*)(0xb8000);

static const char Signal[]="Signal0";

void deb_signal0()
{
// sys_cli();
 for(unsigned i=0;Signal[i];++i)
 {
  Video[i]=Signal[i]|(0xc0<<8);
 }
 while(1){}
}

