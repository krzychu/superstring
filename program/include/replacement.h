#ifndef REPLACEMENT_H_
#define REPLACEMENT_H_

#include <algorithm_state.h>

class ReplacementStrategy{
  public:
    virtual ~ReplacementStrategy(){}

    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0; 
};



class BestOfReplacement : public ReplacementStrategy{
  public:
    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;
};


class FamilyReplacement : public ReplacementStrategy{
  public:
    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;

  public:
    void add_with_cost(std::vector< std::pair<int, Individual *> > & , 
      Individual * n) const;
};



#endif
