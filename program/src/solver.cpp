#include <solver.h>

#include <vector>
#include <cstdio>
#include <cassert>
#include <cmath>


void Solver::run(
  const Instance & instance,
  const TerminationCondition & termination,
  int population_size
)
{
  const ReplacementStrategy & secondary_replacement = 
    * secondary_replacement_ptr;
  

  // generate random population
  for(int i = 0; i < population_size; i++){
    Individual * next = new Individual(instance.num_words());
    state.inc_processed();
    next->randomize();
    next->set_cost(instance.evaluate(next));
    state.population().add(next);
  }

  
  // evaluate individuals, sort them etc.
  update_population(instance);
  
  while( !termination(state) ){
    // select parents
    std::vector<const Individual *> parents = 
      parent_selector(state);

    // crossover 
    std::vector<Individual *> children = 
      crossover_strategy(state, parents);

    // mutation
    mutation_strategy(state, children);

    // evaluate children
    for(unsigned int i = 0; i < children.size(); i++){
      int c = instance.evaluate(children[i]); 
      state.inc_processed();
      children[i]->set_cost(c);
    }

    local_search(state, children);

    // replacement
    if(!secondary_replacement_ptr){
      replacement_strategy(state, children);
    }
    else{
      if(state.iteration() % secondary_period == 0)
        secondary_replacement(state, children);
      else
        replacement_strategy(state, children);
    }
    

    update_population(instance);

    immigration(state, instance);

    update_population(instance);

    // one more iteration...
    state.inc_iteration();

    printf("current iteration : %5d best: %d diversity : %lf processed : %llu  \n",
      state.iteration(), 
      state.population().best(), 
      state.population().diversity(),
      state.processed());
    fflush(stdout);

    save_iteration_info();
  }
}


void Solver::update_population(const Instance & instance){
  state.population().update_stats();
  adaptation.update(state);
}


const std::vector<IterationInfo> & Solver::iterations() const{
  return iterations_;
}


void Solver::save_iteration_info(){
  IterationInfo info;
  info.cost_mean = state.population().mean();
  info.cost_variance = state.population().variance();
  info.cost_sdev = sqrt(state.population().variance());
  info.best_cost = state.population().best();
  info.diversity = state.population().diversity();
  iterations_.push_back(info);
}


int Solver::solution() const{
  return std::min(state.best(), state.population().best());
}


void Solver::set_secondary_replacement
  (const ReplacementStrategy & rep, int period)
{
  secondary_replacement_ptr = &rep;
  secondary_period = period;
}


int Solver::processed() const{
  return state.processed();
}


int Solver::num_iterations() const{
  return state.iteration();
}
