#include <cstdio>

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
  printf("solution : %d\n", solver.run()); 

  return 0;
}
