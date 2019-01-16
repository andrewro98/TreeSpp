/*

  test_sparse_bst.cpp
  Andrew Rosen Dec 2018
  CPP file for testing sparse binary search tree.

*/

#include "../include/sparse_bst.h"
//#include <iostream>

int main()
{
  sparse_bst<int> sbst;
  sbst.insert(1);
  sbst.insert(-20);
  sbst.insert(-30);
  sbst.insert(0);
  std::cout << sbst.insert(0) << std::endl;
  std::cout << sbst.contains(0) << std::endl;
  std::cout << sbst.find(-30) << std::endl;
  const sparse_elt<int> * root = sbst.get_root();
  std::cout << sbst.inorder(root, " ") << std::endl;
  std::cout << sbst.inorder(root, ", ") << std::endl;
  std::cout << sbst.erase(-20) << std::endl;
  std::cout << sbst.inorder(root, ", ") << std::endl;
  std::cout << sbst.erase(0) << std::endl;
  std::cout << sbst.inorder(root, ", ") << std::endl;
  std::cout << sbst.erase(1) << std::endl;
  std::cout << sbst.inorder(root, ", ") << std::endl;
  std::cout << sbst.erase(-30) << std::endl;
  std::cout << sbst.inorder(root, ", ") << std::endl;
}
