#ifndef ADDER_H
#define ADDER_H

#include <iostream>
#include "Component.h"
//#include "IntToken.h"

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

  //  addChannel<int>("in1");
  //addChannel<int>("in2");
  //addChannel<int>("out");
}

void* Adder::task(void* nullarg)
{
  std::cout << "Adder's implementation of task thread." << std::endl;

  //int data[5];
  
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

      
      /* /\*int** t_a = new int*; */
      /* void** a  = (void**)t_a; */
      /* channels["in1"]->read(a); */
      /* int* tt_a = (int*)*a;*\/ */
      /* IntToken** it_a = new IntToken*;//(10); */
      /* channels["in1"]->read((Token**)it_a); */


      /* /\*int** t_b = new int*; */
      /* void** b = (void**)t_b; */
      /* channels["in2"]->read(b); */
      /* int* tt_b = (int*)*b;*\/ */
      /* IntToken** it_b = new IntToken*;//(10); */
      /* channels["in2"]->read((Token**)it_b); */

      /* IntToken* res = new IntToken( (*it_a)->getData() + (*it_b)->getData() ); */
      /* //\*res = *tt_a + *tt_b; */

      /* channels["out"]->write( res ); */
      /* std::cout << this->name << " wrote "  << res->getData() << std::endl; */

      /* //channels["sharedcount"]->write( channels["sharedcount"]->read()+1 ); */
      /* //data[i] = s1a.read() + s2a.read(); */
      /* //printf("%s : step %d \n", thread_name, i); */
      
      /* //as.write(data[i]); */
    }

  //printf("Finished: %s \n", thread_name);
  return NULL;
}


#endif
