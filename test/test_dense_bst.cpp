/*

  test_dense_bst.cpp
  Andrew Rosen Dec 2018
  CPP file for testing dense binary search tree.

*/

#include "../include/dense_bst.h"
#include <iostream>

int main()
{
  dense_bst<int> dbst;
  dbst.insert(1);
  dbst.insert(-20);
  dbst.insert(-30);
  dbst.insert(0);
  std::cout << dbst.insert(0) << std::endl;
  std::cout << dbst.contains(0) << std::endl;
}
