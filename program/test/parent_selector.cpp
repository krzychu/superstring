#include <parent_selector.h>

#include <gtest/gtest.h>
#include <cmath>


TEST(KBestSelector, WorksAsExpected){
  const int n = 10;
  AlgorithmState st;
  Population & pop = st.population();

  for(int i = 0; i < n ; i++){
    Individual * next = new Individual(10);   
    next->set_cost(100.0 * sin(5.0 * i));
    pop.add(next);
  }

  pop.update_stats();
  KBestSelector kbs(n / 2);

  std::vector<const Individual * > parents = kbs(st);
  ASSERT_EQ(n / 2, parents.size());

  for(int i = 0; i < n / 2; i++){
    for(int j = i + 1; j < n; j++){
      ASSERT_LT(*parents[i], *pop[j]); 
    } 
  }
}



TEST(RouletteSelector, WorksAsExpected){
  AlgorithmState st;
  Population & pop = st.population();

  const int n = 3;
  double probs[] = {0.1, 0.5, 0.4};

  for(int i = 0; i < n ; i++){
    Individual * next = new Individual(10);
    next->set_scaled_adaptation(probs[i]);
    pop.add(next);
  }
  
  const int reps = 1000000;
  RouletteSelector rs(reps);
  std::vector<const Individual * > parents = rs(st);
  ASSERT_EQ(reps, parents.size());
 
  int num[n];
  for(int i = 0; i < n; i++)
    num[i] = 0;

  for(int i = 0; i < reps; i++){
    for(int j = 0; j < n; j++)
      if(pop[j] == parents[i])
        num[j]++;
  }

  for(int i = 0; i < n; i++){
    double p = double(num[i]) / reps;
    ASSERT_GT(0.01, fabs(probs[i] - p));
  }
}
