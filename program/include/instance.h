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

    Word & operator[] (int word){ 
      return words_[word]; 
    }

    const Word & operator[] (int word) const{
      return words_[word]; 
    }
   
    int num_words() const { return words_.size(); }
    void add_word(const std::string & str);
    void add_word(const Word & vec);
    int evaluate(const Individual * ind) const;

    Individual solution() const { return solution_; }

    void randomize(int num_words, 
      int superstring_length, 
      float avg_common_part_percentage);

  private:
    const int alphabet_size_; 
    char random_nucleotide();
    Instance(const Instance & instance);
    const Instance & operator=(const Instance & other);
    
    std::vector< Word > words_;
    std::vector<int *> pis_;
    int superstring_length_;
    Individual solution_; 
};

#endif
