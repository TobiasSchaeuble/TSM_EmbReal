//----------------------------
//Atomic
//(c) H.Buchmann  FHNW 2012
//$Id$
//----------------------------
import java.util.Date;
import java.util.concurrent.atomic.AtomicLong;

class Atomic
{
 final static long COUNT  =1<<24;
 
 static class Shared
 {
  private long val=0;

  Shared(){}
  void inc()
  {
   ++val;
  }

  void dec()
  {
   --val;
  }
  
  public String toString(){return ""+val;}
 }

 static abstract class Agent implements Runnable //superclass of Incrementer
 {
  private    Thread th     =new Thread(this);
  protected  Shared shared;

  Agent(Shared shared)
  {
   this.shared=shared;
  }

  void start() 
  {
   th.start();
  }
  
  void join()throws Exception
  {
   th.join();
  }
 }

 static class Incrementer extends Agent
 {
  Incrementer(Shared shared) throws Exception
  {
   super(shared);
   start();
  }

  public void run()
  {
   for(int c=0;c<COUNT;++c)
   {
    shared.inc();
   }
  } 
 }

 static class Decrementer extends Agent
 {
  Decrementer(Shared shared) throws Exception
  {
   super(shared);
   start();
  }

  public void run()
  {
   for(int c=0;c<COUNT;++c)
   {
    shared.dec();
   }
  } 
 }
 
 public static void main(String args[]) throws Exception
 {
  Shared shared=new Shared();
  Date t0=new Date();
  Agent inc=new Incrementer(shared);
  Agent dec=new Decrementer(shared);
  inc.join();
  dec.join();
//both threads are dead now  
  Date t1=new Date();
  System.err.println("shared "+shared+" time = "+(t1.getTime()-t0.getTime())+" ms");
 }
}
