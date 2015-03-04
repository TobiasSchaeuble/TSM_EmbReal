//---------------------------------
//CriticalSection0
// shows the problem
//(c) H.Buchmann FHNW 2013
//---------------------------------
import java.util.concurrent.atomic.AtomicLong;

class CriticalSection
{
 static class Section
 {
  private AtomicLong val=new AtomicLong(0);
  Section()
  {
  }
  
  public String toString(){return ""+val;}
  
  void inc()
  {
   val.incrementAndGet();
  }
  
  void dec()
  {
   val.decrementAndGet();
  }
 }
 
 static abstract class Agent implements Runnable //operation on Section
 {
  private Thread th=new Thread(this);
  protected Section section;
  private int cnt;
  
  protected Agent(Section s,int cnt)
  {
   this.section=s;
   this.cnt=cnt;
  }
  
  protected void start()
  {
   th.start();
  }
  
  abstract void section(); //do something with section

  public void run() 
  {
   try
   {
    while(cnt>0)
    {
     section();
     --cnt;
    }
   }
   catch(Exception ex)
   {
    ex.printStackTrace();
   }
  }
  
  public void join() throws Exception
  {
   th.join();
  }
 }
 
 static class Decrementer extends Agent
 {
  public Decrementer(Section s,int cnt)
  {
   super(s,cnt);
   start();
  }
  
  void section()
  {
   section.dec();
  }
 }
 
 static class Incrementer extends Agent
 {
  public Incrementer(Section s,int cnt)
  {
   super(s,cnt);
   start();
  }
  
  void section() 
  {
   section.inc();
  }
 }
 
 public static void main(String args[]) throws Exception
 {
  Section section=new Section();
  int cnt=(1<<25);
  long start=System.currentTimeMillis();
  Agent inc=new Incrementer(section,cnt);
  Agent dec=new Decrementer(section,cnt);
  dec.join();
  inc.join();
  long delta=System.currentTimeMillis()-start;
  System.err.println("section="+section+" delta="+delta+" ms");  
 }
}
