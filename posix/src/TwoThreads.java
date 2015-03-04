//---------------------
//TwoThreads
//(c) H.Buchmann FHNW 2013
//---------------------
class TwoThreads
{
 static int current(){return 0;}
 static int other(){return 1;} 

 static int other(int th) //pure function
 {
  return 1-th; 
 }
}
