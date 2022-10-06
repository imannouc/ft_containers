#include "enable_if.hpp"
#include "is_integral.hpp"
#include <iostream>
#include <type_traits>

template<class T, class = typename ft::enable_if<std::is_unsigned<T>::value>::type>
void f(T)
{
    std::cout << "is unsigned" << std::endl;
}

int main() {
  std::cout << std::boolalpha;
  std::cout << "is_integral:" << std::endl;
  std::cout << "\tchar: " << ft::is_integral<char32_t>::value << std::endl;
  std::cout << "\tint: " << ft::is_integral<int>::value << std::endl;
  std::cout << "\tfloat: " << ft::is_integral<float>::value << std::endl;


  unsigned long y;
  f(y);
  return 0;
}
