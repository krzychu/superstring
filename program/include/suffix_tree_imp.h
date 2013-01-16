template<class TextIterator>
bool stree::Tree::contains
  (const TextIterator & begin, const TextIterator & end) const
{
  Node * cur = root_;  
  int on_edge = 1;
  for(TextIterator i = begin; i != end; i++){
    const int letter = *i;
    if(on_edge == cur->size()){
      if(!cur->children[letter])
        return false;
      
      cur = cur->children[letter];
      on_edge = 0;
    }
    else{
      if(letter != text_[cur->begin + on_edge])
        return false;
    }
    on_edge++;
  }
  return true;
}



template<class TextIterator>
void stree::Tree::push_back(const TextIterator & begin, const TextIterator & end)
{
  for(TextIterator itr = begin; itr < end; itr++)
    push_back(*itr);
}


