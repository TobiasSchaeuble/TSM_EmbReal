class Peterson implements Lock {
 private boolean lock[]={false,false}; //from LockFirst
 private int victim;           //from LockSecond
 
 public void lock() {
  lock[TwoThreads.current()]=true;
  victim=TwoThreads.current();
  while(lock[TwoThreads.other()] && 
       (victim==TwoThreads.current())){}
  // we are in crititcal section
 }
 
 public void unlock(){
  lock[TwoThreads.current()]=false;
 }
}
