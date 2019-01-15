/*

  tree.h
  Andrew Rosen Dec 2018
  Header file for generic tree.

*/

template <typename T>
class tree {
  protected:
    int number_of_elements;
  public:
    virtual bool insert(const T & obj) = 0;
    virtual bool contains(const T & obj) = 0;
    virtual bool erase(const T & obj) = 0;
    virtual int size() { return number_of_elements; }
    virtual bool empty() { return number_of_elements == 0; }
};
