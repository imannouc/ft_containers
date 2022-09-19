#include <vector>
#include <iostream>

#include "vector.hpp"
#include <iterator>
#include <vector>

void print(int x){
    std::cout << "int\n";
    std::cout << x << std::endl;
}

template <typename T>
void print(T x){
    std::cout << "T" << std::endl;
    std::cout << x << '\n';
}
#include <stack>
#include <string>
#include <algorithm>

int main()
{
    ft::vector<int> v;
    std::stack<int> s;
    std::string youlam = "you haja wtf";
    std::string youlamSubStr = youlam.substr(0,3);
    

    youlamSubStr += " are amazing";
    youlam += youlamSubStr;
    std::cout <<"youlam siize :" <<youlamSubStr  << '\n';
    std::cout << v.size() << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
        std::cout << "size" <<v.size() << std::endl;
        std::cout << "capcaity "<<v.capacity() << std::endl;
    }
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << v[i] <<  std::endl;
    }


    return(0);
}