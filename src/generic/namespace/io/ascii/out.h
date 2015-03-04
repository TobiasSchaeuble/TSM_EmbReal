#pragma once
//---------------------------
//out
//(c) H.Buchmann FHSO 2003
//$Id: out.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//---------------------------
INTERFACE(io_ascii_out,$Revision: 137 $)
namespace io
{
 namespace ascii
 {
//------------------------------------------------- Output
  struct Output
  {
   virtual ~Output();
   virtual void put(char ch)=0;
   virtual void put(const char s[]); 
           //overwrite this if you have a better solution   
  };
  
//------------------------------------------------- Entaber
//replaces sequence of whitespace with tab char if appropriate
  class Entaber:public Output
  {
   private:
    Output& layer;
    const unsigned tab;
    unsigned pos;         //|----->|
                          //t      pos
    unsigned blankN;      //the number of consecutive blanks
 
   public:
    using Output::put;
             Entaber(Output& layer,unsigned tab=8);
    virtual ~Entaber();
    void put(char ch);
  };
  
 }
}
