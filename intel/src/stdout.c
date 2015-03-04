/*-----------------------
 stdout
 (c) H.Buchmann FHNW 2011
 $Id$
-------------------------*/
#include "stdout.h"
#include "io/ascii.h"
#include "io/screen.h"
Out* stdout;
void stdout_init()
{
 screen_init();
 stdout=Screen;
}
