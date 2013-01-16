#include <instance.h>
#include <text.h>
#include <algorithm>
#include <iostream>

using namespace std;

void Instance::add_word(const std::string & str)
{
  words_.push_back(str);
  int * pi = new int[str.size()];
  pis_.push_back(pi);
  calculate_pi(str.begin(), str.end(), pi);
}



Instance::~Instance()
{
  for(unsigned int i = 0; i < pis_.size(); i++)
    delete [] pis_[i];
}



int Instance::evaluate(const Individual * ind) const
{
  const Individual & P = *ind;
  vector<char> ss;

  for(int i = 0; i < num_words(); i++){
    const std::string & w = words_[P[i]];
    int * pi = pis_[P[i]];
    
    pair<int, int> out = find_with_overlap(w, pi, ss.begin(), ss.end());
    const unsigned int match = out.first;
    const int overlap = out.second;

    if(match != w.size())
      copy(w.begin() + overlap, w.end(), back_inserter(ss)); 
  } 

  return ss.size();
}
