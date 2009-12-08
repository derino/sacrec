#include <iostream>

#include "Display.h"

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

      int** t_a = new int*;
      void** a = (void**)t_a;
      channels["in"]->read(a);
      int* tt_a = (int*)*a;
      std::cout << "Result: " << *tt_a << std::endl;
      //channels["sharedcount"]->write( channels["sharedcount"]->read()+1 );
    }

  //std::cout << channels["sharedcount"]->read();
  //    printf("Finished: %s \n", thread_name);
  return NULL;
}
