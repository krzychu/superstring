#ifndef SUPERSTRING_INSTANCE_H_
#define SUPERSTRING_INSTANCE_H_

#include <vector>

#include <algorithm_state.h>

class Instance{
  public:
    Instance(int num_machines, int num_tasks, int feasible_solution);
    
    virtual ~Instance();

    int evaluate(const Individual * individual) const; 
    std::vector<int> evaluate_all_insertions(const Individual * individual) const;

    void update_cost(AlgorithmState & state) const;

    int & operator() (int machine, int task);
    int operator() (int machine, int task) const;

    int num_machines() const;
    int num_tasks() const;
    int feasible_solution() const;
  
  private:
    Instance(const Instance & instance);
    const Instance & operator=(const Instance & other);

    int * data_;
    int num_machines_;
    int num_tasks_;
    int feasible_solution_;
};

#endif
