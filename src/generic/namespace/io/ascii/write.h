#pragma once
//---------------------------
//write
//(c) H.Buchmann FHSO 2003
//$Id: write.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//TODO rewrite
//TODO significant(20) dont works
//---------------------------
INTERFACE(io_ascii_write,$Revision: 189 $)
#include "io/ascii/out.h"
#include "util/float-conv.h"

namespace io
{
 namespace ascii
 {
  class Writer
  {
   public:
//------------------------------------------------- EOLListener
//what to do in case of eol
    struct EoLListener
    {
     virtual ~EoLListener(){}
     virtual void onEoL(Output&)=0;
                     //the \n will be written by the writer
                     //avoid recursive call
    };
    
//------------------------------------------------- DumpLine
    template<typename T>
    class DumpLine //used in dump(const char d[],unsigned len)
    {
     public:
      static const unsigned MAX_BYTE = 16;
              DumpLine(Writer& out,
	              unsigned offset);
     virtual ~DumpLine();
     void put(T val);

     private:
      Writer& out;
      static const unsigned PerLine=MAX_BYTE/sizeof(T);
      T line[PerLine];
      unsigned lineIdx;       //0<=lineIdx<perLine
      unsigned offset;
      void show();
    };
    
   private:
    Writer(const Writer&);
    Writer  operator=(const Writer&);

//------------------------------------------------- Formatter
    struct Formatter
    {
     Writer& wr;
              Formatter(Writer& wr):wr(wr){}
     virtual ~Formatter(){}
    };
    
//------------------------------------------------- StringFormatter
    struct StringFormatter:public Formatter
    {
              StringFormatter(Writer& wr):Formatter(wr){}
     virtual ~StringFormatter(){}
//both stops at eol     
     virtual const char* put(const char s[]) const=0; //zero terminated
     virtual const char* put(const char s[],unsigned len) const=0;
    };
    
    struct LeftAlign:public StringFormatter //xxxx___
    {
      LeftAlign(Writer& wr):StringFormatter(wr){}
     ~LeftAlign(){}
     const char* put(const char s[]) const; 
     const char* put(const char s[],unsigned len) const;
    };
    
    struct RightAlign:public StringFormatter //____xxx
    {
      RightAlign(Writer& wr):StringFormatter(wr){}
     ~RightAlign(){}
     const char* put(const char s[]) const; 
     const char* put(const char s[],unsigned len) const;
    };
    
//    typedef const char* (Writer::*StringFormat)(const char s[]);

//------------------------------------------------- NumberFormatter
    struct NumberFormatter:public Formatter
    {
              NumberFormatter(Writer& wr):Formatter(wr){}
     virtual ~NumberFormatter(){}
     virtual Writer& put(unsigned char) const=0;
     virtual Writer& put(unsigned short) const=0;
     virtual Writer& put(unsigned) const=0;
     virtual Writer& put(int) const=0;
     virtual Writer& put(unsigned long long) const=0;
     virtual Writer& put(int long long) const=0;
    };
    
//------------------------------------------------- Dec.Formatter
    struct Dec:public NumberFormatter
    {
     template<typename typ>Writer& putU(typ) const; //unsigned
     template<typename typ>Writer& putS(typ) const; //signed
     Dec(Writer& wr):NumberFormatter(wr){}
     Writer& put(unsigned char) const;
     Writer& put(unsigned short) const;
     Writer& put(unsigned) const;
     Writer& put(int) const;
     Writer& put(unsigned long long) const;
     Writer& put(int long long) const;
    };

//------------------------------------------------- Hex.Formatter
    struct Hex:public NumberFormatter
    {
     template<typename typ>unsigned put(char s[],typ) const;
     template<typename typ>Writer&  put(typ) const;
     
     Hex(Writer& wr):NumberFormatter(wr){}
//result in s in reversed order without prefix 0x
//return len
     unsigned put(char s[],unsigned short) const; 
     unsigned put(char s[],unsigned) const;     
     
     Writer& put(unsigned char) const;
     Writer& put(unsigned short) const;
     Writer& put(unsigned val) const;
     Writer& put(int val) const{return put((unsigned)val);}
     Writer& put(unsigned long long) const;
     Writer& put(int long long val) const{return put((unsigned long long)val);}
    };

//------------------------------------------------- Default.Formatter    
    struct DefaultEoL:public EoLListener
    {
     void onEoL(Output&); //does nothing
    };

#ifndef NO_FLOATS
//------------------------------------------------- Double
    struct Double:public util::Double::Format
    {
     typedef Writer& (Double::*FixForm)();
     Writer& out;
     unsigned fixLen; //length in fixed format
     unsigned sciLen; //       in sci format
     FixForm fixForm; //will be set in constructor
     void prefix(unsigned len); //fill and sign
     void fixPrefix(){prefix(fixLen);}
     Writer& put(const char s[],unsigned len); //right aligned 
                                               //respecting out.width 
     Writer& fix_d_d(); //d.ddd
     Writer& fix_0_d(); //0.0ddd
     Writer& fix_d_0(); //ddd000

