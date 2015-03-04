//------------------------
//Cache
//(c) H.Buchmann FHNW 2011
//$Id$
//be careful: there are two kind of addresses:
// the Cache.Address line,pos
// the Memory Address of type Integer
//------------------------
package mem.ram;
class Cache implements mem.Cache<Cache.Address,Integer>
{
 class Address   //nested class
 {
  int tag;
  int line;
  int pos;

  Address(mem.ram.Address a)
  {
   pos=a.val%lineL;
   line=(a.val/lineL)%lineN;
   tag= (a.val/lineL)/lineN;
  }
  
  public String toString(){return ""+tag+":"+line+":"+pos;}
 }

 final Memory memory;
 final int lineN;
 final int lineL;
 
 class Line //inner class
 {
  int     tag;
  boolean valid=false;
  int line[]=new int[lineL];

  void fill(Integer from) //from memory
  {
   for(int i=0;i<lineL;++i) line[i]=memory.read(from++);
   valid=true;
  }

  void flush(Integer to)
  {
   for(int i=0;i<lineL;++i) memory.write(to++,line[i]);
   valid=false;
  }
  
  Integer read(int pos)
  {
   return line[pos];
  } 
  
  void write(int pos,Integer p)
  {
   line[pos]=p;
  }
 }
 
 Line lines[];

 Cache(Memory m,int lineN,        //number of lines
                int lineL)        //length of lines
 {
  this.memory=m;
  this.lineN=lineN;
  this.lineL=lineL;
  lines=new Line[lineN];
  for(int i=0;i<lineN;++i) lines[i]=new Line();
 }

//TODO discuss where to put the Integer -> Cache.Address transformation   
 public Integer read(mem.ram.Address a)
 {
  Address ca=new Address(a);
  if (!hit(ca))
     {
     }
  return lines[a.line].read(a.pos);
 }
 
 public void write(mem.ram.Address a,Integer p)
 {
  lines[a.line].write(a.pos,p);
 }
 
 public boolean hit(Address a)
 {
  Line l=lines[a.line];
  return l.valid&&(l.tag==a.tag);
 }
 
 public boolean valid(Address a)
 {
  return lines[a.line].valid;
 }
 
 public void fill(Address to,Integer from)
 {
  lines[to.line].fill(from);
 }

 public void flush(Address from,Integer to)
 {
  lines[from.line].flush(to);
 }
  
 public void dump()
 {
 }
}
