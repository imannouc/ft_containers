#include <vector>
#include <iostream>

#include "vector.hpp"
#include <iterator>

çtemplate <class T>
void    print(T toprint)
{
    std::cout << toprint << std::endl;
}

int main()
{
    // std::vector<int> vect1(3,420);
    // std::vector<int>::iterator iter = vect1.begin();
    // std::vector<int>::iterator end = vect1.end();

    // int *pointer;
    // std::allocator<int> alloc;
    // size_t size = 10;

    // pointer = alloc.allocate(5);
    // Myiterator it(pointer);
    // Myiterator it2(pointer + 10);
    // for (int i = 0 ; i < size ; i++)
    //     alloc.construct(&pointer[i],i);
    // for (; it != it2 ; it++)
    //     *it = 133;
    // for (int i = 0 ; i < size ; i++)
    //     std::cout << pointer[i] << '-';
    // std::cout << std::endl;


    // for (; it != it2 ; it++)
    //     std::cout << *it << std::endl;

    // std::cout << vect1.size() << std::endl;
    // std::cout << vect1.capacity() << std::endl;
    // std::cout << !vect1.empty() << std::endl;
    // std::cout << vect1.max_size() << std::endl;

    ft::vector<int> empty;
    ft::vector<int> fill(10,69);
    //enable_if

    // fill = empty;
    // std::cout << fill.size() << std::endl;
    // for (int i = 0 ; i < fill.size() ; i++)
    // {
    //     std::cout << fill[i] << std::endl;
    // }

    // std::cout << fill.size() << std::endl;
    // std::cout << fill.capacity() << std::endl;
    // std::cout << fill.empty() << std::endl;
    // std::cout << fill.max_size() << std::endl;
    int a[16] = {4,4,4,4,4,-1,4};
    std::vector<int> v(a , a + 10);
    a[17] = 19;
    
    print<std::string>("string test");
    print(10000);
    std::cout << a[17] << std::endl;

    for (int i = 0; i < v.size() ; i++){
        std::cout << v[i] << std::endl;
    }
    std::cout << std::endl;
    for (auto i : v)
        std::cout << i << std::endl;

    for (std::vector<int>::iterator it = v.begin(); it != v.end() ; it++)
        std::cout << *it;

}