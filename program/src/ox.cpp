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

OXimproved::OXimproved(Instance & ins) : instance(ins){}

Crossover::Result OXimproved::operator () (const Individual * m, const Individual * d) const{
  
  const P & mom = *m;
  const P & dad = *d;

  Result r;
  std::pair<int, int> abmom;
  abmom.first = 10000000;
  abmom.second = 10000000;
  for(unsigned int i = 0; i < mom.size()-1; i++){
    int val = instance.ov(mom[i], mom[i+1]);
    if(val < abmom.first) abmom.first = val;
  }
  for(unsigned int i = 0; i < mom.size()-1; i++){
    int val = instance.ov(mom[i], mom[i+1]);
    if(val < abmom.second && val != abmom.first) abmom.second = val;
  }

  std::pair<int, int> abdad;
  abdad.first = 10000000;
  abdad.second = 10000000;
  for(unsigned int i = 0; i < dad.size()-1; i++){
    int val = instance.ov(dad[i], dad[i+1]);
    if(val < abdad.first) abdad.first = val;
  }
  for(unsigned int i = 0; i < dad.size()-1; i++){
    int val = instance.ov(dad[i], dad[i+1]);
    if(val < abdad.second && val != abdad.first) abdad.second = val;
  }

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
