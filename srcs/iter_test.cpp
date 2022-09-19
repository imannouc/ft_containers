#include <iostream>     // std::cout
#include <iterator>     // std::reverse_iterator
#include <vector>       // std::vector
#include "iterator.hpp"

int main () {
	std::vector<int> myvector;
	int v[10] = {0,1,2,3,4,5,6,7,8,9};
	for (int i=0; i<10; i++) myvector.push_back(v[i]);	// myvector: 0 1 2 3 4 5 6 7 8 9
	typedef std::vector<int>::iterator iter_type;

	ft::MyIterator<int *> myit(v);
	ft::MyIterator<int *> myit2(v + 10);
	iter_type iter1;
	iter_type iter2;

  	iter1 = myvector.begin();
	iter2 = myvector.begin() + 2;

	std::cout << *iter1 << std::endl;
	std::cout << *iter2 << std::endl;

	// for (ft::MyIterator<int *> it0(v) ; it0 != myit2; ++it0)
		std::cout << "myit " << *(myit) << std::endl;
		std::cout << "++myit " << *(++myit) << std::endl;
		std::cout << "--myit " << *(--myit) << std::endl;
		std::cout << "myit++ " << *(myit++) << std::endl;
		std::cout << "myit-- " << *(myit--) << std::endl;
		std::cout << "myit " << *(myit) << std::endl;
	std::cout << *myit << std::endl;
	std::cout << myit[(myit2 - (myit2 - 5))] << std::endl;

  return 0;
}