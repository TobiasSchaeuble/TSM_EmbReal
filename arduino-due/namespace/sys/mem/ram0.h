#pragma once
INTERFACE(sys_mem_ram0,$Revision: 1.1 $)
//------------------------
//the systems memory dummy 
//(c) H.Buchmann FHSO 2002
//$Id: ram0.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//------------------------
//---------------------------
//global new/delete
//---------------------------
typedef __SIZE_TYPE__ size_t;

extern void* operator new(size_t size);//{return sys::RAM::take(size);}
extern void operator delete(void* mem);//{sys::RAM::free((unsigned char*)mem);}


extern void* operator new[](size_t size);//{return sys::RAM::take(size);}
extern void operator delete[](void* mem);//{sys::RAM::free((unsigned char*)mem);}
