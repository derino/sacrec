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
  addChannel<int>("out");
  //addSharedVariable("sharedcount");
}

void* Source2::task(void* nullarg)
{
  std::cout << "Source2's implementation of task thread." << std::endl;
  int data[] = {6, 7, 8, 9, 10};
  
  int i;
  for(i=0; i<5; i++)
    {
      IntToken* it = new IntToken(data[i]);
      // write out data
      //      channels["out"]->write(&data[i]);
      channels["out"]->write(it);
      std::cout << this->name << " wrote "  << it->getData() << std::endl;
      //channels["sharedcount"]->write( channels["sharedcount"]->read()+1 );

      //s1a.write(data[i]);
      //printf("%s : step %d \n", thread_name, i);
    }
  
  //printf("Finished: %s \n", thread_name);
  return NULL;
}

#endif
