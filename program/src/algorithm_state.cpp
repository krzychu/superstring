#include <algorithm_state.h>
#include <individual.h>
#include <algorithm>
#include <limits>

AlgorithmState::AlgorithmState(){
  iteration_ = 1;  
  processed_ ++;
  best_solution_ = std::numeric_limits<int>::max();
}


int AlgorithmState::iteration() const{
  return iteration_;
}


void AlgorithmState::inc_iteration() {
  iteration_++;
}


Population & AlgorithmState::population(){
  return population_;
}

int AlgorithmState::processed() const{
  return processed_;
}

void AlgorithmState::inc_processed(int delta){
  processed_ += delta;
}


const Population & AlgorithmState::population() const{
  return population_;
}


const int AlgorithmState::best() const{
	return best_solution_;
}


void AlgorithmState::set_best_if_better(const Individual & ind){
  best_solution_ = std::min(best_solution_, ind.cost());
}
