#include <iostream>     // std::cout
#include <iterator>     // std::reverse_iterator
#include <vector>       // std::vector
#include "vector.hpp"

int main () {
  ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  ft::reverse_iterator<ft::vector<int>::iterator> from,until;

  from = myvector.rbegin();
  until = myvector.rend();

  std::cout << "myvector has " << (until-from) << " elements.\n";

  return 0;
}
