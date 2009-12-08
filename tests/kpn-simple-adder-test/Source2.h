#ifndef SOURCE2_H
#define SOURCE2_H

#include "Component.h"
#include "IntToken.h"

using namespace sacre;

class Source2: public Component
{
 public:
  Source2(std::string);
  virtual void* task(void*);
};

Source2::Source2(std::string _name): Component(_name)
{
  addOutPort<int>("out");
}

void* Source2::task(void* nullarg)
{
  std::cout << "Source2's implementation of task thread." << std::endl;
  int data[] = {6, 7, 8, 9, 10};
  
  int i;
  for(i=0; i<5; i++)
    {
      this->outPort<int>("out")->write( data[i] );
      std::cout << this->name << " wrote "  << data[i] << std::endl;
    }
  
  return NULL;
}

#endif
