#include <instance.h>
#include <sstream>


int main(){
  Instance I(4);

  I.randomize(10, 50, 0.7);
  I.save("gdb.test");

  for(int num_words = 100; num_words <= 1000; num_words += 100){
    const int len = 50000;
    I.randomize(num_words, len, 0.7);
    std::stringstream fname;
    fname << "test_" << num_words << "_" << len << ".test";
    I.save(fname.str().c_str());
  }
  return 0;
}
