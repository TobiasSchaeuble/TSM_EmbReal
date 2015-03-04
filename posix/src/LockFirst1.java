class LockFirst1 implements Lock
{
 boolean lock[]={false,false};
 public void lock()
 {
  int me   =TwoThreads.current(); //me: local variable
  int other=TwoThreads.other(me); //pure function

  lock[me]=true; 
  while(lock[other]){} 
 }
 
 public void unlock()
 {
  int me=TwoThreads.current();
  lock[me)]=false;
 }
}
