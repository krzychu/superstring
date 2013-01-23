#include <heuristic.h>
#include <text.h>
#include <find_union.h>

#include <algorithm>
#include <vector>
#include <cstdio>


struct Overlap
{
  int len;
  int left;
  int right;

  Overlap(int o, int l, int r)
    : len(o), left(l), right(r) {}

  bool operator < (const Overlap & other) const
  {
    return len < other.len; 
  }
};


const char * b2s(bool x)
{
  return x ? "true" : "false";
}


int Heuristic::run() const
{
  const int n = instance_.num_words();
  std::vector<Overlap> overlaps;

  std::vector<bool> prefix_used(n, false);
  std::vector<bool> suffix_used(n, false);
  std::vector<int> next(n, -1);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(i == j)
        continue;
      overlaps.push_back(Overlap(instance_.ov(i, j), i, j));
    }
  }

  std::sort(overlaps.begin(), overlaps.end());
  FindUnion fu(n);
  int size = 0;


  while(!overlaps.empty()){
    Overlap cur = overlaps.back();
    overlaps.pop_back();

    if(prefix_used[cur.right] || suffix_used[cur.left])
      continue;

    if(fu.find(cur.right) == fu.find(cur.left))
      continue;
    
    prefix_used[cur.right] = true;    
    suffix_used[cur.left] = true;
    next[cur.left] = cur.right;
    fu.sum(cur.left, cur.right);
    size += instance_[cur.left].size() - cur.len;
  }
  
  return size; 
}
