//---------------------------
//write
//(c) H.Buchmann FHSO 2003
//$Id: write.cc 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//---------------------------
IMPLEMENTATION(io_ascii_write,$Revision: 189 $)
//#define IO_ASCII_WRITE_TEST
#include "io/ascii/write.h"
#define LONG_LONG
//--------------- set or unset NO_LONG_DIV with -D
#ifdef NO_LONG_DIV
#undef LONG_LONG
#define NO_DOUBLE_CONVERSION
#warning no NO_LONG_DIV available
#endif


#include "sys/deb/deb.h"

namespace io
{
 namespace ascii
 {
//------------------------------------------------- Writer
                             // 0123456789abcdef 
  const char Writer::Digits_[]="fedcba9876543210123456789abcdef";
                             //                ^
			     //                |---- entry
			     //see val%10 and val/10 if val<0
  const char*const Writer::Digits=Digits_+15;			      
  const char Writer::Fill=' ';

//------------------------------------------------- StringFormatter
  const char* Writer::LeftAlign::put(const char s[]) const
  {
   return wr.putX_(s);
  }

  const char* Writer::LeftAlign::put(const char s[],unsigned len) const
  {
   return wr.putX_(s,len);
  }

  const char* Writer::RightAlign::put(const char s[]) const
  {
   return wr.put_X(s);
  }

  const char* Writer::RightAlign::put(const char s[],unsigned len) const
  {
   return wr.put_X(s,len);
  }
  
//------------------------------------------------- Dec.Formatter
  template<typename typ>Writer& Writer::Dec::putU(typ val) const
  {
   //strln(s) =round(8*sizeof(typ)*log(2)+1) 
   //        ~ (8*sizeof(typ)*3)/10+1
   //          
   char s[(8*sizeof(typ)*3)/10+2];
   unsigned l=0;
   do
   {
    s[l++]=Digits[val%10];
    val/=10;
   }while(val);
   return wr.putReverse(s,l);
  }

  template<typename typ>Writer& Writer::Dec::putS(typ val) const
  {
   char s[(8*sizeof(typ)*3)/10+4]; //plus sign -/+
   bool neg=val<0;
   unsigned l=0;
   do
   {
    s[l++]=Digits[val%10];
    val/=10;
   }while(val);
   if (neg) s[l++]='-';
   return wr.putReverse(s,l);
  }
  
  Writer& Writer::Dec::put(unsigned char val) const
  {
   return putU<unsigned>((unsigned)val);
  }
  
  Writer& Writer::Dec::put(unsigned val) const
  {
   return putU<unsigned>(val);
  }

  Writer& Writer::Dec::put(unsigned short val) const
  {
   return putU<unsigned short>(val);
  }

  Writer& Writer::Dec::put(unsigned long long val) const
  {
#ifdef LONG_LONG  
   return putU<unsigned long long>(val);
#else
#warning NO_LONG_DIV defined
   return wr.putReverse("gnol gnol",9);  //long long
#endif
   
  }
  
  Writer& Writer::Dec::put(int val) const
  {
   return putS<int>(val);
  }
  
  Writer& Writer::Dec::put(int long long val) const
  {
#ifdef LONG_LONG
   return putS<int long long>(val);
#else
#warning NO_LONG_DIV defined
   return wr.putReverse("gnol gnol",9);  //long long
#endif   
  }
  
//------------------------------------------------- Hex.Formatter
  template<typename typ>
  unsigned Writer::Hex::put(char s[],typ val) const
  {
   unsigned l=0;
   typ mask=1;
   while(mask)
   {
    s[l++]=Digits[val&0xf];
    val>>=4;
    mask<<=4;
   }
   return l;
  }
  
  template<typename typ>
  Writer& Writer::Hex::put(typ val) const
  {
   char s[2*sizeof(typ)+4];
        //^             ^--- 0x + spare ev terminating zer
	//|------------------ 2 nibbles per byte
   unsigned l=put<typ>(s,val);
   s[l++]='x';s[l++]='0';
   return wr.putReverse(s,l);
  }
 
  unsigned Writer::Hex::put(char s[],unsigned short val) const
  {
   return put<unsigned short>(s,val);
  }
   
  unsigned Writer::Hex::put(char s[],unsigned val) const
  {
   return put<unsigned>(s,val);
  }

  Writer& Writer::Hex::put(unsigned char val) const
  {
   return put<unsigned char>(val);
  }
    
