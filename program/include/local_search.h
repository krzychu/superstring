#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <individual.h>
#include <algorithm_state.h>
#include <cstdlib>
#include <instance.h>


class LocalSearch{
  public:
    LocalSearch(const Instance & instance)
      : instance_(instance) {};

    struct Result{
      Individual individual;
      int num_processed;

      Result(const Individual & f, int n) 
        : individual(f), num_processed(n) {}

      Result() : num_processed(0) {}
    };

    virtual Result operator() (const Individual * Ind) const = 0;
  
  protected:
    const Instance & instance_;
};



class TranspositionSearch : public LocalSearch{
  public:
    TranspositionSearch(const Instance & instance)
      : LocalSearch(instance) {}

    Result operator() (const Individual * a) const;
};


class InsertionSearch : public LocalSearch{
  public:
    InsertionSearch(const Instance & instance)
      : LocalSearch(instance) {}

    Result operator() (const Individual * a) const;
};








class LocalSearchStrategy{
  public:
    LocalSearchStrategy(const LocalSearch & ls)
      : local_search_(ls) {}
    
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0;
 
  protected:
    const LocalSearch & local_search_;
};


class LaziestStrategy : public LocalSearchStrategy{
  public:
    LaziestStrategy(const LocalSearch & ls)
      : LocalSearchStrategy(ls) {}

    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const {}
};


class SimpleStrategy : public LocalSearchStrategy{
  public:
    SimpleStrategy(const LocalSearch & local) :
      LocalSearchStrategy(local) {}

    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;
};


class ParallelSearchStrategy : public LocalSearchStrategy{
  public: 
    ParallelSearchStrategy(const LocalSearch & local) 
      : LocalSearchStrategy(local) {}

    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;
};

#endif
