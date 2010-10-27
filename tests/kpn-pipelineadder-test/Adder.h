#ifndef ADDER_H
#define ADDER_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include "Component.h"

using namespace sacre;

class Adder: public Component
{
 public:
  Adder(std::string);
  virtual void* task(void*);
  ~Adder();
};

Adder::Adder(std::string _name): Component(_name)
{
  addInPort<int>("in1");
  addInPort<int>("in2");
  addOutPort<int>("out");
}

Adder::~Adder()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << " is destructed."
		);
}

void* Adder::task(void* nullarg)
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << "'s implementation of task thread."
		);

  int i;
  for(i=0; i<5; i++)
    {
      // read data from source 1 and source 2 and write out sum
      int t1 = this->inPort<int>("in1")->read();
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " read "  << t1
		    );

      int t2 = this->inPort<int>("in2")->read();
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " read "  << t2
		    );
      
      int sum = t1 + t2;
      this->outPort<int>("out")->write(sum);
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " wrote "  << sum
		    );
    }

  return NULL;
}


#endif
