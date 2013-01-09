#include <crossover.h>
#include <random.h>
#include <algorithm>
#include <cassert>


std::vector<Individual *> RandomCrossoverStrategy::operator() (
  const AlgorithmState & state, 
  std::vector<const Individual *> & parents) const
{
  std::vector<Individual *> children;
  const Population & P = state.population();

  for(int i = 0; i < P.size(); i++){
    std::pair<int, int> ab = randpair(P.size());
    if(randbool(0.5))
      std::swap(ab.first, ab.second);

    Crossover::Result r = cross_(P[ab.first], P[ab.second]); 
    Individual * a = new Individual(r.first);
    Individual * b = new Individual(r.second);
    children.push_back(a);
    children.push_back(b);
  }

  return children;
}




std::vector<Individual *> RandomPairCrossoverStrategy::operator()(
  const AlgorithmState & state, 
  std::vector<const Individual *> & parents) const
{
  assert( parents.size() % 2 == 0 );
  std::random_shuffle(parents.begin(), parents.end());
  std::vector<Individual *> children;

  for(unsigned int i = 0; i < parents.size() / 2; i++){
    const Individual * mom = parents[2*i];
    const Individual * dad = parents[2*i + 1];
    Crossover::Result r = cross_(mom, dad);
    Individual * a = new Individual(r.first);
    Individual * b = new Individual(r.second);

    assert(mom != dad);
    assert(mom == a->parent(0));
    assert(dad == a->parent(1));
    assert(mom == b->parent(1));
    assert(dad == b->parent(0));
    assert(a != b);

    children.push_back(a);
    children.push_back(b);
  }

  return children;
}
