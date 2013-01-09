#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>
#include <utility>
#include <vector>


// returns random integer from range [a, b)
int randint(int a, int b);

// returns random integer from range [0, a)
int randint(int a);

// returns true with probability true_prob
bool randbool(double true_prob);

// returns uniform random from [0, 1)
double randu();

// returns pair <a, b>   0 <= a < b < n
std::pair<int, int> randpair(int n);

// randomly partitions set of n elements into two
// even parts
std::vector< std::pair<int, int> > randpart(int n);

// returns random k element subset of 0..n-1
std::vector<int> randsubset(int n, int k);


#endif
