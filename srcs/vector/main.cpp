#include <vector>
#include <iostream>

int main()
{
    std::vector<int> vect1;
    int num (9);

    std::cout << num ;
    std::cout << vect1.size() << std::endl;
    std::cout << vect1.capacity() << std::endl;
    std::cout << !vect1.empty() << std::endl;
    std::cout << vect1.max_size() << std::endl;

}