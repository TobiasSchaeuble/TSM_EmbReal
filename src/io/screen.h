#pragma once
/*------------------------
 screen the basic output
 (c) H.Buchmann FHNW 2009
 $Id$
--------------------------*/
#include "io/ascii.h"
extern Out* Screen;
void screen_init();  /* TODO init by call back:sys_install() */
/*TODO some shortcuts sys_ascii_xxx() */

