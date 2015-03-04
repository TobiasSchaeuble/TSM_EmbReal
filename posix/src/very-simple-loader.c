/*---------------------
 very simple loader
 (c) H.Buchmann FHNW 2009
 $Id$
 calling
 very-simple-loader program-name parameters
-----------------------*/
#include <stdio.h>
#include <unistd.h>

int main(int argc,char** args)
{
 if (argc<2)
    {
     printf("usage: %s program-name parameters\n",args[0]);
     return 1;
    }
 int res=execv(args[1],args+1); 
 if (res<0)
    {
     perror("execv");
    }
 return 0;
}
 
