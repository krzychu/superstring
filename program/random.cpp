#include <instance.h>
#include <local_search.h>
#include <crossover.h>
#include <solver.h>

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <sstream>

const int file_name_idx = 1;
const int execution_idx = 2;
const int num_processed_idx = 3;




void save_results(int result, long long processed, int time, const char * filename, int execution_number)
{
  std::stringstream name;
  name << filename <<  "_" << execution_number << ".random";
  FILE * out = fopen(name.str().c_str(), "w");
  fprintf(out, "our solution: %d\n", result);
  fprintf(out, "time (s): %d\n", time);
  fprintf(out, "number of processed individuals: %lld\n", processed);
  fclose(out);
}


int main(int argc, char ** argv){

  // parse arguments
  if(argc != 4){
    printf("usage: ./random problem_file execution_number num_iterations\n");
    return -1;
  }

  const char * file_name = argv[file_name_idx];
  int execution_number = atoi(argv[execution_idx]);
  long long num_processed = atoll(argv[num_processed_idx]);

  // read instance
  Instance instance = Instance::load(file_name);

  int n = instance.num_words();
  int best_known = instance.superstring_length();
  int random_best = INT_MAX;
  Individual *x = new Individual(n);
  

  int start = time(0);
  for(int i = 0; i < num_processed; i++){
    x->randomize();
    int v = instance.evaluate(x);
    if(v < random_best) random_best = v;
  }

  int duration = time(0) - start;
  printf("time = %d\nbest found = %d\nbest known = %d\n", duration, random_best, best_known);

  save_results(random_best, num_processed, duration, file_name, execution_number);

  return 0;
}