     Double(Writer& out,double val,unsigned sig);
     Writer& fixStrict(){(this->*fixForm)();return out;}
     Writer& fix();
     Writer& sci();
    };
#endif     

    typedef Writer& (Writer::*Put)(double); 
    
    static const char  Digits_[];
    static const char*const Digits;
    static const char Fill;
    static const unsigned SIG=6; //default number of significant digits 
                                 //for doubles
//    static const unsigned MAX_TAB_NBR = 40;

    Output& out;
//------------------------------------------------- state
    unsigned   chN;   //number of chars in current line
    unsigned   width; //set by setw normally 0 
                      //set by putChar
    unsigned   sig;   //the number of significant digits 
                      //for double		      
    unsigned   indentN; //the blanks after new line		    
    Dec        decF;
    Hex        hexF;
    LeftAlign  leftAlign;
    RightAlign rightAlign;
    DefaultEoL defEoL;
              
    NumberFormatter*  cNumberF; //current 
    StringFormatter*  cStringF;
    Put               putDouble;
    EoLListener* eol;
    
    Writer& newLine();
    Writer& putChar(char ch);
    Writer& fillLeft(unsigned len);      //ffffxxxxx 
    Writer& putReverse(const char s[],
                       unsigned len);    //_______xxxx
 
    const char* putX_(const char s[]); //xxxxxx_____
    const char* putX_(const char s[],unsigned len);

    const char* put_X(const char s[]); //_______xxxx
    const char* put_X(const char s[],unsigned len);
    void put_XLine(const char s[],unsigned len);
                  //s contains no \n char
      

    template<typename T> 
    Writer& dump(const T d[],unsigned len,
                 unsigned offset);
   
    template<typename typ> Writer& putNumber(typ val);
    template<typename typ> Writer& putAsHex(typ val);
    void debug();

   public:
	     Writer(Output& out);
	     Writer(Output& out,EoLListener&);
	     Writer(Output& out,EoLListener&,const char tabString[]);
    virtual ~Writer(){}
    Writer& setOutput(Output& new_){out=new_;return *this;}
    Output& getOutput()const{return out;}
    Writer& setEoLListener(EoLListener&  eol){this->eol=&eol;return *this;}
    const EoLListener& getEoLListener()const{return *eol;}
    Writer& dec(){cNumberF=&decF;return *this;}
    Writer& hex(){cNumberF=&hexF;return *this;}
    Writer& setw(int w);
         //w<0  strings right aligned ____ssss
	 //w>0          left  aligned ssss____ 
	 //numbers always right aligned

    Writer& fix(){putDouble=&Writer::putFix;return *this;}
            //fixpoint dd.ddd
    Writer& sci(){putDouble=&Writer::putSci;return *this;}
            //scientific d.ddddesddd
    Writer& significant(unsigned sig){this->sig=sig;return *this;}
            //number of significant digits
    Writer& indent(unsigned w);
    unsigned getIndent()const{return indentN;}

    Writer& incIndent(unsigned w){return indent(indentN+w);}
    Writer& decIndent(unsigned w)
            {return (indentN>=w)?indent(indentN-w):indent(0);}
    
    Writer& put(char ch);
    Writer& put(const char s[]); //terminating zero
    Writer& put(const char s[],unsigned len); //len chars
    Writer& put(unsigned char val);
    Writer& put(unsigned short val);
    Writer& put(unsigned val);
    Writer& put(int val);
    Writer& put(unsigned long long val);
    Writer& put(int long long val);
    Writer& put(const void* val);
    Writer& put(unsigned long val){return put((unsigned)val);}
    Writer& put(bool val);
    Writer& put(double val){return (this->*putDouble)(val);}
    Writer& putFixStrict(double val);
       //fixpoint always even it makes not really sense
       //1e300 = 10....0 300 zeroes
    Writer& putFix(double val);
       //fixpoint if possible sig: number of significant digits
       // 0.000ddddd 
       //ddddd000000 
    Writer& putSci(double val);
       //scientific sig: number of significant digits
       //[s]d.ddddeszzz
       //s: sign +|-
       //d: digits sig times
       //e: 'e'
       //z: digits of exp   

    Writer& rep(unsigned cnt,const char s[]);
    Writer& blank(unsigned cnt){return rep(cnt," ");}

//------------------------------------ stateless unformatted
//hex output without prefix 0x
    Writer& hex(unsigned val);
    Writer& hex(unsigned short val);
    Writer& hex(unsigned char val);
    Writer& hex(char val);
    Writer& dec(unsigned val)      {return decF.put(val);}
    Writer& dec(unsigned short val){return decF.put(val);}
    Writer& dec(int val)           {return decF.put(val);}

//------------------------------------ debug
    Writer& dump(const char d[],unsigned len,
                 unsigned offset);
    Writer& dump(const char d[],unsigned len)
                {return dump(d,len,0);}

