#include "suffix_tree.h"
#include <limits>
#include <cassert>

using namespace stree;

const int inf = std::numeric_limits<int>::max() / 4;

stree::Tree::Tree(int alphabet_size)
  : context_(text_), alphabet_size_(alphabet_size)
{
  root_ = new Node(-1, 0, alphabet_size);
  aux_ = new Node(0, 0, alphabet_size);
  for(int i = 0; i < alphabet_size; i++)
    aux_->children[i] = root_;
  root_->suffix_link = aux_;

  active_ = RefPair(root_, 0, 0);
}



stree::Tree::~Tree()
{
  for(int i = 0; i < alphabet_size_; i++)
    aux_->children[i] = 0;
  
  delete aux_;
  delete root_;
}



void stree::Tree::push_back(int letter)
{
  Node * parent;
  Node * last_parent = root_;
  text_.push_back(letter);
  while(!active_.has_trans(context_, letter)){
    parent = active_.node;
    if(active_.implicit())
      parent = parent->split(context_, active_);
   
    // add a leaf
    parent->children[letter] = new Node(active_.end, inf, alphabet_size_);
    
    if(last_parent != root_)
      last_parent->suffix_link = parent;
    last_parent = parent;

    // move active
    active_.node = active_.node->suffix_link;
    active_.canonize(context_);
  }
  
  if(last_parent != root_)
    last_parent->suffix_link = active_.node;

  active_.end++;
  active_.canonize(context_);
}




void stree::Tree::dump(std::ostream & out) const
{
  root_->dump(out, 0, context_);
}
