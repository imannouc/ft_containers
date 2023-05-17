#include <iostream>
#include <vector>
#include "vector.hpp"
#ifndef NS
# define NS std
#endif


int main ()
{
  NS::vector<int> myvector (3,100);
  NS::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );
  std::cout << "\nmyvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;

  myvector.insert (it,2,300);
  std::cout << "\nmyvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  NS::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());
  std::cout << "\nmyvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;



  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);
  std::cout << "\nmyvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

