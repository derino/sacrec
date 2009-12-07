#ifndef DISPLAY_H
#define DISPLAY_H

#include "Component.h"

using namespace sacre;

class Display: public Component
{
 public:
  Display(std::string);
  virtual void* task(void*);
};

Display::Display(std::string _name): Component(_name)
{
  addChannel<int>("in");
  //addSharedVariable("sharedcount");
}

void* Display::task(void* nullarg)
{
  std::cout << "Display's implementation of task thread." << std::endl;

  int i;
  for(i=0; i<5; i++)
    {
      // read data from input and print
      //printf("%s : step %d \n", thread_name, i);
      //printf("Result: %d \n", as.read());

      IntToken** it = new IntToken*;//(111);
      channels["in"]->read((Token**)it);
      std::cout << this->name << " read "  << (*it)->getData() << std::endl;
      /*int** t_a = new int*;
      void** a = (void**)t_a;
      channels["in"]->read(a);
      int* tt_a = (int*)*a;
      std::cout << this->name << " read "  << *tt_a << std::endl;*/
      //std::cout << "Result: " << *tt_a << std::endl;
      
      //channels["sharedcount"]->write( channels["sharedcount"]->read()+1 );
    }

  //std::cout << channels["sharedcount"]->read();
  //    printf("Finished: %s \n", thread_name);
  return NULL;
}


#endif
