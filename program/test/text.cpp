#include <gtest/gtest.h>
#include <cstring>
#include <text.h>


TEST(text, calculate_pi){
  std::string text("abaabbbab"); 
  const int pi[] = {0, 0, 1, 1, 2, 0, 0, 1, 2};

  int * out = new int[text.size()];
  calculate_pi(text.begin(), text.end(), out);

  for(unsigned int i = 0; i < text.size(); i++){
    ASSERT_EQ(pi[i], out[i]);
  }

  delete [] out;
}


TEST(text, find_with_overlap){
  std::string pat = "ababd";
  std::string text = "ababddaabab";
 
  int * pi = new int[pat.size()];
  calculate_pi(pat.begin(), pat.end(), pi);

  std::pair<int, int> res = find_with_overlap(pat, pi, 
    text.begin(), text.end());

  ASSERT_EQ(4, res.second);
  ASSERT_EQ(5, res.first);

  delete [] pi;
}
