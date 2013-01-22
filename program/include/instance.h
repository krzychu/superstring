#ifndef SUPERSTRING_INSTANCE_H_
#define SUPERSTRING_INSTANCE_H_

#include <vector>
#include <string>
#include <random.h>
#include <algorithm_state.h>

class Instance{
  public:

    typedef std::vector<char> Word;

    Instance(int alphabet_size) 
      : alphabet_size_(alphabet_size){}

    virtual ~Instance();

    Word & operator[] (int word){ return words_[word]; }
    const Word & operator[] (int word) const{ return words_[word]; }
    const int * pi(int word) const{ return pis_[word]; }
   
    int num_words() const { return words_.size(); }
    int alphabet_size() const { return alphabet_size_; }
    int superstring_length() const { return superstring_length_; }
    Individual solution() const { return solution_; }
    void add_word(const std::string & str);
    void add_word(const Word & vec);
    int evaluate(const Individual * ind) const;

    void randomize(int num_words, 
      int superstring_length, 
      float avg_common_part_percentage);

    void save(const char *file_name);
    static Instance load(const char *file_name);
    void clear();

  private:
    const int alphabet_size_; 
    char random_nucleotide();
    
    std::vector< Word > words_;
    std::vector<int *> pis_;
    int superstring_length_;
    Individual solution_;
};

#endif
