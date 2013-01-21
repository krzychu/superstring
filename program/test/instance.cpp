#include <gtest/gtest.h>
#include <instance.h>


TEST(Instance, EvaluatesIndividuals){
  Instance instance(200);
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

/*
TEST(instance, generate_random_instance){
  Instance I(4);
  I.randomize(7, 350, 0.7);
  for(int i = 0; i < I.num_words(); i++){
  	std::cout << I[i] << "  " << I[i].size() << std::endl;
  }
  std::cout << "\n" << I.solution() << std::endl;
}
*/

TEST(Instance, save_instance){
  Instance I(4);
  I.randomize(7, 350, 0.7);
  I.save("temp.txt");
}


TEST(Instance, save_load_instance){
  Instance I(4);
  I.randomize(7, 350, 0.7);
  I.save("temp.txt");
  Instance J = Instance::load("temp.txt");

  ASSERT_EQ(I.num_words(), J.num_words());
  ASSERT_EQ(I.alphabet_size(), J.alphabet_size());
    ASSERT_EQ(I.superstring_length(), J.superstring_length());
    ASSERT_EQ(I.solution(), J.solution());
    for(int i = 0; i < I.num_words(); i++){
      ASSERT_EQ(I[i] == J[i], true);
    }
  }

