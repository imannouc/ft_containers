#include <vector>
#include <iostream>

#include "vector.hpp"
#include <iterator>

class Myiterator : std::iterator<std::random_access_iterator_tag,int>
{
    private:
        int *p;
    public:
        Myiterator(int *x) : p(x){};
        Myiterator(const Myiterator & rhs) : p(rhs.p) {};
        Myiterator & operator++(){
            ++p;
            return (*this);
        };
        Myiterator operator++(int){
            Myiterator tmp = *this;
            ++p;
            return tmp;
        }
        int & operator*()
        {
            return (*p);
        };
        bool operator!=(const Myiterator & rhs)
        {
            return (p != rhs.p);
        };
        bool operator==(const Myiterator & rhs)
        {
            return (p == rhs.p);
        };

        ~Myiterator(){};
};

int main()
{
    std::vector<int> vect1(3,420);
    std::vector<int>::iterator iter = vect1.begin();
    std::vector<int>::iterator end = vect1.end();

    int *pointer;
    std::allocator<int> alloc;
    size_t size = 10;

    pointer = alloc.allocate(5);
    Myiterator it(pointer);
    Myiterator it2(pointer + 10);
    for (int i = 0 ; i < size ; i++)
        alloc.construct(&pointer[i],i);
    for (; it != it2 ; it++)
        *it = 133;
    for (int i = 0 ; i < size ; i++)
        std::cout << pointer[i] << '-';
    std::cout << std::endl;


    for (; it != it2 ; it++)
        std::cout << *it << std::endl;

    std::cout << vect1.size() << std::endl;
    std::cout << vect1.capacity() << std::endl;
    std::cout << !vect1.empty() << std::endl;
    std::cout << vect1.max_size() << std::endl;

    ft::vector<int> empty;
    // ft::vector<int> fill(10,69);

    // // std::cout << fill.size() << std::endl;
    // for (int i = 0 ; i < fill.size() ; i++)
    // {
    //     std::cout << fill[i] << std::endl;
    // }

    std::cout << empty.size() << std::endl;
    std::cout << empty.capacity() << std::endl;
    std::cout << empty.empty() << std::endl;
    std::cout << empty.max_size() << std::endl;
}