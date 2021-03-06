#include <instance.h>
#include <text.h>
#include <suffix_tree.h>

#include <algorithm>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <stdexcept>

using namespace std;

void Instance::add_word(const std::string & str)
{
  Word w(str.size());
  for(unsigned int i = 0; i < str.size(); i++)
    w[i] = str[i] - 'a';

  add_word(w);
}


void Instance::add_word(const Word & w)
{
  words_.push_back(w);
}



/* saved instance template:
 * 
 *	alphabet_size(int)
 *	solution_length(int)
 *	solution(w1 w2 w3 w4 ...)
 *  num_words(int)
 *	word1(string)
 *	word2(string)
 *	word3(string)
 *  ...
 * 
 */

void Instance::save(const char *file_name){
  FILE * f = fopen(file_name, "w");
  if(!f) throw std::exception();
  fprintf(f, "%d\n", alphabet_size_);
  fprintf(f, "%d\n", superstring_length_);
  int n = words_.size();
  fprintf(f, "%d\n", n);
  for(int i = 0; i < n; i++) fprintf(f, "%d ", solution_[i]);
  fprintf(f, "\n");

  for(int i = 0; i < n; i++){
   for(unsigned int j = 0; j < words_[i].size(); j++){
      fprintf(f, "%c", words_[i][j] + 'a');
    }
    fprintf(f, "\n");
  }
  fclose(f);
}


Instance Instance::load(const char *file_name){
  printf("loading : %s\n", file_name);

  FILE * f = fopen(file_name, "r");
  if(!f) throw std::exception();

  int alphabet_size, superstring_length;
  
  fscanf(f, "%d", &alphabet_size);
  printf("loading : alphabet_size = %d\n", alphabet_size);

  fscanf(f, "%d", &superstring_length);
  printf("loading : superstring_length = %d\n", superstring_length);

  Instance I(alphabet_size);
  I.superstring_length_ = superstring_length;
  int n;
  fscanf(f, "%d", &n);
  printf("loading : n = %d\n", n);

  I.solution_.resize(n);
  for(int i = 0; i < n; i++) fscanf(f, "%d ", &I.solution_[i]);

  for(int i = 0; i < n; i++){
    char s[1000000];
    fscanf(f, "%s", s);
    string str(s);
    I.add_word(str);
  }
  fclose(f);
  return I;
}


Instance::~Instance(){}


void Instance::preprocess() 
{
  const int n = num_words();

  // compute pi for all of them
  for(int i = 0; i < n; i++){
    std::vector<int> pi(words_[i].size()); 
    calculate_pi(words_[i].begin(), words_[i].end(), pi.begin());
    pis_.push_back(pi);
  }

  vector<vector<int> > overlap(n, vector<int>(n));
  vector<bool> inside(n, false);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(i == j)
        continue;

      // calculate overlap of i and j  
      const Word & left = words_[i];
      const Word & right = words_[j];

      std::pair<int, int> res = find_with_overlap(
        right.begin(), right.end(), pis_[j],
        left.begin(), left.end() 
      );

      if(res.first == (int)right.size()){
        inside[j] = true;
      }

      overlap[i][j] = res.second;
    }
  } 

  vector<int> new_index(n, 0);
  for(int i = 1; i < n; i++)
    new_index[i] = new_index[i - 1] + !inside[i-1];

  const int new_n = new_index[n - 1] + 1;

  word_size_sum_ = 0;
  for(int i = 0; i < n; i++){
    if(!inside[i]){
      words_[new_index[i]] = words_[i];
      pis_[new_index[i]] = pis_[i];
      word_size_sum_ += words_[i].size();
    }
  }

  words_.resize(new_n);
  pis_.resize(new_n);

  ov_.clear();
  for(int i = 0; i < n; i++){
    ov_.push_back(std::vector<int>(new_n));
    for(int j = 0; j < n; j++){
      if(i == j || inside[i] || inside[j])
        continue;

      ov_[new_index[i]][new_index[j]] = overlap[i][j];
    }
  }

  needs_preprocessing_ = false;
}




int Instance::evaluate(const Individual * ind) const
{
  assert(!needs_preprocessing_);
  assert(ind->size() == num_words());

  const Individual & P = *ind;
  int sum = 0;
  for(unsigned int i = 0; i < P.size() - 1; i++){
    sum += ov(P[i], P[i+1]);
  }

  return word_size_sum_ - sum;
}




