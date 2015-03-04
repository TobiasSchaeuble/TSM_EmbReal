//--------------------
//CachedMemory
//(c) H.Buchmann FHNW 2011
//$Id$
//--------------------
package mem.ram;
class CachedMemory extends Memory
{
 final private Cache cache;
 final private int lineN;
 final private int lineL;
 
 CachedMemory(int size,
              int lineN,  
	      int lineL)
 {
  super(size);
  this.lineN=lineN;
  this.lineL=lineL;
  cache=new Cache(this,lineN,lineL);
 }
 
 
 public Integer read(Address a)
 {
  return cache.read(a);    //delegate to cache
 }
 
 public void write(Address a,Integer p)
 {
  cache.write(a,p);      //delegate to cache
 }
 
 public static void main(String args[])
 {
  mem.ram.Memory m=new CachedMemory(128, //size  
                                    4,   //lineN
                                    4);  //lineL 
  m.write(1,0x12345678);
  m.write(1,0x9abcdef0);
  System.out.println(m);
 } 
 
}
