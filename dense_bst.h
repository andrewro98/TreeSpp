/*

  dense_bst.h
  Andrew Rosen Dec 2018
  Header file for dense binary search tree.

*/

#include "tree.h"
#include <vector>

template <typename T>
class dense_bst : public tree<T> {
  private:
    vector<T> data;
  public:
    virtual bool insert(T & obj);
    virtual bool contains(T & obj);
    virtual T find(T & obj);
    virtual bool erase(T & obj);
};
