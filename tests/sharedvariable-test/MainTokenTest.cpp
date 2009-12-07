#include <iostream>

#include "IntToken.h"

using namespace std;

int main()
{
  sacre::IntToken it(5);

  sacre::IntToken a = it;

  cout << a.getData() << endl;


  sacre::IntToken it2(5);

  sacre::IntToken a2(6);

  a2 = it2;
  cout << a2.getData() << endl;
}
