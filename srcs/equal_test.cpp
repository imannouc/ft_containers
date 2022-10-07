#include <iostream>     // std::cout
#include <algorithm>    // std::equal
#include <vector>       // std::vector
#include <cctype>       // std::tolower
#include "vector.hpp"
#include "equal.hpp"

bool mypredicate (int i, int j) {
  return (i==j);
}

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{
  return std::tolower(c1)<std::tolower(c2);
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



    char foo[]="Apple";
    char bar[]="apartment";

    std::cout << std::boolalpha;

    std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

    std::cout << "Using default comparison (operator<): ";
    std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
    std::cout << '\n';

    std::cout << "Using mycomp as comparison object: ";
    std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
    std::cout << '\n';
  return 0;
}
