#include <adaptation.h>
#include <cmath>

void AdaptationScaler::update(AlgorithmState & state) const{
  Population & P = state.population(); 
  for(int i = 0; i < P.size(); i++){
    double d = scale(state, P[i]);  
    P[i]->set_scaled_adaptation(d);
  }
}


double IdentityScaler::scale(
  const AlgorithmState & state, 
  const Individual * individual) const
{
  return individual->adaptation();
}


double SimpleScaler::scale(
  const AlgorithmState & state, 
  const Individual * individual) const
{
  double worst = state.population().worst_adaptation();
  return individual->adaptation() - worst;
}


double SigmaScaler::scale(
  const AlgorithmState & state, 
  const Individual * individual) const
{
  double mean = state.population().adaptation_mean();
  double sdev = sqrt(state.population().adaptation_variance());
  return individual->adaptation() - mean + c_*sdev;
}


double RankingScaler::scale(
  const AlgorithmState & state, 
  const Individual * individual) const
{
  return 0;
}


void RankingScaler::update(AlgorithmState & state) const{
  Population & P = state.population();
  double mu = P.size();
  double beta = num_best_offsprings_;
  double alpha = 2.0 - beta;
  for(int i = 0; i < P.size(); i++){
    double rank = mu - i - 1;
    P[i]->set_scaled_adaptation( 
      (alpha + rank / (1 - mu) * (2*beta - 2)) / mu) ;
  }
}

