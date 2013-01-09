#ifndef ADAPTATION_H_
#define ADAPTATION_H_

#include <algorithm_state.h>

class AdaptationScaler{
  public:
    virtual void update(AlgorithmState & state) const;
    virtual double scale(const AlgorithmState & state, 
            const Individual * individual) const = 0;
    virtual ~AdaptationScaler() {};
};


class IdentityScaler : public AdaptationScaler{
  public:
    virtual double scale(const AlgorithmState & state, 
            const Individual * individual) const;
};


class SimpleScaler : public AdaptationScaler{
  public:
    virtual double scale(const AlgorithmState & state, 
            const Individual * individual) const;
};


class SigmaScaler : public AdaptationScaler{
  public:
    SigmaScaler(double c) : c_(c) {}

    virtual double scale(const AlgorithmState & state, 
            const Individual * individual) const;
  private:
    double c_;
};


class RankingScaler : public AdaptationScaler{
  public:
    RankingScaler(double num_best_offsprings)
      : num_best_offsprings_(num_best_offsprings) {}

    virtual void update(AlgorithmState & state) const;

    virtual double scale(const AlgorithmState & state, 
            const Individual * individual) const;

  private:
    double num_best_offsprings_;
};




#endif
