//--------------------------
//sys
//(c) H.Buchmann FHSO 2003
//$Id: sys.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//not yet in final form
// detection of circular import done
// but only rudimentary display of circular import 
//--------------------------
//IMPLEMENTATION(sys_sys,$Revision$)
#include "sys/sys.h"
#include "sys/deb/deb.h"

//#define SYS_SYS_DEBUG
//see Makefile/project xml file
//#define SYS_SYS_SHOW_STARTUP

//#include <cstdio>
//#include <cstdlib>
#ifndef EARLY_INIT
//(<-------------  
namespace sys
{
 extern "C" Mod::Global __GLOBAL__CONSTRUCTORS[];
 extern "C" Mod::Global __GLOBAL__DESTRUCTORS[];
 extern "C" Mod 	__MODULES_BEG[];
 extern "C" Mod 	__MODULES_END[];
 extern "C" Inc	 	__INCLUDES_BEG[];
 extern "C" Inc	 	__INCLUDES_END[];
 
 extern "C" 
 {
#if 0
  int __cxa_atexit(void (*f)(void*),void*p,void* d)
  {
   fprintf(stderr,"%s f=%p p=%p d=%p\n",__PRETTY_FUNCTION__,f,p,d);
   return 0;
  }
#endif
 }
 
 
//--------------------------------
//see -funit-at-a-time
 static const unsigned L0=0;
 static const unsigned L1=1;
 
 const char*const Mod::ErrorCodeText[]=
 {
  "OK","CONSTRUCTOR","DESTRUCTOR","CIRCULAR"
 };
 
 bool                Mod::started=false;
 Mod::ErrorCode      Mod::errorCode=Mod::OK;
 unsigned            Mod::prefixSize=0;
// unsigned            Mod::modN=0;
 
 unsigned Mod::index()const
 {
  return this-__MODULES_BEG;
 }
 
 void Mod::Mod2::init(Mod2 mod2[])
 {
  Mod2* m2=mod2;
  for(Mod* mod=__MODULES_BEG;mod<__MODULES_END;++mod)
  {
   m2->m=mod;
   m2->inc=0;
   m2->incN=0;
   m2->ctor=0;
   m2->dtor=0;
   m2->visited=false;
   m2->onStack=false;
   ++m2;
  }
 }
 
 void Mod::Mod2::include(Mod2 nd[])
 {
  const Mod*  m0=0;
        Mod2* nd0=0;
  
  for(Inc* i=__INCLUDES_BEG;i<__INCLUDES_END;++i)
  {
   const Mod*const mod=  i->mod;
   if (m0!=mod)
      {
       nd0=nd+mod->index();
       nd0->incN=0;
       nd0->inc=i;
       m0=mod;
      }
   ++nd0->incN;
  }
 }
 
#ifdef SYS_SYS_DEBUG
 void Mod::Mod2::showInclude() const
 {
  deb::out(m->getName());
  deb::newln();
  for(unsigned i=0;i<incN;++i)
  {
   const Mod*const mod=*(inc+i)->inc;
   deb::out("\t");
   deb::out(mod->getName());
   deb::newln();
  }
 }
 
 void Mod::Mod2::show() const
 {
  deb::out((void*)m->text);deb::out('\t');
  deb::out((void*)ctor);deb::out('\t');
  deb::out((void*)dtor);deb::out('\t');
  deb::out(m->getName());
  deb::newln();
 }
#endif

 unsigned Mod::Mod2::sort(unsigned idx,Mod2 mod2[],Mod2* sorted[])
 {
  if (onStack)
     {
      deb::out("circular import ");
      deb::out(m->getName());
      deb::halt();
     }
  if (visited) return idx;
  visited=true;
  onStack=true;
  for(unsigned i=0;i<incN;++i)
  {
   const Mod*m=*(inc[i].inc);
   if (m==this->m) continue;
   Mod2* m2=mod2+m->index();
   idx=m2->sort(idx,mod2,sorted);
  }
  sorted[idx++]=this;
  onStack=false;
  return idx;
 }
 
#if (__GNU_MAJOR__==3) && (__GNUC_MINOR__<4)
#error wrong compiler version revisit code 
#endif

 void Mod::mkPrefix()
 {
  const char* prefix=__MODULES_BEG[0].name;
  while(prefix[prefixSize])++prefixSize;
  for(Mod* m=__MODULES_BEG;m<__MODULES_END;++m)
  {
   unsigned i=0; //index in prefix, m->name
   while(true)
   {
    char ch0=prefix[i];
    char ch1=m->name[i];
    if (ch0!=ch1) 
       {
        if (i<prefixSize) prefixSize=i;
	break;
       }
    if (ch0=='\0') 
       {
        break;
       }
    ++i;
   }
  }
 }

 void Mod::matchGlobals(Mod2 mod[],unsigned len)
 {
  Mod2* m0=mod; //using Mod2& m0=mod[0] probably  generates bad code
  Global* ctors=__GLOBAL__CONSTRUCTORS;
  Global* dtors=__GLOBAL__DESTRUCTORS;  
  for(unsigned i=1;i<len;++i)
  {//m0<ctor m0<dtor
   Mod2* m1=mod+i; //using Mod2& m1=mod[i]  probably  generates bad code
   if ((*ctors) && (*ctors<m1->m->text))
      {
       m0->ctor=*ctors;
       ++ctors;
      }
   if ((*dtors) &&(*dtors<m1->m->text))
      {
       m0->dtor=*dtors;
       ++dtors;
      }
   m0=m1;
  }
  m0->ctor=*ctors; //probably 0
  m0->dtor=*dtors;
 }


