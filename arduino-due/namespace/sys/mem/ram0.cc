//------------------------
//the systems memory dummy 
//(c) H.Buchmann FHSO 2002
//$Id: ram0.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//------------------------
IMPLEMENTATION(sys_mem_ram0,$Revision: 1.1 $)
#include "sys/mem/ram0.h"
#include "sys/deb/deb.h"


void* operator new(size_t size)
{
 sys::deb::out("unexpected  ",__PRETTY_FUNCTION__);
 sys::deb::halt();
 return 0;
}

void operator delete(void* mem)
{
 sys::deb::out("unexpected ",__PRETTY_FUNCTION__);
 sys::deb::halt();
}

void* operator new[](size_t size)
{
 sys::deb::out("unexpected   ",__PRETTY_FUNCTION__);
 sys::deb::halt();
 return 0;
}

void operator delete[](void* mem)
{
 sys::deb::out("unexpected  ",__PRETTY_FUNCTION__);
 sys::deb::halt();
}
