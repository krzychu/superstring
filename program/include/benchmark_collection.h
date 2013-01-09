#ifndef BENCHMARKS_H_
#define BENCHMARKS_H_

#include <instance.h>
#include <vector>


class IntStream{
  public:
    IntStream(FILE * f);
    IntStream & operator >> (int & dst);
    bool empty() const;

  private:
    FILE * f_;
    int size_;
    int read_;
};


class BenchmarkCollection{
  public:
    void load(const char * path);
    const Instance & instance(int num) const;
    int size() const;

    ~BenchmarkCollection();

  private:
    int size_;
    std::vector<Instance * > instances_;

    void read_instance(IntStream & is);
};

#endif
