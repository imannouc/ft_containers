#include <iostream>
#include <vector>
#include "vector.hpp"

int main ()
{
    std::vector<int> myvector;

    for (int i=1; i<=10; i++) myvector.push_back(i);
    // myvector.erase(myvector.begin() + 29);
    for (int i = 0 ; i < myvector.size() ; i++)
    {

        std::cout << " size is " << myvector.size() << '\n';
        std::cout << *myvector.erase (myvector.begin() + i) << '\n';
        i--;
        for (unsigned i=0; i<myvector.size(); ++i)
          std::cout << ' ' << myvector[i];

        std::cout << " size is " << myvector.size() << '\n';
    }

//   std::cout << *myvector.erase (myvector.end() - 5 , myvector.end());

//   myvector.erase (myvector.begin(),myvector.begin()+3);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}
