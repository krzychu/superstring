#include <gtest/gtest.h>
#include <local_search.h>


TEST(TranspositionSearch, ReturnsAtLeastTheSame){
  Instance instance(10);
  instance.add_word("abc");
  instance.add_word("ddd");
  instance.add_word("abd");
  instance.preprocess();
  
  Individual start(3);
  start.set_parents((Individual*)10, (Individual*)20);
  start.set_cost(instance.evaluate(&start));

  TranspositionSearch ts(instance);
  LocalSearch::Result r = ts(&start);
  
  ASSERT_EQ(3, r.num_processed);
  ASSERT_GE(start.cost(), r.individual.cost());
  ASSERT_EQ(start.parent(0), r.individual.parent(0));
  ASSERT_EQ(start.parent(1), r.individual.parent(1));
}


TEST(InsertionSearch, ReturnsAtLeastTheSame){
  Instance instance(10);
  instance.add_word("abc");
  instance.add_word("ddd");
  instance.add_word("abd");
  instance.preprocess();
  
  Individual start(3);
  start.set_parents((Individual*)10, (Individual*)20);
  start.set_cost(instance.evaluate(&start));

  InsertionSearch ts(instance);
  LocalSearch::Result r = ts(&start);
  
  ASSERT_EQ(6, r.num_processed);
  ASSERT_GE(start.cost(), r.individual.cost());
  ASSERT_EQ(start.parent(0), r.individual.parent(0));
  ASSERT_EQ(start.parent(1), r.individual.parent(1));
}
