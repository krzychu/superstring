#ifndef TERMINATION_CONDITION_H_
#define TERMINATION_CONDITION_H_

#include <algorithm_state.h>

class TerminationCondition{
  public:
    virtual ~TerminationCondition(){};
    virtual bool operator() (const AlgorithmState & state) const = 0;
};


class NumIterationsCondition : public TerminationCondition{
  public:
    NumIterationsCondition(int max_iterations);
    bool operator() (const AlgorithmState & state) const;

  private:
    int max_iterations_;
};

#endif
