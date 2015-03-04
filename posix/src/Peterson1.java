class Peterson1 implements Lock {
 private boolean lock[]={false,false}; //from LockFirst
 private int victim;           //from LockSecond
 
 public void lock() {
  int me   =TwoThreads.current();
  int other=TwoThreads.other(me);
  lock[me]=true;
  victim=me;
  while(lock[other] && (victim==me)){}
  // we are in crititcal section
 }
 
 public void unlock(){
  lock[TwoThreads.current()]=false;
 }
}