    Writer& dump(const unsigned char d[],unsigned len,
                 unsigned offset);
    Writer& dump(const unsigned char d[],unsigned len)
                {return dump(d,len,0);}

    Writer& dump(const unsigned      d[],unsigned len,
                 unsigned offset);
    Writer& dump(const unsigned  d[],unsigned len)
                {return dump(d,len,0);}

    Writer& dump(const unsigned short d[],unsigned len,
                 unsigned offset);
    Writer& dump(const unsigned short d[],unsigned len)
		{return dump(d,len,0);}
		
    struct BitDesc
    {
     const char* name;
     unsigned pos;
    };
    Writer& dump(unsigned val,const BitDesc bd[]);  
                                   //bd.name=0 terminates list
#if 0
//try once this
    template<typename T>Writer& operator <<(T t){return put(t);}
#endif

#if 1
    Writer& operator <<(char ch){return put(ch);}
    Writer& operator <<(const char s[]){return put(s);}
    Writer& operator <<(unsigned val){return put(val);}   
    Writer& operator <<(unsigned char val){return put(val);}
    Writer& operator <<(unsigned short val){return put(val);}
    Writer& operator <<(int val){return put(val);}
    Writer& operator <<(unsigned long val){return put(val);}
    Writer& operator <<(unsigned long long val){return put(val);}
    Writer& operator <<(int long long val){return put(val);}
    Writer& operator <<(double val){return put(val);}
    Writer& operator <<(const void* val){return put(val);}
    Writer& operator <<(bool val){return put(val);}
    
#endif    
  };

//------------------------------------- Formatter 
//similar to iomanip
  class Formatter
  {
   protected:
    virtual Writer& doIt(Writer& out) const=0;
    virtual ~Formatter(){}
   public:
    friend Writer& operator<<(Writer& out,const Formatter& f)
                   {return f.doIt(out);}
  };
//------------------------------------- some Formatters
  class hex:public Formatter
  {
   private:
    Writer& doIt(Writer& out) const{return out.hex();}
   public:
    hex(){} 
  };

  class dec:public Formatter
  {
   private:
    Writer& doIt(Writer& out) const{return out.dec();}
   public:
    dec(){} 
  };

  class fix:public Formatter
  {
   private:
    Writer& doIt(Writer& out) const{return out.fix();}
   public:
    fix(){} 
  };

  class sci:public Formatter
  {
   private:
    Writer& doIt(Writer& out) const{return out.sci();}
   public:
    sci(){} 
  };
  
  class significant:public Formatter
  {
   private:
    unsigned sig;
    Writer& doIt(Writer& out) const{return out.significant(sig);}
   public:
    significant(unsigned sig):sig(sig){} 
  };
  
  class setw:public Formatter
  {
   private:
    int w;
    Writer& doIt(Writer& out) const{return out.setw(w);}
   public:
    setw(int w):w(w){} 
  };
  
  class indent:public Formatter
  {
   private:
    unsigned ind;
    Writer& doIt(Writer& out) const{return out.indent(ind);}
   public:
    indent(unsigned ind):ind(ind){} 
  };
  template<typename T>
  Writer::DumpLine<T>::DumpLine(Writer& out,unsigned offset)
  :out(out)
  ,lineIdx(0)
  ,offset(offset)
  {
  }

  template<typename T>
  Writer::DumpLine<T>::~DumpLine()
  {
   show();
  }
    
  template<typename T>
  void Writer::DumpLine<T>::put(T val)
  {
   if (lineIdx==PerLine) show();
   line[lineIdx++]=val;      
  }
  
  template<typename T>
  void Writer::DumpLine<T>::show()
  {
   out.hex(offset)<<": ";
   unsigned i=0;
   for(;i<lineIdx;i++)
   {
    T v=line[i];
    if (i==8) out.put(' ');//extra space	
    out.hex(v) 
       .put(' ');
    offset+=sizeof(T);
   }
   for(;i<PerLine;i++) 
   {
    if (i==8) out.put(' '); //extra space 
    out.blank(2*sizeof(T)+1);
   }
   out.put("  ");
   for(unsigned i=0;i<lineIdx;i++)
   {
    T v=line[i];
    for(unsigned shift=0;shift<sizeof(T);++shift)
    {
     char ch=(char)(0xff&v);
     if(sizeof(T)>1) v>>=8;
     out.put( ((' '<=ch)&&(ch<='~'))?ch:'.');
    }
   };
   out.put('\n');
   lineIdx=0;
  }

 }//namespace ascii
}//namespace io
