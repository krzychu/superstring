#include <crossover.h>
#include <gtest/gtest.h>


TEST(PMX, Crossover){
  Individual mom("8473625190");
  Individual dad("0123456789");
  Individual expected_child("0743625189");

  PMX pmx;

  Individual child = pmx.cross(3, 8, &mom, &dad);

  ASSERT_EQ(expected_child, child);
  ASSERT_EQ(&mom, child.parent(0));
  ASSERT_EQ(&dad, child.parent(1));
}



TEST(PMX, BigRandom){
  PMX pmx;
  for(int i = 0; i < 1000; i ++){
    Individual a(20);
    a.randomize();

    Individual b(20);
    b.randomize();

    Crossover::Result res = pmx(&a, &b);
    ASSERT_TRUE(res.first.valid());
    ASSERT_TRUE(res.second.valid());
  }
}
