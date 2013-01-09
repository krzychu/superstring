#include <parent_selector.h>
#include <algorithm>
#include <random.h>
#include <cstdio>

std::vector<const Individual *>
  KBestSelector::operator() (const AlgorithmState & state) const
{
  std::vector<const Individual *> result;
  const Population & P = state.population();

  for(int i = 0; i < k_; i++)
    result.push_back(P[i]);

  return result;
}



std::vector<const Individual *>
  RouletteSelector::operator() (const AlgorithmState & state) const
{
  const Population & P = state.population();
  double sum = 0;
  double * ps = new double[P.size() + 1];
  for(int i = 0; i < P.size(); i++){
    sum += P[i]->scaled_adaptation();
    ps[i] = P[i]->scaled_adaptation();
  }
  ps[P.size()] = 10;

  // scale adaptations to get probabilities
  for(int i = 0; i < P.size(); i++)
    ps[i] /= sum;


  // calculate distribuant
  for(int i = 1; i < P.size(); i++)
    ps[i] += ps[i-1];

  
  // game
  std::vector<const Individual *> result;
  for(int i = 0; i < k_; i++){
    double coin = randu();
    double * bin = std::upper_bound(ps, ps + P.size() + 1, coin);  

    int bin_num = bin - ps;
    bin_num = std::min(bin_num, P.size() - 1);
    result.push_back(P[bin_num]); 
  }
  delete [] ps;

  return result;
}


