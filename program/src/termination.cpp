#include <termination.h>

NumIterationsCondition::NumIterationsCondition(int max_iterations){
  max_iterations_ = max_iterations;
}

bool NumIterationsCondition::operator() (const AlgorithmState & algo) const{
  return algo.iteration() > max_iterations_;
}