  Writer& Writer::Hex::put(unsigned val) const
  {
   return put<unsigned>(val);
  }

  Writer& Writer::Hex::put(unsigned short val) const
  {
   return put<unsigned short>(val);
  }

  Writer& Writer::Hex::put(unsigned long long val) const
  {
   return put<unsigned long long>(val);
  }
  
//------------------------------------------------- Default
  void Writer::DefaultEoL::onEoL(Output&)
  {
  }  

#ifndef NO_FLOATS
//------------------------------------------------- Double
  Writer::Double::Double(Writer& out,double val,unsigned sig)
  :util::Double::Format(val,sig)
  ,out(out)
  {
   sciLen=isNeg()+sig+1+1+1+3;  //[s]d.ddddesddd
		//    | | | |---------- exponent digits
		//    | | |------------ sign of exponent
		//    | |-------------- e for exponent
		//    |---------------- decimal point
   //select fixForm
   int msd=getMSD();
   if (msd<0)
      { //0.0ddddd
        //   |------msd
       fixForm=&Writer::Double::fix_0_d;
       fixLen=isNeg()+1-msd+(int)sig;
       return;
      }
   if (msd<(int)sig)  
      {
       fixForm=&Writer::Double::fix_d_d;
       fixLen=isNeg()+1+sig;
       return;
      } 
   //dddd000000
   fixForm=&Writer::Double::fix_d_0; 
   fixLen=isNeg()+msd+1;  
  }
  
  Writer& Writer::Double::put(const char s[],unsigned len)
  {
  //prefix alread done
   if (out.width==0) 
      {
       for(unsigned i=0;i<len;++i) out.putChar(s[i]);
      }
      else
      {
       for(unsigned i=0;out.width>0;i++) out.putChar(s[i]);
      }
   return out;
  }
    
  void Writer::Double::prefix(unsigned len)
  {
   out.fillLeft(len);
   if (isNeg()) out.putChar('-');
  }
  
  Writer& Writer::Double::fix_d_d()
  {
   //d.dddd
   fixPrefix();
   char s[fixLen];
   unsigned si=0;
   
   const char*const d=getDig(); 
   int msd=getMSD();
   for(int i=0;i<getSig();++i)
   {
    s[si++]=d[i];
    if (msd--==0) s[si++]='.';
   }
   return put(s,si);
  }

  Writer& Writer::Double::fix_0_d()
  {
   fixPrefix();
   char s[fixLen];
   unsigned si=0; 
   //0.000dddd
   s[si++]='0';
   s[si++]='.';
   int msd=getMSD();
   while(++msd<0) s[si++]='0';
   const char*const d=getDig();
   for(int i=0;i<getSig();++i) s[si++]=d[i];
   return put(s,si);
  }


  Writer& Writer::Double::fix_d_0()
  {
   //ddddd0000
   fixPrefix();
   char s[fixLen];
   unsigned si=0;
   const char*const d=getDig();
   for(int i=0;i<getSig();++i) s[si++]=d[i];
   int msd=getMSD()-getSig();
   while(msd-->=0) s[si++]='0';
//ignore width
   for(unsigned i=0;i<si;++i) out.putChar(s[i]);
   return out;
  }

  Writer& Writer::Double::fix()
  {
   if (fixLen>sciLen) return sci();
   (this->*fixForm)();
   return out;
  }
 

  Writer& Writer::Double::sci()
  {
   prefix(sciLen);
   const char*const d=getDig();
   int i=0;         //index in d
   out.putChar(d[i++]);
   out.putChar('.');
   for(;i<getSig();++i) out.putChar(d[i]);
   int exp=getMSD();
   out.putChar('e');
   if (exp<0)
      {
       out.putChar('-');
       exp=-exp;
      }
      else
      {
       out.putChar('+');
      }
   {
    char s[]="000";
    unsigned i=0;
    while(exp>0)
    {
     s[i++]=Digits[exp%10];
     exp/=10;
    }
    i=3;
    while(i>0) out.putChar(s[--i]);
   }
   return out;
  }
#endif
//------------------------------------------------- Writer
  Writer::Writer(Output& out)
  :out(out)
  ,chN(0)
  ,width(0)
  ,sig(SIG)
  ,indentN(0)
  ,decF(*this)
  ,hexF(*this)
  ,leftAlign(*this)
  ,rightAlign(*this)
  ,cNumberF(&decF),cStringF(&leftAlign)
#ifndef NO_FLOATS
  ,putDouble(&Writer::putFix)
#endif  
  ,eol(&defEoL)
  {
  }

 
  Writer::Writer(Output& out,EoLListener& eol)
  :out(out)
  ,chN(0)
  ,width(0)
  ,sig(SIG)
  ,indentN(0)
  ,decF(*this)
  ,hexF(*this)
  ,leftAlign(*this)
  ,rightAlign(*this)
  ,cNumberF(&decF),cStringF(&leftAlign)
#ifndef NO_FLOATS
  ,putDouble(&Writer::putFix)
#endif  
  ,eol(&eol)
  {
  }
  
