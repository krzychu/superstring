#include <gtest/gtest.h>
#include <crossover.h>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;


TEST(RandomPairCrossoverStrategy, EachParentIsInOnePair){
  AlgorithmState st;
  std::vector<const Individual *> parents;
  const int n = 100;
  for(int i = 0; i < n; i++){
    Individual * next = new Individual(50); 
    next->randomize();
    parents.push_back(next);
  }

  PMX pmx; 
  RandomPairCrossoverStrategy rpcs(pmx);

  std::vector<Individual *> children;
  children = rpcs(st, parents);
  ASSERT_EQ(n, children.size());


  typedef const Individual * CI;
  set< pair< CI, CI > > pairs;

  for(int i = 0; i < n; i ++){
    CI mom = children[i]->parent(0);
    CI dad = children[i]->parent(1);
    pair<CI, CI> pair = make_pair(mom, dad);
    ASSERT_EQ(0, pairs.count(pair));
    pairs.insert(pair);
  }

  for(int i = 0; i < n; i++){
    delete children[i];
    delete parents[i];
  }
}
