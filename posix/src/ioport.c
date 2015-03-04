/*--------------------------
  ioport
  (c) H.Buchmann FHNW 2012
  $Id$
----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>

static int error(int cod,const char* msg)
{
 if (cod<0)
    {
     perror(msg);
     exit(1);
    }
 return cod;
}

int main(int argc,char** args)
{
 error(ioperm(0x70,2,1),"ioperm");
 outb(0,0x70); /* value port */
 printf("0x70=%x\n",inb(0x71));
 return 0;
}
  
