//-----------------------
//sysdebug 
//should be implemented in 'board/sys'
//(c) H.Buchmann FHSO 2001
//$Id: deb.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//-----------------------
//not a normal module INTERFACE/IMPLEMENTATION
#include "sys/deb/deb.h"
namespace sys
{
 namespace deb
 {
#ifdef SYS_DEB_DEBUGGER
  bool Debug=false;
  Debugger* debugger=0;
#endif
 
  void pressAnyKey(const char msg[])
  {
   out(msg);out("\npress any key...\n");
   get();
  }
  
  void waitForKey(char ch)
  {
   out("press key '");out(ch);out("' ...\n\r");
   while(true)
   {
    if (get()==ch) break;
   }
  }
  
  void out(const char s[])
  {
   if (s==0) {out("(null)");return;}
   unsigned i=0;
   for(;;)
   {
    char ch=s[i++];
    if (ch=='\0') break;
    out(ch);
   }
  }

  void out(unsigned val)
  {
   static const char Digits[]="0123456789";
   char nbr[25]; //enough for 64 bit unsigned
   char* s=nbr; 
   do
   {
    *s++=Digits[val%10];
    val/=10;
   } while(val);
   do out(*--s); while(s!=nbr);
  }

  void out(int val)
  {
   if (val<0){out('-');out((unsigned)-val);}
	else {out((unsigned)val);}
  }

#ifdef __x86_64
  void out(const void* val)
  {           //    0x0123456789abcdef 
   if (val==0)
      {
          //0x0123456789abcdef
       out("      (null)      ");
      }
      else 
      {
       out('0');out('x');hex((long long unsigned)val);
      }
  }
#else
  void out(const void* val)
  {           //    0x01234567 
   if (val==0)
      {
       out("  (null)  ");
      }
      else 
      {
       out('0');out('x');hex((unsigned)val);
      }
  }
#endif
  
  void out(const char key[],unsigned val)
  {
   out(key);out(' ');out(val);newln();
  }

  void out(const char key[],const void* val)
  {
   out(key);out(' ');out(val);newln();
  }

  void out(const char key[],const unsigned val[],unsigned len)
  {
   out(key);out(' ');
   for(unsigned i=0;i<len;i++)
   {
    if (i>0) out('\t');
    out(val[i]);
   }
   newln();
  }

  void out(const char key[],const char val[]) 
  {
   out(key);
   out(' ');
   out(val);
   newln();
  }
  
  void newln()
  {
   out("\n\r");
  }


  template<typename T>
  static void hexT(T v)
  {
   static const char Digits[]="0123456789abcdef";
   unsigned shift=8*sizeof(T);
   do
   {
    shift-=4;
    out(Digits[(v>>shift)&0xf]);
   }while(shift>0);
  }
  
  void hex(unsigned char val)
  {
   hexT(val);
  }
 
  void hex(unsigned short val)
  {
   hexT(val);
  }
   
  void hex(unsigned val)
  {
   hexT(val);
  }

  void hex(long long unsigned val)
  {
   hexT(val);
  }
  
  void hex(const char key[],unsigned val)
  {
   out(key);hex(val);newln();
  }

  void hex(const char key[],unsigned* val,unsigned len)
  {
   out(key);
   for(unsigned i=0;i<len;i++)
   {
    if (i>0) out(' ');
    hex(val[i]);
   }
   newln();
  }
  
  void dump(const unsigned char data[],unsigned len)
  {
   static const unsigned PER_LINE = 16;
   unsigned perLine=0;
   for(unsigned i=0;i<len;i++)
   {
    if (perLine==0)
       {
        newln();perLine=PER_LINE;
       }
       else out(' ');
    hex((unsigned char)data[i]);
    perLine--;    
   }
   newln();
  }

  void dump(const char s[],unsigned len)
  {
   for(unsigned i=0;i<len;i++) out(s[i]);
  }
 } 
}
