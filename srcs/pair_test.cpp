#include <utility>      // std::pair
#include <iostream>     // std::cout
#include "pair.hpp"
int main () {
  ft::pair <int,int> foo;
  ft::pair <int,int> bar;

  foo = ft::make_pair (10,20);
  bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

  std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
  std::cout << "bar: " << bar.first << ", " << bar.second << '\n';

  ft::pair <std::string,double> product1;                     // default constructor
  ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
  ft::pair <std::string,double> product3 (product2);          // copy constructor

  product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

  product2.first = "shoes";                  // the type of first is string
  product2.second = 39.90;                   // the type of second is double

  std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
  std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
  std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

  ft::pair <std::string,int> planet, homeplanet;

  planet = ft::make_pair("Earth",6371);

  homeplanet = planet;

  std::cout << "Home planet: " << homeplanet.first << '\n';
  std::cout << "Planet size: " << homeplanet.second << '\n';

  std::pair<int,char> foo0 (10,'z');
  std::pair<int,char> bar0 (90,'a');

  if (foo0==bar0) std::cout << "foo0 and bar0 are equal\n";
  if (foo0!=bar0) std::cout << "foo0 and bar0 are not equal\n";
  if (foo0< bar0) std::cout << "foo0 is less than bar0\n";
  if (foo0> bar0) std::cout << "foo0 is greater than bar0\n";
  if (foo0<=bar0) std::cout << "foo0 is less than or equal to bar0\n";
  if (foo0>=bar0) std::cout << "foo0 is greater than or equal to bar0\n";

  return 0;
}
