#include <immigration.h>
#include <cstdio>

void ThresholdImmigrationOperator::operator()
  (AlgorithmState & st, const Instance & instance) const
{
  Population & P = st.population();
  if(P.dissipation() > threshold_){
    return; 
  }

  const int n = P.size() * amount_;
  replace_worst_with_random(n, st, instance);
}



void ProportionalImmigrationOperator::operator()
  (AlgorithmState & st, const Instance & instance) const
{
  double d = st.population().diversity();
  double amt = max_amount_ * (1 - d) + min_amount_ * d;

  const int n = st.population().size() * amt;
  replace_worst_with_random(n, st, instance);
}


void ImmigrationOperator::replace_worst_with_random(
  int n, AlgorithmState & st, const Instance & instance) const
{
  Population & P = st.population();

  // generate n random
  std::vector<Individual *> immigrants;
  for(int i = P.size() - n; i < P.size(); i++){
    Individual * next = new Individual(instance.num_tasks());
    st.inc_processed();
    next->randomize();
    next->set_cost(instance.evaluate(next));
    immigrants.push_back(next);
  }

  for(int i = 0; i < steps_; i++){
    local_search_(st, immigrants);
  }

  for(int i = 0; i < n; i++){
    delete P[i + P.size() - n];
    P.swap(i + P.size() - n, immigrants[i]);
  }
  
  P.update_stats();
}
