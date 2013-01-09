#include <individual.h>
#include <cstring>
#include <algorithm>


Individual::Individual(int size)
  : std::vector<int>(size) 
{
  parents_[0] = 0;
  parents_[1] = 0;
}


Individual::Individual(const char * code)
  : std::vector<int>(strlen(code))
{
  int n = strlen(code);
  for(int i = 0; i < n; i++){
    at(i) = code[i] - '0'; 
  }
}


bool Individual::operator == (const Individual & other) const{
  for(unsigned int i = 0; i < size(); i++){
    if(at(i) != other[i])
      return false;
  }
  return true;
}


bool Individual::valid() const{
  bool was[size()];
  std::fill(was, was + size(), false);
  for(unsigned int i = 0; i < size(); i++){
    if(was[at(i)])
      return false;
    was[at(i)] = true;
  }

  return true;
}



std::ostream & operator << 
  (std::ostream & out, const Individual & p)
{
  for(unsigned int i = 0; i < p.size(); i ++)
    out << p[i] << " ";
  out << std::endl;
  return out;
}


void Individual::swap(int i, int j){
  std::swap(at(i), at(j));
}


void  Individual::randomize(){
  for(unsigned int i = 0; i < size(); i++)
    at(i) = i;
  std::random_shuffle(begin(), end());
}


int Individual::cost() const{
  return cost_;
}

void Individual::set_cost(int cost){
  cost_ = cost;
}

double Individual::adaptation() const{
  return adaptation_;
}

void Individual::set_adaptation(double adaptation){
  adaptation_ = adaptation;
}

double Individual::scaled_adaptation() const{
  return scaled_adaptation_;
}

void Individual::set_scaled_adaptation(double v) {
  scaled_adaptation_ = v;
}

bool Individual::operator < (const Individual & other) const{
  return cost_ < other.cost_;
}

bool Individual::operator <= (const Individual & other) const{
  return cost_ <= other.cost_;
}


void Individual::insert(int elemIdx, int i){
  Individual & t = *this;
  int x = t[elemIdx];
  if(elemIdx > i){
    for(int j = elemIdx; j > i; j--){
      t[j] = t[j-1];
    }
    t[i] = x;
  }
  if(elemIdx < i){
    for(int j = elemIdx; j < i; j++){
      t[j] = t[j+1];
    }
    t[i] = x;
  }
}


const Individual * Individual::parent(int i) const{
  return parents_[i];
}


void Individual::set_parents(const Individual * a, const Individual * b)
{
  parents_[0] = a;
  parents_[1] = b;
}
