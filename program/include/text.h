#ifndef TEXT_H_ 
#define TEXT_H_

#include <algorithm>


template<class T>
void calculate_pi(const T * in, int * out, int size){
  out[0] = 0;   
  int q = 0;
  for(int i = 1; i < size; i++){
    while(q > 0 && in[q] != in[i])
      q = out[q-1];
    if(in[i] == in[q])
      q++;
    out[i] = q;
  }
} 

#endif
