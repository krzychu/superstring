#include <mutation.h>
#include <random.h>
#include <cassert>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <crossover.h>
#include <cmath>

typedef Individual P;

RandomPermutationCrossover::RandomPermutationCrossover(double c){
  Constancy = c;
}


void RandomPermutationCrossover::operator () (Individual * a) const{
  const int n = a->size();
  P randPerm(n);
  std::vector<int> vConst;
  std::vector<int> vDiff;

  for(int i = 0; i < n; i++){

    if(randbool(Constancy)) vConst.push_back(i);
    else vDiff.push_back(i);
  }

  std::random_shuffle ( vDiff.begin(), vDiff.end() );

  unsigned int vc = 0;
  unsigned int vd = 0;
  for(int i = 0; i < n; i++){
    if(vc < vConst.size() && vConst[vc] == i){
      randPerm[i] = vConst[vc];
      vc++;
    }
    else{
      randPerm[i] = vDiff[vd];
      vd++;
    }
  }


  Composition c;
  Individual res = c.cross(&randPerm, a);
  std::copy(res.begin(), res.end(), a->begin());
}


PermutationShift::PermutationShift(double s){
  Shift = s;
}

void PermutationShift::operator () (Individual * a) const{
  const int n = a->size();
  
  const int s = (int)((float)(n) * Shift);
  const int shift = randint(1, 2*s);

  P shiftedPerm(n);

  for(int i = 0; i < n; i++){
    int x = (i + shift >=  n) ? (i+shift - n) : (i+shift);
    shiftedPerm[i] = (*a)[x];
  }

  std::copy(shiftedPerm.begin(), shiftedPerm.end(), a->begin());

  assert( a->valid() );
}



void RandomMutationStrategy::operator() (AlgorithmState & state, 
  std::vector<Individual *> & children) const
{
  for(unsigned int i = 0; i < children.size(); i++)
    if(randbool(p_))
      mutation_(children[i]);
}


void ProportionalMutationStrategy::operator() (AlgorithmState & state, 
  std::vector<Individual *> & children) const
{
  double d = state.population().dissipation();
  double p = min_prob_ * d + max_prob_ * (1 - d);
  for(unsigned int i = 0; i < children.size(); i++)
    if(randbool(p))
      mutation_(children[i]);
}


