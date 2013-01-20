#include <random.h>
#include <cassert>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <local_search.h>
#include <iostream>
#include <bitset>
#include <queue>

typedef Individual P;


LocalSearch::Result TranspositionSearch::operator() 
  (const Individual * a) const
{
  Result result(*a, 0);
  const int n = a->size();
  for(int i = 0; i < n; i++){
    for(int j = i + 1; j < n; j++){
      Individual candidate(*a);  
      candidate.swap(i, j);
      int cost = instance_.evaluate(&candidate);
      candidate.set_cost(cost);
      if(cost < result.individual.cost())
        result.individual = candidate;
      result.num_processed++;
    }
  }
  return result;
}



LocalSearch::Result InsertionSearch::operator() 
  (const Individual * a) const
{
  Result result(*a, 0);
  const int n = a->size();
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(i == j)
        continue;
      Individual candidate(*a);  
      candidate.insert(i, j);
      int cost = instance_.evaluate(&candidate);
      candidate.set_cost(cost);
      if(cost < result.individual.cost())
        result.individual = candidate;
      result.num_processed++;
    }
  }
  return result;
}





void SimpleStrategy::operator () (AlgorithmState & state, 
      std::vector<Individual *> & children) const
{
	for(unsigned int i = 0; i < children.size(); i++){
		LocalSearch::Result r = local_search_(children[i]);
		*(children[i]) = r.individual;
    state.set_best_if_better(r.individual);
    state.inc_processed(r.num_processed);
	}
}



void ParallelSearchStrategy::operator () (AlgorithmState & state, 
      std::vector<Individual *> & children) const
{
  #pragma omp parallel for
	for(unsigned int i = 0; i < children.size(); i++){
		LocalSearch::Result r = local_search_(children[i]);
		*(children[i]) = r.individual;
    
    #pragma omp critical
    {
      state.set_best_if_better(r.individual);
	    state.inc_processed(r.num_processed);
    }
  }
}
