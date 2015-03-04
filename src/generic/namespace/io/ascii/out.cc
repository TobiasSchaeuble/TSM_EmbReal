//---------------------------
//out
//(c) H.Buchmann FHSO 2003
//$Id: out.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//---------------------------
IMPLEMENTATION(io_ascii_out,$Revision: 137 $)
#include "io/ascii/out.h"
#define LONG_LONG
//#define IO_ASCII_OUT_TEST
//#include "sys/deb.h"

namespace io
{
 namespace ascii
 {
//------------------------------------------------- Output
  Output::~Output()
  {
  }
  
  void Output::put(const char s[])
  {
   unsigned i=0;
   while(true)
   {
    char ch=s[i++];
    if (ch=='\0') break;
    put(ch);
   }
  }
  
//------------------------------------------------- Entaber
   Entaber::Entaber(Output& layer,unsigned tab)
   :layer(layer),
    tab(tab),
    pos(0),
    blankN(0)
   {
   }
   
   Entaber::~Entaber()
   {
   }
   
   void Entaber::put(char ch)
   {
    if (ch=='\n')
       {
        pos=0;
	blankN=0;
	layer.put('\n');
	return;
       }
    if (ch=='\t')
       {
        layer.put('\t');
	pos=0;
	blankN=0;
	return;
       }   
    if (pos==tab)
       {
        if (blankN>0) layer.put('\t');
	blankN=0;
	pos=0;
       }
    pos++;
    if (ch==' ')
       {
        blankN++;
       }
       else
       {
        while(blankN>0){layer.put(' ');blankN--;}
        blankN=0;
	layer.put(ch);
       }
   }

#ifdef IO_ASCII_OUT_TEST
  class Tester:public Output
  {
   static Tester tester;
   Entaber out;
   void put(char ch) {sys::deb::out(ch);}
   Tester();
  }; 
  
  Tester Tester::tester;
  
  Tester::Tester()
  :out(*this)
  {
  //               0123456701234567012345670123456701234567
  //               |       |       |       |
   sys::deb::out(  "0123456701234567012345670123456701234567\n"
                   "|       |       |       |       |\n");
   out.Output::put("xxxx     Hello\n");
  }
#endif  
 }//namespace ascii
}//namespace io
