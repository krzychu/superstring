#include <crossover.h>
#include <algorithm>
#include <random.h>
#include <cassert>


typedef Individual P;


PMX::PMX(int seg){
  max_seg_ = seg;
}


Crossover::Result PMX::operator () (const P * mom, const P * dad) const{
  Result r;
  std::pair<int, int> ab = randpair(mom->size()); 
  r.first = cross(ab.first, ab.second, mom, dad);
  r.second = cross(ab.first, ab.second, dad, mom);
  return r;
}



P PMX::cross(int a, int b, const P * m, const P * d) const {
  const P & mom = *m;
  const P & dad = *d;

  P child(mom.size());

  b = std::min(b, a + max_seg_);
  
  std::fill(child.begin(), child.end(), -1);
  std::copy(mom.begin() + a, mom.begin() + b, child.begin() + a);

  const int n = mom.size();
  bool was[n];
  std::fill(was, was + n, false);

  int where[n];
  for(int i = 0; i < n; i++)
    where[dad[i]] = i;

  for(int i = a; i < b; i++)
    was[child[i]] = true;

  for(int i = a; i < b; i++){
    if(was[dad[i]])
      continue;
  
    int j = i;
    while(a <= j && j < b)
      j = where[mom[j]];
    
    child[j] = dad[i];
  }

  for(int i = 0; i < n; i++)
    if(child[i] == -1)
      child[i] = dad[i];

  child.set_parents(m, d);

  return child;
}
