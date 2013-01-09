#include <crossover.h>
#include <gtest/gtest.h>


TEST(Composition, Crossover){
  Individual mom("07243165");
  Individual dad("72403156");

  Composition c;
  
  Individual child = c.cross(&mom, &dad);
  ASSERT_EQ(Individual("52304716"), child);
  
  ASSERT_EQ(&mom, child.parent(0));
  ASSERT_EQ(&dad, child.parent(1));
}

