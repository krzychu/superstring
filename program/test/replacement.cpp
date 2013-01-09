#include <gtest/gtest.h>
#include <replacement.h>
#include <parent_selector.h>
#include <crossover.h>

const int population_size = 100;
const int num_parents = 50;
const int num_tasks = 20;

TEST(FamilyReplacement, WorksAsExpected){
  AlgorithmState state;

  for(int i = 0; i < population_size; i++){
    Individual * next = new Individual(num_tasks);
    next->randomize();
    next->set_cost(i + population_size);
    state.population().add(next);
  }

  state.population().update_stats();
  
  KBestSelector kbs(num_parents);
  std::vector<const Individual *> parents = kbs(state);

  PMX pmx;
  RandomPairCrossoverStrategy rpcs(pmx);

  std::vector<Individual *> children = rpcs(state, parents);
  for(unsigned int i = 0; i < children.size(); i++)
    children[i]->set_cost(i);

  FamilyReplacement fr;
  fr(state, children);

  ASSERT_EQ(population_size, state.population().size());

  // all children should be in population
  for(int i = 0; i < num_parents; i++){
    bool found = false;
    for(int j = 0; j < population_size; j++){
      if(state.population()[j] == children[i]){
        found = true;
        break;
      }
    }

    ASSERT_TRUE(found);
  }
}
