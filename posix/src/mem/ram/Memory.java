//--------------------
//Random Access Memory 
//(c) H.Buchmann FHNW 2011
//$Id$
//--------------------
package mem.ram;
import java.io.Writer;
import java.io.StringWriter; //for debug
import java.io.PrintWriter;
import java.io.OutputStreamWriter;

class Memory implements mem.Memory<Address,Integer>
{
 final private int mem[];
 final private int size;   //for fast modulo

 public Memory(int size)  //size=2^sizeExp
 {
  this.size=size;
  mem=new int[size];
 }

 public Integer read(Address a)
 {
  return mem[a.val%size];
 }
 
 public void write(Address a,Integer p)
 {
  mem[a.val%size]=p;
 }
 
 final static int PER_LINE=8; 
 
 public void dump(Writer dst)  //TODO look for a more elegant solution
 {
  PrintWriter out=new PrintWriter(dst,true); //autoflush
  int perLine=0;
  int addr=0;
  out.format("%08x: ",addr);
  for(int v:mem)
  {
   if (perLine==PER_LINE) 
      {
       out.format("\n%08x: ",addr);
       perLine=0;
      }
   if (perLine>0)
      {
       out.print(" ");
      }
   out.format("%08x",v);
   ++perLine;
   ++addr;
  } 
  out.println();
 }
 
 public String toString()
 {
  StringWriter dst=new StringWriter();
  dump(dst);
  return dst.toString();
 }

//------------------------------------------ main
 public static void main(String args[])
 {
  mem.ram.Memory m=new Memory(128);
  m.write(new Address(1),0x12345678);
  System.out.println(m);
 } 
}
