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
template<class PatternIterator, class PiIterator, class TextIterator> 
std::pair<int, int> find_with_overlap
  (PatternIterator pattern_begin, 
   PatternIterator pattern_end, 
   PiIterator pi_begin, 
   TextIterator text_begin, 
   TextIterator text_end)
{
  unsigned int q = 0;
  unsigned int maxq = 0;
  const unsigned int pattern_size = pattern_end - pattern_begin;
  while(text_begin != text_end){
    while(q == pattern_size || (q > 0 && *text_begin != pattern_begin[q]))
      q = pi_begin[q - 1];
    
    if(pattern_begin[q] == *text_begin)
      q++;

    maxq = std::max(maxq, q);
    text_begin++;
  }

  return std::make_pair(maxq, q);
}

#endif