std::vector< std::vector<int> > Instance::evaluate_all_transpositions
  (const Individual * ind) const
{
  const Individual & P = *ind;
  const int n = ind->size();
  std::vector< std::vector<int> > res(n, std::vector<int>(n, 0));

  int overlap_sum = 0;
  for(unsigned int i = 0; i < P.size() - 1; i++){
    overlap_sum += ov(P[i], P[i+1]);
  }

  for(int i = 0; i < n - 1; i++){
    int sum = overlap_sum;
    if(i > 0){
      sum -= ov(P[i-1], P[i]);
      sum += ov(P[i-1], P[i+1]);
    }

    sum -= ov(P[i], P[i+1]);
    sum += ov(P[i+1], P[i]);
    
    if(i < n - 2){
      sum -= ov(P[i+1], P[i+2]);
      sum += ov(P[i], P[i+2]);
    }
    res[i][i+1] = word_size_sum_ - sum;
  }

  for(int i = 0; i < n; i++){
    for(int j = i + 2; j < n; j++){
      int sum = overlap_sum;

      if(i > 0){
        sum -= ov(P[i - 1], P[i]);
        sum += ov(P[i - 1], P[j]);
      }

      if(j > 0){
        sum -= ov(P[j - 1], P[j]);
        sum += ov(P[j - 1], P[i]);
      }
      
      if(i < n - 1){
        sum -= ov(P[i], P[i + 1]);
        sum += ov(P[j], P[i + 1]);
      }
 
      if(j < n - 1){
        sum -= ov(P[j], P[j + 1]);
        sum += ov(P[i], P[j + 1]);
      }

      res[i][j] = word_size_sum_ - sum;
    }
  }

  return res;
}


 

void Instance::clear(){
  needs_preprocessing_ = true;
	words_.clear();
	pis_.clear();
	superstring_length_ = 0;
	solution_.clear();
}




char Instance::random_nucleotide(){
	int r = randint(0,alphabet_size_);
  return r;

  /* 
   * Zmieniłem, bo jeśli wartości będą z przedziału 0 - 3 to drzewo będzie znacząco
   * mniejsze.
   *
	if(r == 0) return 'A';
	if(r == 1) return 'C';
	if(r == 2) return 'G';
	else return 'T';
  */
}



void Instance::randomize(int num_words, int superstring_length, float avg_common_part_percentage){
	clear();

	Word superstring;
	superstring_length_ = superstring_length;
	superstring.resize(superstring_length);
	for(int i = 0; i < superstring_length; i++){
		superstring[i] = random_nucleotide();
	}
	std::vector<  std::pair<Word, int>  > temp_words;
	temp_words.resize(num_words);
	for(int i = 0; i < num_words; i++){
		temp_words[i].second = i;
	}
	int basic_word_length = superstring_length/num_words;
	int random_scope = int(0.25 * float(basic_word_length) * avg_common_part_percentage);
	int sideword_length = int(float(basic_word_length) * (1.0 + (avg_common_part_percentage)/2.0));
	int midword_length = int(float(basic_word_length) * (1.0 + avg_common_part_percentage));

	temp_words[0].first.resize(sideword_length + randint(-random_scope, random_scope+1));
	for(unsigned i = 0; i < temp_words[0].first.size(); i++) {
		temp_words[0].first[i] = superstring[i];
	}

	temp_words[num_words-1].first.resize(sideword_length + randint(-random_scope, random_scope+1));
	for(int n = temp_words[num_words-1].first.size(), i = 0; i < n; i++) {
		temp_words[num_words-1].first[i] = superstring[superstring_length - n + i];	
	}

	for(int j = 1; j < num_words-1; j++){
		int n = midword_length + randint(-random_scope, random_scope+1);
		temp_words[j].first.resize(n);
		int I = (n - basic_word_length)/2 + basic_word_length*j;
		if(I < 0){
			n += I;
			temp_words[j].first.resize(n);
			I = 0;
		}
		if(I + n >= superstring_length){
			I = superstring_length-n;
		}
		for(int i = 0; i < n; i++, I++){
			temp_words[j].first[i] = superstring[I];
		}
	}

	std::random_shuffle(temp_words.begin(), temp_words.end());

	solution_.resize(num_words);
	for(int i = 0; i < num_words; i++){
		add_word(temp_words[i].first);
		solution_[i] = temp_words[i].second;
	}
}





