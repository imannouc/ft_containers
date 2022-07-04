#include <vector>
#include "vector.hpp"
#include <cstring>
#include <iostream>

int main(int ac, char **av) 
{
	ft::vector<int> vec(10,9);

	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';
	std::cout << '\n';
	vec.resize(5);
	std::cout << "resize 5 :\n";
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';
	std::cout << '\n';
	std::cout << "size : " << vec.size() << " capacity :" << vec.capacity() << "\n";

	vec.resize(18,100);
	std::cout << "resize 18,100 :\n";

	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';
	std::cout << '\n';

	vec.resize(12);
	std::cout << "resize 12 :\n";

	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';
	std::cout << '\n';
	vec.resize(19);
	std::cout << "resize 19:\n";
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';
	std::cout << '\n';
	std::cout << "size : " << vec.size() << " capacity :" << vec.capacity() << "\n";

	// ft::vector<int> vec(10,9);

	// std::cout << "capacity "<< vec.capacity() << std::endl;
	// vec.reserve(20);
	// std::cout << "capacity "<<  vec.capacity() << std::endl;
	// std::cout << "size "<< vec.size() << std::endl;
	// vec.reserve(30);
	// std::cout << "capacity "<< vec.capacity() << std::endl;
	// std::cout << vec[9] << std::endl;
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