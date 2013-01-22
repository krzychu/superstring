#include <instance.h>
#include <text.h>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <functional>
#include <suffix_tree.h>
#include <cstdio>
#include <cstring>

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
  int * pi = new int[w.size()];
  pis_.push_back(pi);
  calculate_pi(w.begin(), w.end(), pi);
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


Instance::~Instance()
{
  for(unsigned int i = 0; i < pis_.size(); i++)
    delete [] pis_[i];
}


int Instance::evaluate(const Individual * ind) const
{
  const Individual & P = *ind;
  vector<char> ss;
  stree::Tree tree(alphabet_size_);

  for(int i = 0; i < num_words(); i++){
    const Word & w = words_[P[i]];
    int * pi = pis_[P[i]];
   
    vector<char>::iterator start;
    if(w.size() > ss.size())
      start = ss.begin();
    else
      start = ss.end() - w.size();

    pair<int, int> out = find_with_overlap(
      w.begin(), w.end(), pi, 
      start, ss.end());

    const int overlap = out.second;

    if(!tree.contains(w.begin(), w.end())){
      copy(w.begin() + overlap, w.end(), back_inserter(ss)); 
      copy(w.begin() + overlap, w.end(), back_inserter(tree)); 
    }
  } 

  return ss.size();
}

void Instance::clear(){
	words_.resize(0);
	pis_.resize(0);
	superstring_length_ = 0;
	solution_.resize(0);
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





