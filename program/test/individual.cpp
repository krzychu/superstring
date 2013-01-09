#include <individual.h>
#include <gtest/gtest.h>

TEST(Individual, ReadsItselfFromString){
  Individual p("0123");

  ASSERT_EQ(4, p.size());
  for(int i = 0; i < 4; i++){
    ASSERT_EQ(i, p[i]);  
  }
}


TEST(Individual, ChecksValidity){
  Individual p(3);
  ASSERT_FALSE(p.valid());

  p[0] = 2;
  p[1] = 1;
  p[2] = 0;
  ASSERT_TRUE(p.valid());
}


TEST(Individual, Insert){
  Individual mom("07243165");

  Individual Child1 = mom; Child1.insert(0, 7);
  Individual Child2 = mom; Child2.insert(7, 0);
  Individual Child3 = mom; Child3.insert(2, 5);

  ASSERT_EQ(Individual("72431650"), Child1);
  ASSERT_EQ(Individual("50724316"), Child2);
  ASSERT_EQ(Individual("07431265"), Child3);
}
