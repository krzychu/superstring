#ifndef IMMIGRANTS_H_
#define IMMIGRANTS_H_

#include <algorithm_state.h>
#include <instance.h>
#include <local_search.h>

class ImmigrationOperator{
  public:
    ImmigrationOperator(const LocalSearchStrategy & local, int steps) :
      local_search_(local), steps_(steps) {}

    virtual void operator() (AlgorithmState & st, const Instance & instance) const = 0;
  
  protected:
    void replace_worst_with_random(int n, AlgorithmState & st, 
        const Instance & instance) const;
    
  private:
    const LocalSearchStrategy & local_search_;
    int steps_;
};


class ThresholdImmigrationOperator : public ImmigrationOperator{
  public:
    ThresholdImmigrationOperator(
      double threshold, 
      double amount, 
      const 
      LocalSearchStrategy & local, 
      int steps) 
    : ImmigrationOperator(local, steps), threshold_(threshold), amount_(amount) {}

    void operator() (AlgorithmState & st, const Instance & instance) const;
  private:
    double threshold_;
    double amount_;
};


class ProportionalImmigrationOperator : public ImmigrationOperator{
  public:
    ProportionalImmigrationOperator(
      double min_amount, 
      double max_amount, 
      const LocalSearchStrategy & local,
      int steps
      ) 
    : ImmigrationOperator(local, steps), min_amount_(min_amount), max_amount_(max_amount){}

    void operator() (AlgorithmState & st, const Instance & instance) const;
  private:
    double min_amount_;
    double max_amount_;
};

#endif
