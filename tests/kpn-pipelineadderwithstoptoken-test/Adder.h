#ifndef ADDER_H
#define ADDER_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include "Component.h"
#include "Token.h"

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
  addInPort< Token<int> >("in1");
  addInPort< Token<int> >("in2");
  addOutPort< Token<int> >("out");
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

  //  int i;
  //for(i=0; i<5; i++)
  while(1)
    {
      // read data from source 1 and source 2 and write out sum
      Token<int> t1 = this->inPort< Token<int> >("in1")->read();
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " read "  << t1.getData()
		    );

      Token<int> t2 = this->inPort< Token<int> >("in2")->read();
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " read "  << t2.getData()
		    );
      
      int sum = t1.getData() + t2.getData();
      Token<int> tsum(sum);
      this->outPort< Token<int> >("out")->write( tsum );
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " wrote "  << sum
		    );
    }

  return NULL;
}


#endif
