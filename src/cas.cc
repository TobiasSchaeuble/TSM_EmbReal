//---------------------------
// cas
// (c) H.Buchmann FHNW 2012
// $Id$
//compile as c++ file
//----------------------------

template<typename T> T cas(T* mem,T old_, T new_)
{
 T old=*mem;
 if (old=old_) *mem=new_;
 return old;
}

void atomic_inc(unsigned* mem)
{
 while(true)
 {
  unsigned n0=*mem; 
  unsigned n1=*mem+1;
  if (cas(mem,n0,n1)==n0) break;
 }
}

int main()
{
 unsigned mem=0;
 unsigned v=cas(&mem,0u,1u);
}
