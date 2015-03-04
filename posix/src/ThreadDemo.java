//-------------------
//ThreadDemo
//(c) H.Buchmann FHNW 2013
//$Id$
//-------------------
class ThreadDemo
{
 static class MyThread implements Runnable
 {
  private String name;
  private Thread th=new Thread(this); 
                            // Runnable.run 
  
  MyThread(String name) //this code is executed in main
  { 
   this.name=name; 
   th.start();
  }
  
  public void run()     //the threads code
  {
   while(true)
   {
    System.out.println(name);
   }
  }
 }
 
 public static void main(String args[])
 {
  new MyThread("111111111");
  new MyThread("222222222");
 }
}
