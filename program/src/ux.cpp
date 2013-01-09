#include <crossover.h>
#include <algorithm>
#include <random.h>

typedef Individual P;


UX::UX(int num){
  num_exchanged_ = num;
}


Crossover::Result UX::operator() 
  (const P * a, const P * b) const
{
  // select random subset  
  std::vector<int> indices = randsubset(a->size(), num_exchanged_);

  Result r;
  r.first = cross(indices, a, b);
  r.second = cross(indices, b, a);

  return r;
}


P UX::cross(const std::vector<int> & ind, const P * m, const P * d) const{
  const Individual & mom = * m;
  const Individual & dad = * d;

  const int n = mom.size();
  
  P child(n);
  std::fill(child.begin(), child.end(), -1);
 
  bool in[n];
  bool was[n];
  std::fill(in, in + n, false);
  std::fill(was, was + n, false);

  for(unsigned int i = 0; i < ind.size(); i++){
    child[ind[i]] = mom[ind[i]];
    was[child[ind[i]]] = true;
    in[ind[i]] = true;
  }

  int where[n];
  for(int i = 0; i < n; i++)
    where[dad[i]] = i;

  for(unsigned int i = 0; i < ind.size(); i++){
    int j = ind[i];
    if(was[dad[j]])
      continue;

    while(in[j])
      j = where[child[j]];

    child[j] = dad[ind[i]];
  }

  for(int i = 0; i < n; i++){
    if(child[i] == -1)
      child[i] = dad[i];
  }

  child.set_parents(m, d);

  return child;
}
