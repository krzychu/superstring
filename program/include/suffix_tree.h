#ifndef SUFFIX_TREE_H_
#define SUFFIX_TREE_H_

#include <vector>
#include <iostream>

namespace stree{



typedef std::vector<char> Text;


struct Substr
{
  int begin;
  int end;

  Substr() {}
  Substr(int b, int e) : begin(b), end(e) {}
  int size() const { return end - begin; }
};



struct Context;
struct RefPair;


struct Node : public Substr
{
  Node ** children;
  int alphabet_size;
  Node * suffix_link;

  Node(int b, int e, int alphabet);
  ~Node();
  
  Node * split(const Context & cx, const RefPair & rp);
  bool leaf() const;

  void dump(std::ostream & out, int indent , const Context & cx) const;
};





struct Context
{
  const Text & text;
  Context(const Text & t) : text(t) {}
};





struct RefPair : public Substr
{
  Node * node;
  RefPair(Node * n = 0, int b = 0, int e = 0) 
    : Substr(b, e), node(n) {}

  bool implicit() const;
  
  void canonize(const Context & context);
  Node * next(const Context & context) const;
  bool has_trans(const Context & context, int letter) const;
};



class Tree
{
  public:

    typedef const char & const_reference;

    Tree(int alphabet_size);
    ~Tree();
    
    void push_back(int letter);

    template<class TextIterator>
    void push_back(const TextIterator & begin, const TextIterator & end);

    Node * root() const {return root_;}
    int alphabet_size() const {return alphabet_size_;}
    
    template<class TextIterator>
    bool contains(const TextIterator & begin, const TextIterator & end) const;

    void dump(std::ostream & out) const;

  private:
    Node * aux_;
    Node * root_;
    RefPair active_;

    Text text_;
    Context context_;
    int alphabet_size_;
};

#include "suffix_tree_imp.h"

}

#endif
