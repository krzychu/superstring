#ifndef SUPERSTRING_INSTANCE_H_
#define SUPERSTRING_INSTANCE_H_

#include <vector>
#include <string>

#include <random.h>
#include <algorithm_state.h>

class Instance{
  public:
    Instance(){}

    virtual ~Instance() {}

    std::string & operator[] (int word){ 
      return words_[word]; 
    }

    const std::string & operator[] (int word) const{
      return words_[word]; 
    }
   
    int num_words() const { return words_.size(); }

    void add_word(const std::string & str){
      words_.push_back(str);
    }

    int evaluate(const Individual * ind) const;

    Individual solution() const { return solution_; }

    void randomize(const int num_words, 
      const int superstring_length, 
      const float avg_common_part_percentage);

  private:
    char random_nucleotide();
    Instance(const Instance & instance);
    const Instance & operator=(const Instance & other);
    
    std::vector<std::string> words_;
    int superstring_length_;
    Individual solution_; 
};

#endif
