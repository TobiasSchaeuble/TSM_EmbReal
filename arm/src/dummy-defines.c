/*-----------------------
 dummy-undefines
 (c) H.Buchmann FHNW 2011
 $Id$
 hack for u-boot
 ------------------------*/
unsigned __exidx_start=0;
unsigned __exidx_end  =0;
void abort()
{
 while(1){}
}
