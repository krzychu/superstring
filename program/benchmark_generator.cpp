#include <instance.h>
#include <sstream>


int main(){
  Instance I(4);

  I.randomize(10, 50, 0.7);
  I.save("gdb.test");

  for(int num_words = 10; num_words <= 100; num_words += 10){
    for(int len = num_words * 10; len <= num_words * 100; len += num_words * 10){
      I.randomize(num_words, len, 0.7);
      std::stringstream fname;
      fname << "test_" << num_words << "_" << len << ".test";
      I.save(fname.str().c_str());
    }
  }
  return 0;
}
