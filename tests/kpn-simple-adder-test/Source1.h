#ifndef SOURCE1_H
#define SOURCE1_H

#include "Component.h"
#include "IntToken.h"

using namespace sacre;

class Source1: public Component
{
 public:
  Source1(std::string);
  virtual void* task(void*);
};

Source1::Source1(std::string _name): Component(_name)
{
  addOutPort<int>("out");
}

void* Source1::task(void* nullarg)
{
  std::cout << "Source1's implementation of task thread." << std::endl;
  int data[] = {1, 2, 3, 4, 5};
  
  int i;
  for(i=0; i<5; i++)
    {
      this->outPort<int>("out")->write(data[i]);
      std::cout << this->name << " wrote "  << data[i] << std::endl;
    }

  return NULL;
}

#endif
