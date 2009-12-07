#include <iostream>

#include "Adder.h"

Adder::Adder(std::string _name): Component(_name)
{
  addChannel<int>("in1");
  addChannel<int>("in2");
  addChannel<int>("out");
  //addSharedVariable("sharedcount");
}

void* Adder::task(void* nullarg)
{
  std::cout << "Adder's implementation of task thread." << std::endl;

  //int data[5];
  
  int i;
  for(i=0; i<5; i++)
    {
      // read data from source 1 and source 2 and write out sum
      int** t_a = new int*;
      void** a = (void**)t_a;
      channels["in1"]->read(a);
      int** t_b = new int*;
      void** b = (void**)t_b;
      channels["in2"]->read(b);
      int* res = new int;
      int* tt_a = (int*)*a;
      int* tt_b = (int*)*b;
      *res = *tt_a + *tt_b;
      channels["out"]->write( res );
      //channels["sharedcount"]->write( channels["sharedcount"]->read()+1 );
      //data[i] = s1a.read() + s2a.read();
      //printf("%s : step %d \n", thread_name, i);
      
      //as.write(data[i]);
    }

  //printf("Finished: %s \n", thread_name);
  return NULL;
}
