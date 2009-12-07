#include <iostream>

#include "Source1.h"

Source1::Source1(std::string _name): Component(_name)
{
  addChannel<int>("out");
  //addSharedVariable("sharedcount");
}

void* Source1::task(void* nullarg)
{
  std::cout << "Source1's implementation of task thread." << std::endl;
  int data[] = {1, 2, 3, 4, 5};
  
  int i;
  for(i=0; i<5; i++)
    {
      // write out data
      channels["out"]->write(&data[i]);
      //channels["sharedcount"]->write( channels["sharedcount"]->read()+1 );

      //s1a.write(data[i]);
      //printf("%s : step %d \n", thread_name, i);
    }
  
  //printf("Finished: %s \n", thread_name);
  return NULL;
}
