#include <iostream>

#include "Source2.h"

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
      // write out data
      channels["out"]->write(&data[i]);
      //channels["sharedcount"]->write( channels["sharedcount"]->read()+1 );
      //s2a.write(data[i]);
      //printf("%s : step %d \n", thread_name, i);
    }
  
  //printf("Finished: %s \n", thread_name);
  return NULL;
}
