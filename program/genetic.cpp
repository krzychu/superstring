#include <instance.h>
#include <local_search.h>
#include <crossover.h>
#include <solver.h>
#include <replacement.h>

#include <cstdio>
#include <cstdlib>
#include <sstream>

const int file_name_idx = 1;
const int execution_idx = 2;
const int num_iterations_idx = 3;
const int operator_idx = 4;

// program parameters
int population_size = 4000;
int num_parents = 4000;

const double max_immigrant_ratio = 0.3;
const int num_immigrant_search_iterations = 5;
const double mutation_probability = 0.05;








void save_results(const Solver & solver, int time, const char * filename, int execution_number, std::string operator_name)
{
  std::stringstream name;
  name << filename <<  "_" << execution_number << ".genetic";
  FILE * out = fopen(name.str().c_str(), "w");
  fprintf(out, "our solution: %d\n", solver.solution());
  fprintf(out, "time (s): %d\n", time);
  fprintf(out, "number of processed individuals: %lld\n", solver.processed());
  fprintf(out, "crossover operator: %s\n", operator_name.c_str());
  fclose(out);
}


void save_progress(const std::vector<IterationInfo> & iterations, 
  const char * file_name, int execution_number)
{
  std::stringstream sname;
  sname <<  file_name << "_" << execution_number << ".progress";
  std::string name = sname.str();
  FILE * out = fopen(name.c_str(), "w");
  fprintf(out, "# iteration best mean sdev diversity\n");
  for(unsigned int i = 0; i < iterations.size(); i++){
    fprintf(out, "%d %lf %lf %lf %lf\n", 
      i,
      iterations[i].best_cost, 
      iterations[i].cost_mean, 
      iterations[i].cost_sdev,
      iterations[i].diversity);
  }
  fclose(out);

  const char * titles[] = {"Best", "Mean", "Sdev"};
  const char * colors[] = {"red", "green", "blue"};

  sname << ".gplt";
  out = fopen(sname.str().c_str(), "w");
  fprintf(out, "plot ");
  for(int i = 0; i < 3; i++){
    fprintf(out, "\"%s\" using 1:%d with lines linecolor rgb \"%s\" title \"%s\"",
      name.c_str(),
      i + 2, 
      colors[i],
      titles[i]
      );

    if(i != 2)
      fprintf(out, ", ");
  }
  fprintf(out, ";\npause -1\n");
  fclose(out);
}







int main(int argc, char ** argv){

  // parse arguments
  if(argc != 5){
    printf("usage: ./genetic problem_file execution_number num_iterations crossover_operator\n");
    return -1;
  }

  const char * file_name = argv[file_name_idx];
  int execution_number = atoi(argv[execution_idx]);
  int num_iterations = atoi(argv[num_iterations_idx]);
  std::string operator_name(argv[operator_idx]);
  // read instance
  Instance instance = Instance::load(file_name);
  instance.preprocess();
  
  // create solver
  NumIterationsCondition termination_condition(num_iterations);


  Crossover *crossover_operator = 0;
  if((operator_name == "ux")) {
    crossover_operator = new UX(5);
  }

  if((operator_name == "pmx")) {
    crossover_operator = new PMX();
  }

  if((operator_name == "ox")) {
    crossover_operator = new OXimproved(instance);
  }

  if((operator_name == "composition")) {
    crossover_operator = new Composition();
  }


  RandomPairCrossoverStrategy crossover_strategy(*crossover_operator);

  KBestSelector parent_selector(num_parents);
  IdentityScaler scaler;

  TranspositionSearch local_search_method(instance);
  ParallelSearchStrategy local_search_strategy(local_search_method);

  FamilyReplacement replacement_strategy;
 
  RandomPermutationCrossover mutation; 
	RandomMutationStrategy mutation_strategy(mutation, mutation_probability);

  ProportionalImmigrationOperator immigration(
    0, 
    max_immigrant_ratio, 
    local_search_strategy, 
    num_immigrant_search_iterations);

  Solver solver(
    parent_selector, 
    crossover_strategy, 
    mutation_strategy, 
    replacement_strategy, 
    scaler, 
    local_search_strategy, 
    immigration
  );

  int start = time(0);
  solver.run(instance, termination_condition, population_size);
  int duration = time(0) - start;
  printf("time = %d\n", duration);

  save_progress(solver.iterations(), file_name, execution_number);
  save_results(solver, duration, file_name, execution_number, operator_name);

  delete crossover_operator;

  return 0;
}
