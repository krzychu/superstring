#include <population.h>
#include <gtest/gtest.h>
#include <cmath>


TEST(Population, SortsItselfOnUpdate){
  Population p;
  const int n = 1000;
  for(int i = 0; i < n; i++){
    Individual * next = new Individual(10);
    next->set_cost(sin(10.0 * i));
    p.add(next);
  }
     
  p.update_stats();
  for(int i = 0; i < n - 1; i++){
    ASSERT_LE(*p[i], *p[i+1]);
  }
}


TEST(Population, CalculatesMeanAndVariance){
  int n = 4;
  double costs [] = {10, 5, 6, 7};
  Population p;
  for(int i = 0; i < n; i++){
    Individual * next = new Individual(10);
    next->set_cost(costs[i]);
    p.add(next);
  }

  p.update_stats();
  ASSERT_FLOAT_EQ(7, p.mean());
  ASSERT_FLOAT_EQ(3.5, p.variance());
}


TEST(Population, CalculatesAdaptationMeanAndVariance){
  int n = 4;
  int costs [] = {10, 5, 6, 7};
  Population p;
  for(int i = 0; i < n; i++){
    Individual * next = new Individual(10);
    next->set_cost(costs[i]);
    p.add(next);
  }

  p.update_stats();

  ASSERT_FLOAT_EQ(0.25, p.adaptation_mean());
  ASSERT_FLOAT_EQ(0.024305556, p.adaptation_variance());
}

