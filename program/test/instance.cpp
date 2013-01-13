#include <instance.h>
#include <gtest/gtest.h>


TEST(instance, generate_random_instance){
  Instance *I = new Instance();
  I->randomize(7, 350, 0.7);
  for(int i = 0; i < I->num_words(); i++){
  	std::cout << (*I)[i] << "  " << (*I)[i].size() << std::endl;
  }
  std::cout << "\n" << I->solution() << std::endl;

}

