#include <crossover.h>
#include <algorithm>
#include <random.h>
#include <cassert>


typedef Individual P;

Crossover::Result OX::operator () (const P * mom, const P * dad) const{
  Result r;
  std::pair<int, int> ab = randpair(mom->size()); 
  r.first = cross(ab.first, ab.second, mom, dad);
  r.second = cross(ab.first, ab.second, dad, mom);
  return r;
}


P OX::cross(int a, int b, const P * m, const P * d) const{
  const P & mom = *m;
  const P & dad = *d;

  assert(mom.valid());
  assert(dad.valid());
  
  P child(mom.size());

  const int n = mom.size();
  bool was[n];
  std::fill(was, was + n, false);
  
  for(int i = 0; i < a; i++){
    child[(n - b + i) % n] = mom[i];
    was[mom[i]] = true;
  }


  int j = b;
  for(int i = 0; i < n - a; i ++){
    while(was[dad[j]]){
      j = (j + 1) % n;
    }
    child[(n - b + a + i) % n] = dad[j];
    was[dad[j]] = true;
  }
  
  child.set_parents(m, d);
  assert(child.valid());
  
  return child;
}
