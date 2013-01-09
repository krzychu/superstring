#ifndef MUTATION_H_
#define MUTATION_H_

#include <individual.h>
#include <algorithm_state.h>
#include <crossover.h>

class Mutation{
  public:
	  virtual void operator() 
        (Individual * a) const = 0;

    virtual ~Mutation(){};
};


class RandomPermutationCrossover : public Mutation{
  public:  
    RandomPermutationCrossover(double constancy = 0.75);
    virtual void operator() (Individual * a) const;

  private:
    double Constancy;
};


class PermutationShift : public Mutation{
  public:  
    PermutationShift(double shift = 0.15);
    virtual void operator() (Individual * a) const;
  
  private:
    double Shift;
};



class MutationStrategy{
  public:
    MutationStrategy(Mutation & mutation) : mutation_(mutation) {}

    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0;

  protected:
    Mutation & mutation_;
};


class RandomMutationStrategy : public MutationStrategy{
  public:
    RandomMutationStrategy(Mutation & mutation, double p) :
      MutationStrategy(mutation), p_(p) {}

    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;
  
  private:
    double p_;
};


class ProportionalMutationStrategy : public MutationStrategy{
  public:
    ProportionalMutationStrategy(Mutation & mutation, double min_prob, double max_prob) :
      MutationStrategy(mutation),
			min_prob_(min_prob),
			max_prob_(max_prob)
		{}

    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;
  
  private:
		double min_prob_;
		double max_prob_;
};

#endif
  

