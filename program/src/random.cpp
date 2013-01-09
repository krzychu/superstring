#include "random.h"

#include <algorithm>
  
int randint(int a, int b){
  return rand() % (b - a) + a; 
}


int randint(int a){
  return randint(0, a);
}


bool randbool(double true_prob){
  return double(rand()) / double(RAND_MAX) < true_prob;
}


double randu(){
  return double(rand()) / double(RAND_MAX);
}


std::pair<int, int> randpair(int n){
  int b = randint(1, n);
  int a = randint(0, b);
  return std::make_pair(a, b);
}


std::vector< std::pair<int, int> > randpart(int n){
  int * elems = new int[n];
  for(int i = 0; i < n; i++) 
    elems[i] = i;

  std::random_shuffle(elems, elems + n);

  std::vector< std::pair<int, int> > ans;
  for(int i = 0; i < n; i+= 2)
    ans.push_back(std::make_pair(elems[i], elems[i+1]));

  delete elems;
  return ans;
}


std::vector<int> randsubset(int n, int k){
  std::vector<int> xs(k);
  int p = -1;
  for(int i = 0; i < k; i++){
    xs[i] = randint(p + 1, n - k + i);
    p = xs[i];
  }
  return xs;
}
