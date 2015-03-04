class LockSecond implements Lock
{
 private int victim;
 
 public void lock()
 {
  victim=TwoThreads.current();
  while(victim==TwoThreads.current()){} 
 }
 
 public void unlock()
 {
 }
}
