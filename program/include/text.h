#ifndef TEXT_H_ 
#define TEXT_H_

#include <algorithm>
#include <utility>
#include <string>

template<class TextIterator, class OutputIterator>
void calculate_pi(const TextIterator & begin, const TextIterator & end, OutputIterator & out)
{
  out[0] = 0;   
  int q = 0;
  for(unsigned int i = 1; i < end - begin; i++){
    while(q > 0 && begin[q] != begin[i])
      q = out[q-1];
    if(begin[i] == begin[q])
      q++;
    out[i] = q;
  }
}


// returns (max q, overlap)
template<class PiItr, class RItr> 
std::pair<int, int> find_with_overlap
  (const std::string & pat, PiItr & pi, RItr begin, RItr end)
{
  unsigned int q = 0;
  unsigned int maxq = 0;
  while(begin != end){
    while(q == pat.size() || (q > 0 && *begin != pat[q]))
      q = pi[q - 1];
    
    if(pat[q] == *begin)
      q++;

    maxq = std::max(maxq, q);
    begin++;
  }

  return std::make_pair(maxq, q);
}

#endif
