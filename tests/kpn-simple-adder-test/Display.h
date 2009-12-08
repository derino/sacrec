#ifndef DISPLAY_H
#define DISPLAY_H

#include <pthread.h>
#include "Component.h"

using namespace sacre;

class Display: public Component
{
 public:
  Display(std::string);
  virtual void* task(void*);
  ~Display();
};

Display::Display(std::string _name): Component(_name)
{
  addInPort<int>("in");
}

Display::~Display()
{
  //  std::cout << "Display is destructed." << std::endl;
}

void* Display::task(void* nullarg)
{
  std::cout << "Display's implementation of task thread." << std::endl;

  int i;
  for(i=0; i<5; i++)
    {
      // read data from input and print
      int res = this->inPort<int>("in")->read();
      std::cout << this->name << " read "  << res << std::endl;
    }

  return NULL;
}


#endif
