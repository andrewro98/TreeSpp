/*

  sparse_bst.h
  Andrew Rosen Dec 2018
  Header file for sparse binary search tree.

*/

#include "tree.h"
#include "exceptions.h"

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
    sparse_elt<T> * root;

    sparse_elt<T> * interior_search(T & obj, sparse_elt<T> * head = root)
    {
      sparse_elt<T> * temp = head;
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
          return temp;
        }
      }
      return nullptr;
    }

    sparse_elt<T> * interior_search_parent(T & obj, sparse_elt<T> * head = root)
    {
      if(head && head->object == obj)
      {
        return nullptr;
      }
      sparse_elt<T> * temp = head;
      sparse_elt<T> * par = head;
      while(temp)
      {
        if(obj < temp->object)
        {
          par = temp;
          temp = temp->left;
        }
        else if(obj > temp->object)
        {
          par = temp;
          temp = temp->right;
        }
        else
        {
          return par;
        }
      }
      throw FailedFindException();
    }

    void erase(T & obj, sparse_elt<T> * head = root)
    {
      sparse_elt<T> * parent = head;
      sparse_elt<T> * to_delete;
      if(parent->left && parent->object == obj)
      {
        to_delete = parent->left;
      }
      else
      {
        to_delete = parent->right;
      }

      // conditions: leaf, one child, two children
      if(!(to_delete->left) && !(to_delete->right)) // leaf
      {
        if(to_delete == parent->left) parent->left = nullptr;
        else parent->right = nullptr;
        delete to_delete;
      }
      else if((to_delete->left) && (to_delete->right)) // two children
      {
        sparse_elt<T> * next = to_delete->right;
        sparse_elt<T> * next_parent = to_delete->right;
        while(next->left)
        {
          next_parent = next;
          next = next->left;
        }
        if(next_parent == next) // right child is next greatest
        {
          to_delete->right = next->right;
          to_delete->object = next->object;
          delete next;
        }
        else
        {
          next_parent->left = next->right;
          to_delete->object = next->object;
          delete next;
        }
      }
      else // one child
      {
        if(to_delete->left) // left child
        {
          to_delete->object = to_delete->left->object;
          erase(to_delete->left->object, to_delete);
        }
        else // right child
        {
          to_delete->object = to_delete->right->object;
          erase(to_delete->right->object, to_delete);
        }
      }
    }

  public:
    virtual bool insert(T & obj)
    {

      if(!root)
      {
        ++(this->number_of_elements);
        root = new sparse_elt<T>(obj);
        return true;
      }
      sparse_elt<T> * temp = root;
      while(temp)
      {
        if(obj < temp->object)
        {
          if(!(temp->left))
          {
            temp->left = new sparse_elt<T>(obj);
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
            temp->right = new sparse_elt<T>(obj);
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
      sparse_elt<T> * temp = interior_search(obj);
      if(temp != nullptr)return true;
      return false;
    }
    virtual T find(T & obj)
    {
      sparse_elt<T> * temp = interior_search(obj);
      if(temp != nullptr)return temp->object;
      // failed find, throw an exception
      throw FailedFindException();
    }
    virtual bool erase(T & obj)
    {
      this->number_of_elements--;
      sparse_elt<T> * parent;
      try{
        parent = interior_search_parent(obj);
      } catch(FailedFindException& e) {
        return false; // object not found
      }

      if(!parent) // deleting root
      {
        if(!(root->left) && !(root->right)) // size == 1
        {
          delete root;
          root = nullptr;
        }
        else if((root->left) && (root->right)) // two children
        {
          // TODO inorder successor and delete leaf
        }
        else // one child
        {
          sparse_elt<T> * temp = root;
          if(root->left)
          {
            root = root->left;
          }
          else
          {
            root = root->right;
          }
          delete temp;
        }
        return true;
      }
      // else we need to use erase from the root
      erase(obj, parent);
      return true;
    }
};
