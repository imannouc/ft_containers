#include <vector>
#include <iostream>

#include "vector.hpp"

int main()
{
    std::vector<int> vect1;
    // int num (9);

    // std::cout << num ;
    // std::cout << vect1.size() << std::endl;
    // std::cout << vect1.capacity() << std::endl;
    // std::cout << !vect1.empty() << std::endl;
    // std::cout << vect1.max_size() << std::endl;

    // int *pointer;
    // std::allocator<int> alloc;
    // size_t size = 10;

    // pointer = alloc.allocate(5);
    // for (int i = 0 ; i < size ; i++)
    //     alloc.construct(&pointer[i],100);
    // for (int i = 0 ; i < size ; i++)
    //     std::cout << pointer[i] << '-';
    // std::cout << std::endl;

    ft::vector<int> empty;
    ft::vector<int> fill(10,69);

    // std::cout << fill.size() << std::endl;
    for (int i = 0 ; i < fill.size() ; i++)
    {
        std::cout << fill[i] << std::endl;
    }

    std::cout << empty.size() << std::endl;
    std::cout << empty.capacity() << std::endl;
    std::cout << empty.empty() << std::endl;
    std::cout << empty.max_size() << std::endl;


}