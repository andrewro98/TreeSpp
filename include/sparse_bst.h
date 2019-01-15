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

    sparse_elt(T & _obj): object(_obj), left(nullptr), right(nullptr) {}
};

template <typename T>
class sparse_bst : public tree<T> {
  private:
    sparse_elt * root;
  public:
    virtual bool insert(T & obj)
    {

      if(!root)
      {
        ++(this->number_of_elements);
        root = new sparse_elt(obj);
        return true;
      }
      sparse_elt * temp = root;
      while(temp)
      {
        if(obj < temp->object)
        {
          if(!(temp->left))
          {
            temp->left = new sparse_elt(obj);
            ++(this->number_of_elements);
            return true;
          }
          else
          {
            temp = temp->left;
          }
        }
        else if(obj > temp->object)
        {
          if(!(temp->right))
          {
            temp->right = new sparse_elt(obj);
            ++(this->number_of_elements);
            return true;
          }
          else
          {
            temp = temp->right;
          }
        }
        else
        {
          return false; // duplicates
        }
      }
    }
    virtual bool contains(T & obj)
    {
      sparse_elt * temp = root;
      while(temp)
      {
        if(obj < temp->object)
        {
          temp = temp->left;
        }
        else if(obj > temp->object)
        {
          temp = temp->right;
        }
        else
        {
          return true;
        }
      }
      return false;
    }
    virtual T find(T & obj)
    {
      sparse_elt * temp = root;
      while(temp)
      {
        if(obj < temp->object)
        {
          temp = temp->left;
        }
        else if(obj > temp->object)
        {
          temp = temp->right;
        }
        else
        {
          return temp->object;
        }
      }
      return obj;//TODO;
    }
    virtual bool erase(T & obj);
};
