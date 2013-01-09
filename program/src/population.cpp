#include <population.h>
#include <algorithm>
#include <stat_utils.h>
#include <iostream>
#include <cmath>
#include <set>
#include <cstdio>



Population::Population(){
  needs_update_ = false;   
  mean_ = 0;
  variance_ = 0;
}


void Population::add(Individual * individual){
  needs_update_ = true;
  individuals_.push_back(individual);
}

void Population::swap(int i, Individual * individual){
  individuals_[i] = individual;
}


void Population::clear(){
  individuals_.clear();
}


bool ind_ptr_cmp(const Individual * a, const Individual * b){
  return a->cost() < b->cost();
}


inline double sq(double x){
  return x * x;
}


struct IndDiffCmp{
  bool operator () (const Individual * a, const Individual * b) const{
    return std::lexicographical_compare(a->begin(), a->end(), b->begin(), b->end()); 
  }
};



void Population::update_stats(){
  if(!size())
    return;

  std::sort(individuals_.begin(), individuals_.end(), ind_ptr_cmp);
 
  best_ = individuals_.front()->cost();
  worst_ = individuals_.back()->cost();


  double * tmp = new double[size()];

  for(int i = 0; i < size(); i++) tmp[i] = individuals_[i]->cost();
  std::pair<double, double> mav = mean_and_variance(tmp, size());
  mean_ = mav.first;
  variance_ = mav.second;

  double scale = size() * (mean_ - worst_);
  if(scale == 0){
    adaptation_mean_ = 1.0 / size();
    adaptation_variance_ = 0;
    for(int i = 0; i < size(); i++)
      individuals_[i]->set_adaptation(adaptation_mean_);
  }   
  else{
    for(int i = 0; i < size(); i++){
      double a = (individuals_[i]->cost() - worst_) / scale; 
      tmp[i] = a;
      individuals_[i]->set_adaptation(a);
    }
    mav = mean_and_variance(tmp, size());
    adaptation_mean_ = mav.first;
    adaptation_variance_ = mav.second;
  }

  std::set<Individual *, IndDiffCmp> different;
  for(int i = 0; i < size(); i++){
    different.insert(individuals_[i]);
  }

  diversity_ = double(different.size()) / size();

  needs_update_ = false;
  delete [] tmp;
}


double Population::mean() const{
  return mean_; 
}


double Population::variance() const{
  return variance_;
}

double Population::diversity() const{
  return diversity_;
}


double Population::dissipation() const{
  return sqrt(variance_) / mean_;
}

int Population::best() const{
  return individuals_[0]->cost();
}


int Population::worst() const{
  return individuals_.back()->cost();
}


int Population::size() const{
  return individuals_.size();
}


bool Population::needs_update() const{
  return needs_update_;
}


double Population::adaptation_mean() const{
  return adaptation_mean_;
}


double Population::adaptation_variance() const{
  return adaptation_variance_;
}


double Population::worst_adaptation() const{
  return individuals_[size() - 1]->adaptation();
}


const Individual * Population::operator[] (int i ) const{
  return individuals_[i];
}


Individual * Population::operator[] (int i ){
  return individuals_[i];
}


Population::~Population(){
  for(int i = 0; i < size(); i++){
    delete individuals_[i]; 
  }
}


