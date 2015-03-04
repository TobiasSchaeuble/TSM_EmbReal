/*-----------------
 kbc keyboard controller
 (c) H.Buchmann FHNW 2009
 $Id$
 TODO not yet in final form 
-------------------*/
#include "sys/kbc.h"
#include "sys/sys.h"
#include "sys/pic.h"
#include "sys/screen.h"
#include "io/ascii.h"

static unsigned initalized=0;
static kbc_Listener     li=0;

static void trap(unsigned id)
{
 
}

void kbc_init()
{
 if (initalized) return;
 pic_init();
// pic_install(1,trap);
 pic_enable(1);
 initalized=1;
}

void setListener(kbc_Listener li)
{
}

