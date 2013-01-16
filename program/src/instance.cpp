#include <instance.h>
#include <text.h>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <functional>


using namespace std;

void Instance::add_word(const std::string & str)
{
  words_.push_back(str);
  int * pi = new int[str.size()];
  pis_.push_back(pi);
  calculate_pi(str.begin(), str.end(), pi);
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

  for(int i = 0; i < num_words(); i++){
    const std::string & w = words_[P[i]];
    int * pi = pis_[P[i]];
    
    pair<int, int> out = find_with_overlap(w, pi, ss.begin(), ss.end());
    const unsigned int match = out.first;
    const int overlap = out.second;

    if(match != w.size())
      copy(w.begin() + overlap, w.end(), back_inserter(ss)); 
  } 

  return ss.size();
}

char Instance::random_nucleotide(){
	int r = randint(0,4);
	if(r == 0) return 'A';
	if(r == 1) return 'C';
	if(r == 2) return 'G';
	else return 'T';
}




void Instance::randomize(int num_words, int superstring_length, float avg_common_part_percentage){
	srand(time(0));
	std::string superstring;
	superstring.resize(superstring_length);
	for(int i = 0; i < superstring_length; i++){
		superstring[i] = random_nucleotide();
	}
	std::vector<  std::pair<std::string, int>  > temp_words;
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





