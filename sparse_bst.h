/*

  sparse_bst.h
  Andrew Rosen Dec 2018
  Header file for sparse binary search tree.

*/

#include "tree.h"

template <typename T>
class sparse_elt {
  public:
    T object;
    sparse_elt * left;
    sparse_elt * right;
};

template <typename T>
class sparse_bst : public tree<T> {
  private:
    sparse_elt * root;
  public:
    virtual bool insert(T & obj);
    virtual bool contains(T & obj);
    virtual T find(T & obj);
    virtual bool erase(T & obj);
};
