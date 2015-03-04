//------------------------------
//Font
//(c) H.Buchmann FHNW 2012
//$Id$
//------------------------------
import java.io.LineNumberReader;
import java.io.InputStreamReader;
import java.io.FileInputStream;
import java.util.zip.GZIPInputStream;
class Font
{
 static class Glyph
 {
  private boolean[][] pixel;
  private int wi;
  Glyph(String li)
  {
   wi=(li.length()==32)?8:16;
   pixel=new boolean[16][wi];
   int r=0;
   int c=0;
   for(int i=0;i<li.length();++i)
   {
    int dig=Character.digit(li.charAt(i),16); //0..15
    int mask=(1<<3);
    while(mask>0)
    {
     pixel[r][c++]=(dig&mask)!=0;
     if (c==wi)
        {
	 c=0;
	 ++r;
	}
     mask>>=1;
    }
   }
  }
  
  private int size_bits()
  {
   return wi*16;
  }
  
  private void display()
  {
   System.err.println("wi="+wi);
   for(boolean[] r:pixel)
   {
    for(boolean c:r)
    {
     System.out.print((c)?'x':'-');
    }
    System.out.println();
   }
  }
  
  private void encode()
  {
   int val=0;
   int cnt=0;
   int bit=0;
   for(boolean[] r:pixel)
   {
    for(boolean c:r)
    {
     if (c) val|=(1<<bit);
     ++bit;
     if (bit==32)
        {
	 if (cnt>0) System.out.print(",");
	 System.out.printf("0x%08x",val);
	 val=0;
	 bit=0;
	 ++cnt;
	}
    }
   }
  }
 } //class Glyph
 
 Glyph glyph[]=new Glyph[0x10000];
 
 private void glyph(String s)
 {
  String[] ss=s.split(":");
  glyph[Integer.parseInt(ss[0],16)]=new Glyph(ss[1]);
 }
 
 private void display(int ch)
 {
  Glyph g=glyph[ch];
  if (g==null)
     {
      System.err.println("not defined");
      return;
     }
  g.display();
 }
 
 
 private void encode(int start,int end)
 {
  System.out.printf("0x%08x,0x%08x,/* start end */ \n",start,end);
//make entries
  int perLine=0;
  int i=0;
  for(int c=start;c<end;++c)
  {
   if (i>0) System.out.print(",");
   if (perLine==4)
      {
       System.out.println();
       perLine=0;
      }
   System.out.printf("0x%08x",i);
   Glyph g=glyph[c];
   if (g==null) g=glyph[0x20];
   i+=(g.size_bits()/32);
   ++perLine;
  }
  System.out.println(",");
  System.out.printf("0x%08x,\n",i); //last
  System.out.println("/* pixel */");
  for(int c=start;c<end;++c)
  {
   Glyph g=glyph[c];
   if (g==null) g=glyph[0x20];
   if (c>start) System.out.println(",");
   g.encode();   
  }
  System.out.println();
 }
 
 private Font(String fontFile) throws Exception
 {
  LineNumberReader src=new LineNumberReader(
   new InputStreamReader(
    new GZIPInputStream(
     new FileInputStream(fontFile)
                       )
                        )
                                           );
  while(true)
  {
   String li=src.readLine();
   if (li==null) break;
   glyph(li);
  }
 }
 
 public static void main(String args[]) throws Exception
 {
  Font f=new Font(args[0]);
/*
  if (args.length==2)
     {
      f.display(args[1].charAt(0));
     }
*/
  f.encode(0x20,128);
 }
}
