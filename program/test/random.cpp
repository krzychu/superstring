#include <random.h>
#include <gtest/gtest.h>

TEST(Random, ReturnIntegersInRange){
  for(int i = 0; i < 1000000; i++){
    ASSERT_LE(0, randint(10)); 
    ASSERT_GT(10, randint(10)); 
  }
}
