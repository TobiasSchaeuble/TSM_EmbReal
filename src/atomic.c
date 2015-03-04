/*------------------------
 atomic.c
 (c) H.Buchmann FHNW 2012
 $Id$
--------------------------*/

unsigned val;

int main()
{
 unsigned v=__atomic_add_and_fetch(&val,4,0);
 return 0;
}
  
