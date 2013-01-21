#include <gtest/gtest.h>
#include <find_union.h>


TEST(FindUnion, Works)
{
  FindUnion fu(1000);

  for(int i = 0; i < 1000; i++)
    ASSERT_EQ(i, fu.find(i));


  fu.sum(3, 4);
  fu.sum(5, 4);

  ASSERT_EQ(fu.find(3), fu.find(4));
  ASSERT_EQ(fu.find(3), fu.find(5));
  ASSERT_EQ(fu.find(4), fu.find(5));
}
