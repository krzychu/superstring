#include <replacement.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <cassert>
#include <iostream>


void BestOfReplacement::operator() 
  (AlgorithmState & state, std::vector<Individual *> & children) const
{
  using std::make_pair;

  std::vector< std::pair<int, Individual *> > pairs;
  
  for(unsigned int i = 0; i < children.size(); i++)
    pairs.push_back(make_pair(children[i]->cost(), children[i]));

  Population & p = state.population();
  for(int i = 0; i < p.size(); i++)
    pairs.push_back(make_pair(p[i]->cost(), p[i]));

  std::sort(pairs.begin(), pairs.end());
  
  const unsigned int n = p.size();
  p.clear();

  for(unsigned int i = 0; i < pairs.size(); i++){
    Individual * individual = pairs[i].second;
  
    if(i < n)
      p.add(individual);
    else
      delete individual;
  }
}


void FamilyReplacement::add_with_cost(
  std::vector< std::pair<int, Individual *> > & v, Individual * n) const
{
  assert(n->valid());
  v.push_back(std::make_pair(n->cost(), n)); 
}



void FamilyReplacement::operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const
{
  using namespace std;
  typedef Individual * IP;
  typedef map< pair<IP, IP>, vector<IP> > SYF;

  SYF families;
 
  set< IP > single;
  Population & p = state.population();
  for(int i = 0; i < p.size(); i++)
    single.insert(p[i]);
  p.clear();

  for(unsigned int i = 0; i < children.size(); i++){
    IP m = const_cast<IP>(children[i]->parent(0));
    IP d = const_cast<IP>(children[i]->parent(1));
    single.erase(m);
    single.erase(d);
    IP u = min(m, d);
    IP v = max(m, d);
    assert(u < v);
    families[make_pair(u, v)].push_back(children[i]);
  }

  for(set<IP>::iterator i = single.begin(); i != single.end(); i++){
    p.add(*i); 
  }


  for(SYF::iterator i = families.begin(); i != families.end(); i++){
    assert(i->second.size() == 2);
    vector< pair< int, IP> > family; 
    add_with_cost(family, i->second[0]);
    add_with_cost(family, i->second[1]);
    add_with_cost(family, i->first.first);
    add_with_cost(family, i->first.second);
    std::sort(family.begin(), family.end());
    
    p.add(family[0].second);
    p.add(family[1].second);

    delete family[2].second;
    delete family[3].second;
  }
}
