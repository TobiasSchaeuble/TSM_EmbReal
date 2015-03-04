/*-------------------
 pic-devel
 (c) H.Buchmann FHNW 2009
 $Id$
 TODO make io example quite complex control
 TODO make debug press_anykey reset etc.
 see: 8259A PROGRAMMABLE INTERRUPT CONTROLLER
---------------------*/
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/sys.h"
#include "sys/trap.h"
#include "io/kbd.h"
#include "sys/pic.h"

static void tick(unsigned id)             /* the Trap */
{
 ascii_string(Screen,"tick\n");
}

int main()
{
 pic_init();
 pic_install(0,tick);
 sys_sti();                               /* enable */
 while(1)
 {
  kbd_get();
 }
 return 0;
}

