#include <crossover.h>
#include <random.h>
#include <cassert>


typedef Individual P;


Crossover::Result Composition::operator () (const P * mom, const P * dad) const{
  Crossover::Result r;
  r.first = cross(mom, dad);
  r.second = cross(dad, mom);
  return r;
}



P Composition::cross(const P * m, const P * d) const{
  const Individual & mom = *m;
  const Individual & dad = *d;
  const int n = mom.size();
  P child(n);

  for(int i = 0; i < n; i++){
    child[i] = mom[dad[i]];
  }
  
  child.set_parents(m, d);
  assert(child.valid());

  return child;
}
