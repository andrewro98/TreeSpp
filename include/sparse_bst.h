/*

  sparse_bst.h
  Andrew Rosen Dec 2018
  Header file for sparse binary search tree.

*/

// TODO adjust to handle root invalidations -- partially done but could require more work/adjustments later

#include "tree.h"
#include "exceptions.h"
#include <string>
#include <sstream>
#include <iostream>

template <typename T>
class sparse_elt {
  public:
    T object;
    sparse_elt * left;
    sparse_elt * right;

    sparse_elt(const T & _obj): object(_obj), left(nullptr), right(nullptr) {}
};

template <typename T>
class sparse_bst : public tree<T> {
  private:
    sparse_elt<T> * root;
    /////////////////////////////////////////////////
    // used to make sure user doesn't read old roots
    bool root_is_valid;
    sparse_elt<T> * old_root;
    /////////////////////////////////////////////////

    sparse_elt<T> * interior_search(const T & obj, sparse_elt<T> * head)
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

    sparse_elt<T> * interior_search_parent(const T & obj, sparse_elt<T> * head)
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

    void erase(const T & obj, sparse_elt<T> * head)
    {
      sparse_elt<T> * parent = head;
      sparse_elt<T> * to_delete;
      if(parent->left && parent->left->object == obj)
      {
        to_delete = parent->left;
      }
      else
      {
        to_delete = parent->right;
      }

      //std::cout << to_delete->object << std::endl;

      // conditions: leaf, one child, two children
      if(!(to_delete->left) && !(to_delete->right)) // leaf
      {
        if(to_delete == parent->left) parent->left = nullptr;
        else parent->right = nullptr;
        delete to_delete;
      }
      else if((to_delete->left) && (to_delete->right)) // two children
      {
        //std::cout << "correct loc" << std::endl;
        sparse_elt<T> * next = to_delete->right;
        sparse_elt<T> * next_parent = to_delete->right;
        while(next->left)
        {
          next_parent = next;
          next = next->left;
        }
        //std::cout << next->object << " " << next_parent->object << std::endl;
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

    void interior_inorder(const sparse_elt<T> * head, std::stringstream & ss, const std::string & delim)
    {
      if(!head)return;
      interior_inorder(head->left, ss, delim);
      ss << head->object << delim;
      interior_inorder(head->right, ss, delim);
    }

  public:

    virtual const sparse_elt<T> * get_root() {
      root_is_valid = true;
      old_root = root;
      return root;
    }

    virtual bool insert(const T & obj)
    {

      if(!root)
      {
        ++(this->number_of_elements);
        root = new sparse_elt<T>(T(obj));
        return true;
      }
      sparse_elt<T> * temp = root;
      while(temp)
      {
        if(obj < temp->object)
        {
          if(!(temp->left))
          {
            temp->left = new sparse_elt<T>(T(obj));
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
            temp->right = new sparse_elt<T>(T(obj));
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
      return false; // TODO add error, code should never get here and we want a bug report
    }
    virtual bool contains(const T & obj)
    {
      sparse_elt<T> * temp = interior_search(obj, root);
      if(temp != nullptr)return true;
      return false;
    }
    virtual T find(const T & obj)
    {
      sparse_elt<T> * temp = interior_search(obj, root);
      if(temp != nullptr)return temp->object;
      // failed find, throw an exception
      throw FailedFindException();
    }
    virtual bool erase(const T & obj)
    {
      sparse_elt<T> * parent;
      try{
        parent = interior_search_parent(obj, root);
      } catch(FailedFindException& e) {
        return false; // object not found
      }
      this->number_of_elements--;
      if(!parent) // deleting root
      {
        root_is_valid = false;
        if(!(root->left) && !(root->right)) // size == 1
        {
          delete root;
          root = nullptr;
        }
        else if((root->left) && (root->right)) // two children
        {
          sparse_elt<T> * next = root->right;
          sparse_elt<T> * next_parent = root->right;
          while(next->left)
          {
            next_parent = next;
            next = next->left;
          }
          if(next_parent == next) // right child is next greatest
          {
            root->right = next->right;
            root->object = next->object;
            delete next;
          }
          else
          {
            next_parent->left = next->right;
            root->object = next->object;
            delete next;
          }
        }
        else // one child
        {
          //std::cout << "correct loc" << std::endl;
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
        //std::cout << root->object << std::endl;
        return true;
      }
      // else we need to use erase from the root
      //std::cout << parent->object << std::endl;
      erase(obj, parent);
      return true;
    }
    virtual std::string inorder(const sparse_elt<T> * head, const std::string & delim)
    {
      if(!root_is_valid && head == old_root) head = root; // this is assuming a user deleted the root and didn't update the root pointer
      if(!head)return "";
      std::stringstream ss;
      interior_inorder(head, ss, delim);
      std::string result = ss.str();
      return result.substr(0, result.length()-delim.length());
    }
};
