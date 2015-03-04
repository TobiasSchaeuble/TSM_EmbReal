class LockSecond1 implements Lock
{
 private int victim;
 
 public void lock()
 {
  int me=TwoThreads.current();
  victim=me;
  while(victim==me){} 
 }
 
 public void unlock()
 {
 }
}
