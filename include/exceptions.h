/*

  exceptions.h
  Andrew Rosen Dec 2018
  Header file for sparse binary search tree.

*/

#include <exception>

struct FailedFindException : public std::exception {
   const char * what () const throw () {
      return "Failed to find an object after find() call.";
   }
};
