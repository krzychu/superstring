#include <replacement.h>
#include <gtest/gtest.h>


TEST(BestOfReplacement, SelectsBest){
  AlgorithmState state;  
  Population & p = state.population();

  const int n = 3;
  double costs[] = {1,3,5,2,4,6};
  for(int i = 0; i < n; i++){
    Individual * ind = new Individual(10);
    ind->set_cost(costs[i]);
    p.add(ind);
  }

  std::vector<Individual *> children;
  for(int i = n ; i < 2*n; i++){
    Individual * ind = new Individual(10);
    ind->set_cost(costs[i]);
    children.push_back(ind);
  }

  BestOfReplacement repl;
  repl(state, children);
  
  p.update_stats();
  for(int i = 0; i < n ; i++)
    ASSERT_EQ(i + 1, p[i]->cost());
}
