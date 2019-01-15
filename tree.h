/*

  tree.h
  Andrew Rosen Dec 2018
  Header file for generic tree.

*/

template <typename T>
class tree {
  private:
    int number_of_elements;
  public:
    virtual bool insert(T & obj) = 0;
    virtual bool contains(T & obj) = 0;
    virtual T find(T & obj) = 0;
    virtual bool erase(T & obj) = 0;
    virtual int size() { return number_of_elements; }
    virtual bool empty() { return number_of_elements == 0; }
};
