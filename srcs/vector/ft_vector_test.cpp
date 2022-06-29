#include <vector>
// #include "vector.hpp"
#include <cstring>
#include <iostream>

int main(int ac, char **av) 
{
	std::vector<int> vec(10,9);

	std::cout << vec.capacity() << std::endl;
	vec.push_back(11);
	std::cout << vec.capacity() << std::endl;
	vec.resize(10);
	std::cout << vec.capacity() << std::endl;
	std::cout << vec.size() << std::endl;

	std::cout << vec[10] << std::endl;
}


// int		main()
// {
// 	ft::vector<int> vec1(10,69);
// 	ft::vector<int>::iterator iter1(vec1.begin());
// 	ft::vector<int>::iterator iter2(vec1.end());

// 	for (int i = 0 ; i < vec1.size() ; i++)
// 		std::cout << vec1[i] << std::endl;

// 	ft::vector<int> vec2 = vec1;

// 	for (int i = 0 ; i < vec2.size() ; i++)
// 		std::cout << vec2[i] << std::endl;


// 	ft::vector<int> vec3(iter1,iter2);

// 	for (; iter1 < iter2 ; iter1++)
// 		std::cout << *iter1 << std::endl;



	
// 	return 0;
// }