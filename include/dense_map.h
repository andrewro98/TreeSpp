/*

  dense_map.h
  Andrew Rosen Dec 2018
  Header file for map represented by dense binary search tree.

*/

#include "dense_bst.h"

template <typename K, typename V>
class dense_pair;

template <typename K, typename V>
class dense_map {
    dense_bst< dense_pair<K,V> > bst;
  public:
    int size() { return bst.size(); }
    bool empty() { return bst.size() == 0; }
    V & operator[](const K & key)
    {
      try{
        return bst.find(key).value;
      } catch (FailedFindException & e)
      {
        bst.insert(sparse_pair<K,V>(key, V()));
        return bst.find(key);
      }
    }
    void insert(const K & key, const V & val)
    {
      if(!bst.insert(sparse_pair<K,V>(key, val)))
      {
        // duplicates
        bst.find(key).value = val;
      }
    }
    void erase(const K & key)
    {
      bst.erase(sparse_pair<K,V>(key, V()));
    }
};

template <typename K, typename V>
class dense_pair {
  friend class dense_map<K,V>;
  protected:
    K key;
    V value;
  public:
    dense_pair<K,V>(const K & _key, const V & _val):key(_key), value(_val) {}
    bool operator==(const dense_pair & rhs)
    {
      return key == rhs.key;
    }
    bool operator<(const dense_pair & rhs)
    {
      return key < rhs.key;
    }
    bool operator>(const dense_pair & rhs)
    {
      return key > rhs.key;
    }
    K get_key() { return key; }
    V get_value() { return value; }
  };
