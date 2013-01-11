#ifndef ALGORITHM_STATE_H_
#define ALGORITHM_STATE_H_

#include <vector>
#include <population.h>

class AlgorithmState{
  public:
    AlgorithmState();
    int iteration() const; 
    void inc_iteration(); 

    unsigned long long int processed() const;
    void inc_processed(int delta = 1);
    Population & population();   
    const Population & population() const;

    const int best() const;
    void set_best_if_better(const Individual & Ind);

  private:
    Population population_;
    int iteration_;
    unsigned long long int processed_;
    int best_solution_;
};

#endif
