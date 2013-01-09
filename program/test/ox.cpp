#include <crossover.h>
#include <gtest/gtest.h>


TEST(OX, Crossover){
  Individual mom("07243165");
  Individual dad("72403156");

  OX ox;
  
  Individual child = ox.cross(2, 5, &mom, &dad);
  ASSERT_EQ(Individual("24307156"), child);
  ASSERT_EQ(&mom, child.parent(0));
  ASSERT_EQ(&dad, child.parent(1));

  child = ox.cross(2, 5, &dad, &mom);
  ASSERT_EQ(Individual("04372165"),child);
  ASSERT_EQ(&mom, child.parent(1));
  ASSERT_EQ(&dad, child.parent(0));
}



TEST(OX, BigRandom){
  OX ox;
  for(int i = 0; i < 1000; i ++){
    Individual a(20);
    a.randomize();

    Individual b(20);
    b.randomize();

    Crossover::Result res = ox(&a, &b);
    ASSERT_TRUE(res.first.valid());
    ASSERT_TRUE(res.second.valid());
  }
}
