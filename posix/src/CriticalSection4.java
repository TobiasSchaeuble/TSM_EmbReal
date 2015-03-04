//---------------------------------
//CriticalSection4
// atomic instructions
//(c) H.Buchmann FHNW 2013
//---------------------------------
import java.util.concurrent.atomic.AtomicLong;
class CriticalSection4 
{
 static class Section
 {
  private AtomicLong val=new AtomicLong();
  Section()
  {
  }
  
  public String toString(){return ""+val;}
  
  void inc()
  {
   val.getAndIncrement();
  }
  
  void dec()
  {
   val.getAndDecrement();
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
   while(cnt>0)
   {
    section();
    --cnt;
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
  inc.join();
  dec.join();
  long delta=System.currentTimeMillis()-start;
  System.err.println("section="+section+" delta="+delta+" ms");  
 }
}
