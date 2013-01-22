#include <cstdio>
#include <sstream>

#include <instance.h>
#include <heuristic.h>


int main(int argc, char ** argv)
{
  if(argc != 2){
    printf("usage: ./heuristic file_name\n");
    return -1;
  }

  const char * file_name = argv[1];
  Instance instance  = Instance::load(file_name);
  
  Heuristic solver(instance);

  int start = time(0);
  int solution = solver.run();
  int duration = time(0) - start;

  printf("solution : %d\n", solution); 


  std::stringstream name;
  name << file_name << ".heuristic";
  FILE * out = fopen(name.str().c_str(), "w");
  fprintf(out, "heuristic solution: %d\n", solution);
  fprintf(out, "time: %d\n", duration);
  fclose(out);

  return 0;
}
