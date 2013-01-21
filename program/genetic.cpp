#include <cstdlib>
#include <instance.h>
#include <cstdio>

const int file_name_idx = 1;
const int execution_idx = 2;

int main(int argc, char ** argv){

  // parse arguments
  if(argc != 3){
    printf("usage: ./genetic problem_file execution_number");
    return -1;
  }

  const char * file_name = argv[file_name_idx];
  int execution_number = atoi(argv[execution_idx]);

  // read instance
  //Instance instance = Instance::load(filename);


  return 0;
}
