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
      : alphabet_size_(alphabet_size),
        needs_preprocessing_(true) {}

    virtual ~Instance();

    const Word & operator[] (int word) const{ return words_[word]; }
    const std::vector<int> & pi(int word) const{ return pis_[word]; }
   
    int num_words() const { return words_.size(); }
    int alphabet_size() const { return alphabet_size_; }
    int superstring_length() const { return superstring_length_; }
    int word_size_sum() const {return word_size_sum_;}
    Individual solution() const { return solution_; }

    void add_word(const std::string & str);
    void add_word(const Word & vec);

    void preprocess();
    int evaluate(const Individual * ind) const;
    std::vector< std::vector<int> > evaluate_all_transpositions(const Individual * ind) const;
    int ov(int i, int j) const { return ov_[i][j]; }

    void randomize(int num_words, 
      int superstring_length, 
      float avg_common_part_percentage);

    void save(const char *file_name);
    static Instance load(const char *file_name);

  private:
    const int alphabet_size_; 
    bool needs_preprocessing_;
    char random_nucleotide();
    void clear();
    
    std::vector< Word > words_;
    std::vector< std::vector<int> > pis_;
    std::vector< std::vector<int> > ov_;
    int word_size_sum_;

    int superstring_length_;
    Individual solution_;
};

#endif