 void Mod::sortModules(Mod2 m2[],Mod2* sorted[],unsigned len)
 {

#ifdef SYS_SYS_DEBUG
  deb::out("----------------------------------------- Sorting\n\r");
#endif
  unsigned idx=0;
  for(unsigned i=0;i<len;++i)
  {
   idx=m2[i].sort(idx,m2,sorted);  
  }
 }

 void Mod::thumbStart()
 {
  Global* c=__GLOBAL__CONSTRUCTORS;
  while(c)
  {
   (*c++)();
  }
 }
 
#ifdef SYS_SYS_DEBUG
 void Mod::align(unsigned size,const char*const s,const char*const next)
 {
  unsigned pos=0;
  for(unsigned i=0;s[i];++i){deb::out(s[i]);++pos;}
  while(pos++<size) deb::out(' ');
  if (next) deb::out(next);
 }
  
 void Mod::showInclude(const Mod2 nd[],unsigned len)
 {
  deb::out("----------------------------------------- Include List\n\r");
  for(unsigned i=0;i<len;++i)
  {
   nd[i].showInclude();
  }
 }

 void Mod::showStartup(const Mod2*const sorted[],unsigned len)
 {
  for(unsigned i=0;i<len;++i)
  {
   const Mod2* m2=sorted[i];
   if (m2->ctor) 
      {
       deb::out(m2->getName());
       deb::newln();
      }
  }
 }
 
 void Mod::showModules(const Mod2 nd[],unsigned len)
 {
  deb::out("----------------- Module List\n\r");
  static const unsigned Field=2+2*sizeof(void*);
                         //  0x 
  align(Field,"start","\t");
  align(Field,"ctor","\t");
  align(Field,"dtor","\tName\n\r");
  for(unsigned i=0;i<len;++i)
  {
   nd[i].show();
  }
 }

 void Mod::showGlobal()
 {
  deb::hex("----------------------------- __GLOBAL__CONSTRUCTORS",
            __GLOBAL__CONSTRUCTORS);
  Global* g=__GLOBAL__CONSTRUCTORS;
  while(*g)
  {
   deb::out("",(void*)*g);
   g++;
  }

  deb::out("----------------------------- __GLOBAL__DESTRUCTORS",
           __GLOBAL__DESTRUCTORS);
  Global* d=__GLOBAL__DESTRUCTORS;
  while(*d)
  {
   deb::out("",(void*)*d);
   d++;
  }
 }
#endif

 Mod::ErrorCode Mod::getErrorCode(){return errorCode;}
 
 const char* Mod::getErrorCodeText(){return ErrorCodeText[errorCode];}


 void Mod::call(Mod2* sorted[],unsigned len)
 {
  unsigned i=0;
  while(i<len)
  {
   Mod2* m=sorted[i++];
   if (m->ctor) 
      {
#ifdef  SYS_SYS_SHOW_STARTUP
	deb::out("ctor: --------------------------- ");
	deb::out(m->getName());
	deb::newln();
#endif     
       m->ctor();
      }
  }
  
  while(i>0)
  {
   Mod2* m=sorted[--i];
   if (m->dtor) 
      {
#ifdef  SYS_SYS_SHOW_STARTUP
	deb::out("dtor: --------------------------- ");
	deb::out(m->getName());
	deb::newln();
#endif     
       m->dtor();
      }
  }
 }
 
 void Mod::start()
 {
  if (started)
     {
      deb::out("**** already started\n\r");
      return;
     }

  started=true;
  
  mkPrefix();

  const unsigned modN=__MODULES_END-__MODULES_BEG;
  Mod2 mod2[modN]; // on stack
  
  
  Mod2::init(mod2);

  Mod2::include(mod2);
  
  
//  showInclude(mod2,modN);
 
  matchGlobals(mod2,modN);
//  showModules(mod2,modN);

  Mod2* sorted[modN];
  sortModules(mod2,sorted,modN);
//  showStartup(sorted,modN);
  call(sorted,modN);
 }
 
 void Mod::stop() 
 {
//only dummy
 }
 
 void Mod::enumerate(const Listener& li)
 {
#if 0
  for(Mod** m=__MODULES_BEG;m<__MODULES_END;++m)
  {
   li.onModule(*m,(*m)->inc,(*m)->incSize);
  }
#endif
 }
}
//) <-----------------------
#else
//EARLY_INIT
extern const sys::Mod::Entry __InitSequence[];
extern "C" sys::Mod::Global __GLOBAL__CONSTRUCTORS[];
namespace sys
{
 void Mod::start()
 {
  unsigned i=0;
  while(true)
  {
   const Mod::Entry& e=__InitSequence[i++];
   if (e.name==0) break;
   Global g=__GLOBAL__CONSTRUCTORS[e.index];
#ifdef SYS_SYS_SHOW_STARTUP   
   deb::out((void*)g);deb::out("\t");
   deb::out(e.index);deb::out("\t");deb::out(e.name);
   deb::newln();
#endif   
   g();
  }
 }
 
 void Mod::stop()
 {
 }
}//namespace sys
#endif
extern "C" const unsigned  __BUILD_ID[];
namespace sys
{
 const BuildID& buildId()
 {
  static const BuildID Id={(char*)(__BUILD_ID+3), //name
                             __BUILD_ID[2], //type
			     __BUILD_ID[1], //idSize
	     (unsigned char*)(__BUILD_ID+3)+__BUILD_ID[0]
		     };      
  return Id;
 }
 
}
