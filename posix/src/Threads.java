//--------------------------
//Threads
//(c) H.Buchmann FHNW 2012
//$Id$
//--------------------------
import java.util.Date;
class Threads //dont confuse with java.lang.Thread
{
 static final long COUNT         =(1<<27); 
 static final long SLEEP         = 63;    //milliseconds */ 
 static final int  RUN           = 32;
 
 TheThread theThreads[];
  
 class TheThread implements Runnable //the peace of code
 {
          Thread th=new Thread(this); 
  private int    id;
  private int    run=0;
          long[] time=new long[RUN];
   
  TheThread(int id) throws Exception
  {
   this.id=id;
   theThreads[id]=this; /* insert in global list */
   th.start();
  }
  
  private void busy(long count) throws Exception
  {
   while(count>0){--count;}
  }
  
  public void run() // the implementation of Runnable
  {
   try
   {
    for(int r=0;r<RUN;++r)
    {
     long t0=System.currentTimeMillis();
//     busy(COUNT);
     Thread.sleep(SLEEP);
     long t1=System.currentTimeMillis();
     time[r]=t1-t0;
    }
   } catch(Exception ex)
   {
   }
  }
  
  void join() throws Exception
  {
   th.join();
  }
 }
 
 private void gnuplot() // see slides 
 {
  System.out.println(
  "set style data histograms\n"+
  "set style histogram rowstacked\n"+
  "set style fill solid 1.0 border -1\n"+
  "set title '"+theThreads.length+" Thread(s)'\n"+
  "set xlabel 'run'\n"+
  "set ylabel 'time[ms]'");

  System.out.print("plot");
  for(int i=0;i<theThreads.length;++i)
  {
   if (i>0) System.out.print(',');
   System.out.println("\\");
   System.out.print("'-' using 2 title 'T#"+i+"'");
  }
  System.out.println();
  for(TheThread th:theThreads)
  {
   for(int i=0;i<RUN;++i)
   {
    System.out.println(i+"\t"+th.time[i]);
   }
   System.out.println("e");
  }
 }

 private void time()
 {
  long sum=0;
  for(int r=0;r<RUN;++r)
  {
   System.out.print(r);
   for(TheThread th:theThreads)
   {
    long ti=th.time[r];
    sum+=ti;
    System.out.print("\t"+ti);
   }
   System.out.println();
  }
 }
  
 private Threads(int threadsN) throws Exception
 {
  long t0=System.currentTimeMillis();
  theThreads=new TheThread[threadsN];
  for(int i=0;i<threadsN;++i)
  {
   new TheThread(i); 
  }
  for(TheThread th:theThreads) th.join();
  long total=System.currentTimeMillis()-t0;
  gnuplot();
//  time();
  System.err.println(total);
 }
 
 
 public static void main(String args[]) throws Exception
 {
  if (args.length!=1)
     {
      System.err.println("usage Threads nbrOfThreads");
      System.exit(1);
     }
  new Threads(Integer.parseInt(args[0]));
 }
}
