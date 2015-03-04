/*------------------------
 pointer
 (c) H.Buchmann FHNW 2011
 before running this program think about the output
--------------------------*/
#include <stdio.h>

unsigned val=7;
unsigned* valP=&val;
/*
     unsigned
     +----------+
val  |         7|<----+
     +----------+     |
                      |
      unsigned*       |
     +----------+     |
valP |          |-----+
     +----------+
*/

int main(int argc,char** args)
{
 *valP=8;               /* access to val via valP */
 printf("  val=%d\n"
        " &val=%p\n"
        " valP=%p\n"
	"&valP=%p\n",  val          /* value of val */
	            , &val        /* address of val */
		    , valP         /* value of valP */
		    ,&valP);	 /* address of valP */
 return 0;
}
