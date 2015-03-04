/*-------------------
 calling an Image
 (c) H.Buchmann FHNW 2009
 $Id$
---------------------*/
typedef void (*Start)();
extern Start start;

void callIt()
{
 start();
}  
