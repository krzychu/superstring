#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <vector>
#include <istream>


class Individual : public std::vector<int>{
  public:
    Individual() {}
    Individual(int size);
    Individual(const char * str);

    bool operator == (const Individual & other) const;
    bool operator < (const Individual & other) const;
    bool operator <= (const Individual & other) const;
    bool valid() const;

    void swap(int i, int j);
    void insert(int i, int j);
    void randomize();

    int cost() const;
    void set_cost(int cost);

    double adaptation() const;
    void set_adaptation(double adaptation);

    double scaled_adaptation() const;
    void set_scaled_adaptation(double scaled);

    const Individual * parent(int i) const;
    void set_parents(const Individual * a, const Individual * b);

  private:
    int cost_;
    double adaptation_;
    double scaled_adaptation_;

    const Individual * parents_[2];
};


std::ostream & operator << (std::ostream & out, const Individual & p);


#endif
