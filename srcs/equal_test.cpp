#include <iostream>     // std::cout
#include <algorithm>    // std::equal
#include <vector>       // std::vector
#include "vector.hpp"
#include "equal.hpp"

bool mypredicate (int i, int j) {
  return (i==j);
}

int main () {
  int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
  ft::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

    std::cout << myvector.capacity() << std::endl;
  // using default comparison:
  if ( ft::equal (myvector.begin(), myvector.end(), myints) )
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  myvector[3]=81;                                 // myvector: 20 40 60 81 100

  // using predicate comparison:
  if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  return 0;
}