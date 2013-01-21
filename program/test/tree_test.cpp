#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "suffix_tree.h"
#include <text.h>



using namespace stree;

Text str2text(const char * x, const char * end = 0);

TEST(SuffixTree, ContainsAllSubstrings)
{
  const char * text = "bananasandcaca";
  const int len = strlen(text);
  Tree t(50);

  for(int i = 0; i < len; i++){
    t.push_back(text[i] - 'a');
  } 

  for(const char * begin = text; begin < text + len; begin++){
    for(const char * end = begin + 1; end <= text + len; end++){
      Text subword = str2text(begin, end);
      ASSERT_TRUE(t.contains(subword.begin(), subword.end()));
    }
  }
}

/*
TEST(SuffixTree, BigRandom)
{
  // generate big random text 
  const int size = 1 << 10;
  const int range = 10;
  Text text;
  for(int i = 0; i < size; i++)
    text.push_back(rand() % range);

  Tree t(range);   
  t.push_back(text.begin(), text.end()); 

  // check some substrings
  const int num_substrings = 100;
  for(int i = 0; i < num_substrings; i++){
    int begin = rand() % size;
    int end = begin + rand() % (size - begin);
    ASSERT_TRUE(t.contains(text.begin() + begin, text.begin() + end));
  }

  // check some random strings
  const int num_random = 100;
  for(int i = 0; i < num_random; i++){
    const int len = rand() % size;
    Text str;
    for(int j = 0; j < len; j++)
      str.push_back(rand() % range);

    // search for this text in
    int * pi = new int[len];
    calculate_pi(str.begin(), str.end(), pi);

    std::pair<int, int> result = find_with_overlap(
      str.begin(), str.end(), pi, text.begin(), text.end());
    ASSERT_EQ(result.first == len, t.contains(str.begin(), str.end()));

    delete [] pi;
  }
}
*/

