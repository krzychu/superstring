#include <stat_utils.h>

double sq(double x){
  return x * x;
}


std::pair<double, double> mean_and_variance(const double * xs, int n){
  double mean = 0;
  for(int i = 0; i < n; i++)
    mean += xs[i];
  mean /= n;

  double variance = 0;
  for(int i = 0; i < n; i++)
    variance += sq(mean - xs[i]);
  variance /= n;

  return std::make_pair(mean, variance);
}
