/*
  TODO INCOMPLETE
  dense_bst.h
  Andrew Rosen Dec 2018
  Header file for dense binary search tree.

  Important things to consider:
    - the templated type T must have a default initialization
    - the erase for this type is relatively slower than the erase for sparse/other bst's. This is inherent because of the array representation.
  Takeaway:
    This is best used for situations in which there is little erasing, and few sticks in the tree-- only use when your data can be inserted in a way that reduces sticks, or this data structure is not your best choice. Consider sparse_bst or any self-balancing tree.
*/


#include "tree.h"
#include <iostream>
#include <vector>

template <typename T>
class dense_bst : public tree<T> {
  private:
    struct data {
      T obj;
      bool empty;
      void set(const T & _obj) {
        obj = T(_obj);
        empty = false;
      }
      data() : empty(true) {}
    };
    data * arr;
    int current_capacity;
    int height;
  public:
    dense_bst()
    {
      arr = new data[2];
      current_capacity = 1;
      height = 1;
      this->number_of_elements = 0;
    }
    virtual bool insert(const T & obj)
    {
      int index = 1;
      while(index <= current_capacity && !arr[index].empty)
      {
        if(arr[index].obj < obj)
        {
          index*=2;
        }
        else if(arr[index].obj > obj)
        {
          index = index*2+1;
        }
        else
        {
          return false; // duplicate entry, return false
        }
      }
      // if we're oob, we need to grow the array
      /////////////////////////////////////////////////////
      if(index > current_capacity)
      {
        data * temp = new data[1 + current_capacity + height*2];
        for(int i = 1; i <= current_capacity; ++i)
        {
          temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        current_capacity += height*2;
        ++height;
      }
      /////////////////////////////////////////////////////
      // then, we insert

      arr[index].set(obj);
      ++(this->number_of_elements);

      // and return true
      return true;
    }
    virtual bool contains(const T & obj)
    {
      int index = 1;
      while(index <= current_capacity && !arr[index].empty)
      {
        if(arr[index].obj < obj)
        {
          index*=2;
        }
        else if(arr[index].obj > obj)
        {
          index = index*2+1;
        }
        else
        {
          return true;
        }
      }
      return false;
    }

    virtual bool erase(const T & obj) /* deleted with inorder successor */
    {
      int index = 1;
      while(index <= current_capacity && !arr[index].empty)
      {
        if(arr[index].obj < obj)
        {
          index*=2;
        }
        else if(arr[index].obj > obj)
        {
          index = index*2+1;
        }
        else /* we found the item to delete */
        {
          break;
        }
      }
      if(index > current_capacity) // item not found
      {
        return false;
      }
      // perform the erase
      --(this->number_of_elements);
      bool erasing = true;
      while(erasing)
      {
        erasing = false;
        // no children:
        if((index*2 <= current_capacity && arr[index*2].empty && index*2 < current_capacity && arr[index*2+1].empty)||index*2 > current_capacity)
        {
          arr[index].empty = true;
        }
        // two children
        else if(index*2 <= current_capacity && !arr[index*2].empty && index*2 < current_capacity && !arr[index*2+1].empty)
        {
          // TODO
        }
        else if(index*2 <= current_capacity && !arr[index*2].empty) // left child only
        {
          arr[index].obj = arr[index*2].obj;
          index*=2;
          erasing = true;
        }
        else // right child only
        {
          arr[index].obj = arr[index*2+1].obj;
          index=index*2+1;
          erasing = true;
        }
      }

    virtual T & find(const T & obj)
    {
      int index = 1;
      while(index <= current_capacity && !arr[index].empty)
      {
        if(arr[index].obj < obj)
        {
          index*=2;
        }
        else if(arr[index].obj > obj)
        {
          index = index*2+1;
        }
        else /* we found the item to delete */
        {
          break;
        }
      }
      if(index > current_capacity) // item not found
      {
        throw FailedFindException();
      }
      else return arr[index];
    }

    }
    virtual ~dense_bst()
    {
      delete[] arr;
    }

    /*
      TODO
        - add multithreaded cleanup? don't want to hurt performance but if we delete all leaves in a level, we may as well free the memory
    */
};
