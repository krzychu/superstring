#include <instance.h>
#include <individual.h>
#include <benchmark_collection.h>
#include <parent_selector.h>
#include <crossover.h>
#include <mutation.h>
#include <replacement.h>
#include <adaptation.h>
#include <solver.h>
#include <termination.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(Instance, CalculatesIndividualCost){
  Individual ind("210");
  
  double cost[3][3] = {
    {3, 3, 2},
    {1, 4, 4},
    {5, 1, 1}
  };

  const int tasks = 3;
  const int machines = 3;
  const int solution = 16.0;

  Instance instance(machines, tasks, solution);
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      instance(m, t) = cost[m][t];

  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      ASSERT_EQ(cost[m][t], instance(m, t));
  
  ASSERT_FLOAT_EQ(solution, instance.evaluate(&ind));
}


TEST(Instance, CalculatesIndividualCost2){
  Individual ind("0123");
  
  double cost[4][4] = {
    {2, 3, 2, 1},
    {1, 1, 2, 1},
    {3, 2, 1, 1},
    {1, 1, 3, 1}
  };

  const int tasks = 4;
  const int machines = 4;
  const int solution = 14.0;

  Instance instance(machines, tasks, solution);
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      instance(m, t) = cost[m][t];
  ASSERT_FLOAT_EQ(solution, instance.evaluate(&ind));
}


TEST(Instance, CalcluatesAllInsertionsCost){
  Individual ind("0312");
  
  double cost[4][4] = {
    {2, 3, 2, 1},
    {1, 1, 2, 1},
    {3, 2, 1, 1},
    {1, 1, 3, 1}
  };

  const int tasks = 4;
  const int machines = 4;

  Instance instance(machines, tasks, 55);
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      instance(m, t) = cost[m][t];

  std::vector<int> is = instance.evaluate_all_insertions(&ind);
  ASSERT_EQ(tasks, is.size());
  
  for(int i = tasks - 1; i >= 0; i--){
    Individual clone = ind;  
    clone.insert(tasks - 1, i);
    ASSERT_EQ(instance.evaluate(&clone), is[i]);
  }
}


TEST(Instance, CalcluatesAllInsertionsCostBIG){
  const int tasks = 10;
  const int machines = 4;

  Instance instance(machines, tasks, 55);
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      instance(m, t) = rand() % 100;

 
  for(int t = 0; t < 100; t++){
    Individual ind(tasks);
    ind.randomize();
    std::vector<int> is = instance.evaluate_all_insertions(&ind);
    ASSERT_EQ(tasks, is.size());
    for(int i = tasks - 1; i >= 0; i--){
      Individual clone = ind;  
      clone.insert(tasks - 1, i);
      ASSERT_EQ(instance.evaluate(&clone), is[i]);
    }
  }
}



TEST(Instance, HandlesBigData){
  Individual ind(10000); 
  ind.randomize();
  Instance instance(100, 10000, 10000.0);
  instance.evaluate(&ind);
}

