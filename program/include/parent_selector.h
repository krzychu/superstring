#ifndef PARENT_SELECTOR_H_
#define PARENT_SELECTOR_H_

#include <vector>
#include <individual.h>
#include <population.h>
#include <algorithm_state.h>

class ParentSelector{
  public:
    virtual ~ParentSelector(){}
    virtual std::vector<const Individual *> 
      operator() (const AlgorithmState & state) const = 0;
};


class KBestSelector : public ParentSelector{
  public:
    KBestSelector(int k): k_(k) {} 
    virtual std::vector<const Individual *> 
      operator() (const AlgorithmState & state) const;

  private:
    int k_;
};


class RouletteSelector : public ParentSelector{
  public:
    RouletteSelector(int k): k_(k) {}

    virtual std::vector<const Individual *> 
      operator() (const AlgorithmState & state) const;
  
  private:
    int k_;
};


#endif
