#include <gtest/gtest.h>
#include <cstring>
#include <text.h>


TEST(text, calculate_pi){
  const char * text = "abaabbbab";   
  const int pi[] = {0, 0, 1, 1, 2, 0, 0, 1, 2};

  const int n = strlen(text);

  int * out = new int[n];
  calculate_pi(text, out, n);

  for(int i = 0; i < n; i++){
    ASSERT_EQ(pi[i], out[i]);
  }

  delete out;
}
