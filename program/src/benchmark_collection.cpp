#include <benchmark_collection.h>
#include <cstdio>
#include <cassert>
#include <exception>


IntStream::IntStream(FILE * f){
  f_ = f;
  read_ = 0;
  fscanf(f_, "%d", &size_);
}


IntStream & IntStream::operator >> (int & dst){
  fscanf(f_, "%d", &dst);
  read_++;
  assert(read_ <= size_);
  return * this;
}


bool IntStream::empty() const{
  return read_ >= size_;
}


BenchmarkCollection::~BenchmarkCollection(){
  for(int i = 0; i < size(); i++)
    delete instances_[i];
}


int BenchmarkCollection::size() const{
  return instances_.size();
}


void BenchmarkCollection::load(const char * path){
  instances_.clear(); 
  FILE * f = fopen(path, "r");
  if(!f)
    throw std::exception();
  IntStream is(f);

  while(!is.empty())
    read_instance(is);
  
  fclose(f);
}


void BenchmarkCollection::read_instance(IntStream & in){
  int tasks, machines, seed, upper_bound, lower_bound; 
  in >> tasks >> machines >> seed >> upper_bound >> lower_bound;
  
  Instance * inst = new Instance(machines, tasks, upper_bound);
  Instance & instance = * inst;
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      in >> instance(m, t); 
 
  instances_.push_back(inst);
}


const Instance & BenchmarkCollection::instance(int i) const{
  return * instances_[i];
}
