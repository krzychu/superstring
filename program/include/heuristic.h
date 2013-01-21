#ifndef HEURISTIC_H_
#define HEURISTIC_H_

#include <instance.h>

class Heuristic
{
  public:
    Heuristic(const Instance & instance)
      : instance_(instance) {}

    // returns solution    
    int run() const;

  private:
    const Instance & instance_;
};

#endif
