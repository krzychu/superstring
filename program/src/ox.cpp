#include <crossover.h>
#include <algorithm>
#include <random.h>
#include <cassert>
#include <instance.h>

typedef Individual P;

Crossover::Result OX::operator () (const P * mom, const P * dad) const{
  Result r;
  std::pair<int, int> ab = randpair(mom->size()); 
  r.first = cross(ab.first, ab.second, mom, dad);
  r.second = cross(ab.first, ab.second, dad, mom);
  return r;
}


std::pair<int, int> smallest_idx(const Individual & P, const Instance & instance){
  const int n = P.size();
  const int inf = std::numeric_limits<int>::max();

  int best = -1;
  int best_val = inf;

  int second = -1;
  int second_val = inf;

  for(int i = 0; i < n - 1; i++){
    int v = instance.ov(P[i], P[i+1]);
    if(v < best_val){
      second_val = best_val;
      second = best;
      best_val = v;
      best = i;
    }
    else if(v < second_val){
      second_val = v;
      second = i;
    }
  }

  return std::make_pair(best, second);
}



Crossover::Result OXimproved::operator () (const Individual * m, const Individual * d) const{
  
  const P & mom = *m;
  const P & dad = *d;

  Result r;
  std::pair<int, int> abmom = smallest_idx(mom, instance_);
  std::pair<int, int> abdad = smallest_idx(dad, instance_);
  r.first = cross(abmom.first, abmom.second, m, d);
  r.second = cross(abdad.first, abdad.second, d, m);

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
