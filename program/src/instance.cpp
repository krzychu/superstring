#include <instance.h>
#include <algorithm>
#include <cstdio>


Instance::Instance(int m, int t, int s){
  num_machines_ = m;
  num_tasks_ = t;
  feasible_solution_ = s;
  data_ = new int[m * t];
  std::fill(data_, data_ + m * t, 0);
}


Instance::~Instance(){
  delete [] data_;
}


int Instance::num_machines() const{
  return num_machines_;
}


int Instance::num_tasks() const{
  return num_tasks_;
}

int Instance::feasible_solution() const{
  return feasible_solution_;
}

int & Instance::operator() (int machine, int task){
  return data_[num_tasks_ * machine + task];
}


int Instance::operator() (int machine, int task) const{
  return data_[num_tasks_ * machine + task];
}


void print_mat(int rows, int cols, int ** mat){
  for(int r = 0; r < rows; r++){
    for(int c = 0; c < cols; c++)
      printf("%5d", mat[r][c]);
    printf("\n");
  }
}


void Instance::update_cost(AlgorithmState & state) const{
  Population & P = state.population();
  for(int i = 0; i < P.size(); i++){
    int cost = evaluate(P[i]);
    P[i]->set_cost(cost);
  }
}


int Instance::evaluate(const Individual * individual) const{
  const Instance & T = *this;
  const Individual & p = *individual;
 
  int ** e = new int * [num_machines_];
  for(int i = 0; i < num_machines(); i++)
    e[i] = new int [num_tasks_];

  e[0][0] = T(0, p[0]);
  for(int t = 1; t < num_tasks_; t++)
    e[0][t] = e[0][t-1] + T(0, p[t]);
  for(int m = 1; m < num_machines_; m++)
    e[m][0] = e[m-1][0] + T(m, p[0]);
  
  for(int m = 1; m < num_machines_; m++)
    for(int t = 1; t < num_tasks_; t++)
      e[m][t] = std::max(e[m-1][t], e[m][t-1]) + T(m, p[t]);

  int cost = e[num_machines_ - 1][num_tasks_ - 1];

  for(int i = 0; i < num_machines(); i++)
    delete [] e[i];
  delete [] e;

  return cost;
}


std::vector<int> 
Instance::evaluate_all_insertions(const Individual * individual) const
{
  const Instance & T = *this;

  int ** e = new int * [num_machines_];
  int ** q = new int * [num_machines_];
  int ** f = new int * [num_machines_];
  for(int i = 0; i < num_machines(); i++){
    e[i] = new int [num_tasks_];
    q[i] = new int [num_tasks_];
    f[i] = new int [num_tasks_];
  }

  // prepare individual
  const int n = num_tasks_ - 1;
  Individual p(*individual);

  // E
  e[0][0] = T(0, p[0]);
  for(int m = 1; m < num_machines_; m++)
    e[m][0] = e[m-1][0] + T(m, p[0]);

  for(int t = 1; t < n; t++)
    e[0][t] = e[0][t-1] + T(0, p[t]);

  for(int m = 1; m < num_machines_; m++)
    for(int t = 1; t < n; t++)
      e[m][t] = std::max(e[m-1][t], e[m][t-1]) + 
        T(m, p[t]);
 
  // Q
  const int lastm = num_machines_ - 1;
  const int lastt = n - 1;
  q[lastm][lastt] = T(lastm, p[lastt]);
  for(int m = lastm; m >= 0; m--)
    q[m][lastt+1] = 0;
  for(int t = lastt - 1; t >= 0; t--)
    q[lastm][t] = q[lastm][t+1] + T(lastm, p[t]);
  for(int m = lastm - 1; m >= 0; m--)
    for(int t = lastt; t >= 0; t--)
      q[m][t] = std::max(q[m+1][t], q[m][t+1]) + T(m, p[t]);
 
    
  // F
  f[0][0] = T(0, p[n]);
  for(int m = 1; m < num_machines_; m++)
    f[m][0] = f[m-1][0] + T(m, p[n]);
  for(int t = 1; t <= n; t++)
    f[0][t] = e[0][t-1] + T(0, p[n]);
  for(int m = 1; m < num_machines_; m++)
    for(int t = 1; t <= n; t++)
      f[m][t] = std::max(f[m-1][t], e[m][t-1]) + T(m, p[n]);


/*
  // print debug info
  for(int m = 0; m < num_machines_; m++){
    for(int t = 0; t <= n; t++)
      printf("%5d", T(m, p[t]));
    printf("\n");
  }
  printf("e:\n");
  print_mat(num_machines_, n, e);
  printf("q:\n");
  print_mat(num_machines_, n, q);
*/



  // check all possible places to insert
  std::vector<int> costs;
  for(int t = 0; t <= n; t++){
    int cost = 0;
    for(int m = 0; m < num_machines_; m++)
      cost = std::max(cost, f[m][t] + q[m][t]);
    costs.push_back(cost);
  }

  for(int i = 0; i < num_machines(); i++){
    delete [] e[i];
    delete [] q[i];
    delete [] f[i];
  }
  delete [] e;
  delete [] q;
  delete [] f;

  return costs;
}

