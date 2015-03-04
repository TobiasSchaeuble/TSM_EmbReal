/*--------------------
 minimal-1
 (c) H.Buchmann FHNW 2011
 $Id:$
----------------------*/
#include <unistd.h>

int main(int argc,char** args)
{
 static const char MSG[]="Hello World\n";
 write(STDOUT_FILENO,MSG,sizeof(MSG)); /* an elementary system call */
 while(1){}
}
  