  Writer& Writer::newLine()
  {
   out.put('\n');
   eol->onEoL(out);
   width=0;
   chN=0;
   cStringF=&leftAlign;
   cNumberF=&decF;
   return *this;
  }

  Writer& Writer::putReverse(const char s[],unsigned len)
  {           // ____01234
              //         1
	      //         
   fillLeft(len);
   while(len>0) putChar(s[--len]);
   cNumberF=&decF;
   return *this;
  }


  const char* Writer::putX_(const char s[])  //xxxxxx_____
  {
   unsigned i=0;
   while(true)
   {
    char ch=s[i++];
    switch(ch)
    {
     case '\0':
      fillLeft(0);
     return 0;
     case '\n':
      newLine();
     return s+i;
    }
    putChar(ch);
   }
  }

  const char* Writer::putX_(const char s[],unsigned len)
  {
   for(unsigned i=0;i<len;i++)
   {
    char ch=s[i];
    if (ch=='\n') 
       {
        newLine();
	return s+i+1;
       }
    putChar(ch);   
   }
   fillLeft(0);
   return 0;
  }

  void Writer::put_XLine(const char s[],unsigned len)
  {
   fillLeft(len);
   for(unsigned i=0;i<len;i++) putChar(s[i]);
  }

  const char* Writer::put_X(const char s[],unsigned len)
  {         //_______xxxx
   fillLeft(len);
   for(unsigned i=0;i<len;i++)
   {
    char ch=s[i];
    switch(ch)
    {
     case '\n':
      put_XLine(s,i);
      newLine();
     return s+i+1;

     case '\t':
      put_XLine(s,i);
     return s+i;
     default:
      putChar(ch);
     break;
    }
   }
   return 0;
  }

  const char* Writer::put_X(const char s[])  //_______xxxx
  {
   if (width==0) return putX_(s); 
   unsigned i=0;
   while(true)
   {
    char ch=s[i];
    switch(ch)
    {
     case '\0':
      put_X(s,i);
     return 0;
     
     case '\n':
      put_XLine(s,i);
      newLine();
     return s+i+1;
     
     case '\t':
      put_XLine(s,i);
     return s+i;
    }
    i++;
   }
  }

  Writer& Writer::putChar(char ch)
  {
   if (chN==0)
      {
       for(unsigned i=0;i<indentN;i++) out.put(' ');
      }
   out.put(ch);
   if (width>0) width--;
   chN++;
   return *this;
  }

  Writer& Writer::fillLeft(unsigned len)
  {
   while(width>len) putChar(Fill);
   return *this;
  }
  
  Writer& Writer::put(char ch)
  {
   switch(ch)
   {
    case '\n':return newLine();
   }
   return putChar(ch);
  }

  Writer& Writer::put(const char s[])
  {
   if (s==0) return put("(null)"); //recursive call
   while(s&&s[0])
   {
    s=cStringF->put(s);
   }
   return *this;
  }

  Writer& Writer::put(const char s[],unsigned len)
  {
   if (s==0) return put("(null)"); //recursive call
   while(s[0])
   {
    const char* s1=cStringF->put(s,len);
    if (s1==0) break;
    len=len-(s1-s); //rest 
    s=s1;
   }
   return *this;
  }
  
  Writer& Writer::setw(int w)
  {
   if (w>=0) 
      { 
       width=w;
       cStringF=&leftAlign;
      }
      else
      {
       width=-w;
       cStringF=&rightAlign;
      }
   return *this;   
  }
  
  Writer& Writer::indent(unsigned w)
  {
   indentN=w;
   return *this;
  }
  
  template<typename typ> Writer& Writer::putAsHex(typ val)
  {
   char s[2*sizeof(typ)+2];
   unsigned l=hexF.put(s,val);
   putReverse(s,l);
   return *this;
  }

