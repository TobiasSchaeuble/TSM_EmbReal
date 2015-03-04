class LockFirst implements Lock
{
 boolean lock[]={false,false};
 public void lock()
 {
  lock[TwoThreads.current()]=true; 
  while(lock[TwoThreads.other()]){} 
 }
 
 public void unlock()
 {
  lock[TwoThreads.current()]=false;
 }
}
