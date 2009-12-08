#ifndef ADDER_H
#define ADDER_H

#include <iostream>
#include "Component.h"

using namespace sacre;

class Adder: public Component
{
 public:
  Adder(std::string);
  virtual void* task(void*);
};

Adder::Adder(std::string _name): Component(_name)
{
  addInPort<int>("in1");
  addInPort<int>("in2");
  addOutPort<int>("out");
}

void* Adder::task(void* nullarg)
{
  std::cout << "Adder's implementation of task thread." << std::endl;

  int i;
  for(i=0; i<5; i++)
    {
      // read data from source 1 and source 2 and write out sum
      int t1 = this->inPort<int>("in1")->read();
      std::cout << this->name << " read "  << t1 << std::endl;

      int t2 = this->inPort<int>("in2")->read();
      std::cout << this->name << " read "  << t2 << std::endl;

      int sum = t1 + t2;
      this->outPort<int>("out")->write(sum);
      std::cout << this->name << " wrote "  << sum << std::endl;
    }

  return NULL;
}


#endif
