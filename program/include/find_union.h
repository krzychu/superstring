#ifndef FIND_UNION_H_
#define FIND_UNION_H_


class FindUnion{
  public:
    FindUnion(int size);
    ~FindUnion();

    int find(int elem);
    void sum(int a, int b);

  private:
    int * parent_;
    int * rank_;
};


#endif
