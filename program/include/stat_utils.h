#ifndef STAT_UTILS_H_
#define STAT_UTILS_H_

#include <utility>

double sq(double x);

std::pair<double, double> mean_and_variance(const double* xs, int n);

#endif
