#include <find_union.h>
#include <algorithm>



FindUnion::FindUnion(int size)
{
  parent_ = new int[size];
  rank_ = new int[size];
  for(int i = 0; i < size; i++){
    parent_[i] = i;
    rank_[i] = 0;
  }
}


FindUnion::~FindUnion()
{
  delete [] parent_;
  delete [] rank_;
}


int FindUnion::find(int elem)
{
  int x = elem;
  while(x != parent_[x])
    x = parent_[x];

  while(elem != x){
    int tmp = parent_[elem];
    parent_[elem] = x;
    elem = tmp;
  }

  return x;
}


void FindUnion::sum(int a, int b)
{
  a = find(a);
  b = find(b);
  
  if(rank_[a] == rank_[b]){
    parent_[a] = b;
    rank_[b] ++;
  }
  else if(rank_[a] < rank_[b]){
    parent_[a] = b;
  }
  else{
    parent_[b] = a;
  }
    
}