  Writer& Writer::hex(unsigned val)
  {
   return putAsHex<unsigned>(val);
  }
  
  Writer& Writer::hex(unsigned short val)
  {
   return putAsHex<unsigned short>(val);
  }

  Writer& Writer::hex(unsigned char val)
  {
   return putAsHex<unsigned char>(val);
  }

  Writer& Writer::hex(char val)
  {
   return putAsHex<char>(val);
  }

  template<typename typ>Writer& Writer::putNumber(typ val)
  {
   cNumberF->put(val);
   return *this;
  }

  Writer& Writer::put(unsigned char val)
  {
   return putNumber<unsigned char>(val);
  }

  Writer& Writer::put(unsigned val)
  {
   return putNumber<unsigned>(val);
  }

  Writer& Writer::put(unsigned short val)
  {return putNumber<unsigned short>(val);}
  
  Writer& Writer::put(int val)
  {return putNumber<int>(val);}
  
  Writer& Writer::put(unsigned long long val)
  {return putNumber<unsigned long long>(val);}

  Writer& Writer::put(int long long val)
  {return putNumber<int long long>(val);}
  
  Writer& Writer::put(const void* val)
  {
#ifdef __x86_64        //  0x0123456789abcdef
   if (val==0) putReverse("      )llun(      ",18);
      else hexF.put((long long unsigned)val);
#else
                         //0x12345678
   if (val==0) putReverse("  )llun(  ",10); //(null)
      else hexF.put((unsigned)val);
#endif

   return *this;   
  }

#if 0
  Writer& Writer::put(double val)
  {
#warning not yet implemented
   put("not yet implemented");
   return *this; 
  }
#endif

  Writer& Writer::put(bool val)
  {
   static const char* Bool[]={"false","true "};
   return put(Bool[val]);
  }

#ifndef NO_FLOATS
  Writer& Writer::putFixStrict(double val)
  {
   return Double(*this,val,sig).fixStrict();
  }

  Writer& Writer::putFix(double val)
  {
   return Double(*this,val,sig).fix();
  }
  
  Writer& Writer::putSci(double val)
  {
   return Double(*this,val,sig).sci();
  }
#endif

  Writer& Writer::rep(unsigned cnt,const char s[])
  {
   while(cnt>0){put(s);cnt--;}
   return *this;
  }

  
  
  Writer& Writer::dump(const char d[],unsigned len,
                       unsigned offset)
  {
   DumpLine<char> line(*this,offset);
   for(unsigned i=0;i<len;i++) line.put(d[i]);
   return *this;
  }

  template<typename T> 
  Writer& Writer::dump(const T d[],unsigned len,unsigned offset)
  {
   DumpLine<T> dL(*this,offset);
   for(unsigned i=0;i<len;++i) dL.put(d[i]);
   return *this;
  }
  
  Writer& Writer::dump(const unsigned char d[],unsigned len,
                       unsigned offset)
  {
   return dump<unsigned char>(d,len,offset);
  }

  Writer& Writer::dump(const unsigned      d[],unsigned len,
                       unsigned offset)
  {
   return dump<unsigned>(d,len,offset);
  }  
  
  Writer& Writer::dump(const unsigned short d[],unsigned len,
                       unsigned offset)
  {
   return dump<unsigned short>(d,len,offset);
  }

  Writer& Writer::dump(unsigned val,const BitDesc bitd[])
  {
   static const char Bool[]="01";
   unsigned i=0;
   while(true)
   {
    const BitDesc& bd=bitd[i++];
    if (bd.name==0) break;
    put(bd.name);
    put(Bool[0x1&(val>>bd.pos)]);
    put('\n');
   }
   return *this; 
  }
  
  void Writer::debug()
  {
//   fprintf(stderr,"\npos0= %d pos1= %d tPos= %d\n",
//                   pos0,    pos1,    tPos);
  }


#ifdef IO_ASCII_WRITE_TEST
  class Tester:public Output
  {
   static Tester tester;
   Writer out;
   void put(char ch){sys::deb::out(ch);}
   Tester();
  };
  
  Tester Tester::tester;
   
  Tester::Tester()
  :out(*this)
  {
   static const unsigned WI=10;
   double v0=1e20; //1.86947e+091;
   double v1=0.000999;
   out<<v0<<"\n";
      
  }
#endif
 }//namespace ascii
}//namespace io
