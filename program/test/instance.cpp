#include <gtest/gtest.h>
#include <instance.h>


TEST(Instance, EvaluatesIndividuals){
  Instance instance;
  instance.add_word("ab");
  instance.add_word("bc");
  instance.add_word("abc");
  instance.add_word("cd");
  instance.add_word("de");

  Individual ind(instance.num_words());
  for(int i = 0; i < instance.num_words(); i++)
    ind[i] = i;
  ASSERT_EQ(5, instance.evaluate(&ind));
}
