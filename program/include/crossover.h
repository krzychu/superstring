#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include <individual.h>
#include <algorithm_state.h>
#include <utility>


class Crossover{
  public:
    typedef std::pair<Individual, Individual> Result;

    virtual Result operator() 
      (const Individual * a, const Individual * b) const = 0;
};


class OX : public Crossover{
  public:  
    virtual Result operator() 
      (const Individual * a, const Individual * b) const;

    Individual cross(int a, int b, 
      const Individual * mom, const Individual * dad) const;
};


class PMX : public Crossover{
  public:  
    PMX(int max_segment = 100000000);

    virtual Result operator() 
      (const Individual * a, const Individual * b) const;

    Individual cross(int a, int b, 
      const Individual * mom, const Individual * dad) const;
  
  private:
    int max_seg_;  
};


class UX : public Crossover{
  public: 
    UX(int num_exchanged);
    
    virtual Result operator() 
      (const Individual * a, const Individual * b) const;
    
    Individual cross(const std::vector<int> & ind, 
      const Individual * mom, const Individual * dad) const;
  
  private:
    double num_exchanged_;
};


class Composition : public Crossover{
  public: 
    
    virtual Result operator() 
      (const Individual * a, const Individual * b) const;
    
    Individual cross(const Individual * mom, const Individual * dad) const;
};













class CrossoverStrategy{
  public:
    CrossoverStrategy(const Crossover & cross) : cross_(cross) {}

    virtual std::vector<Individual *> operator() (
      const AlgorithmState & state, 
      std::vector<const Individual *> & parents) const = 0;

  protected:
    const Crossover & cross_;
};


class RandomCrossoverStrategy : public CrossoverStrategy{
  public:
    RandomCrossoverStrategy(const Crossover & cross) 
      : CrossoverStrategy(cross) {}
    
    virtual std::vector<Individual *> operator() (
      const AlgorithmState & state, 
      std::vector<const Individual *> & parents) const;
};


class RandomPairCrossoverStrategy : public CrossoverStrategy{
  public:
    RandomPairCrossoverStrategy(const Crossover & cross) 
      : CrossoverStrategy(cross) {}


    virtual std::vector<Individual *> operator() (
      const AlgorithmState & state, 
      std::vector<const Individual *> & parents) const;
};


#endif
