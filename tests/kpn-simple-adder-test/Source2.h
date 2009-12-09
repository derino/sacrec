#ifndef SOURCE2_H
#define SOURCE2_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Component.h"
#include "IntToken.h"

using namespace sacre;

class Source2: public Component
{
 public:
  Source2(std::string);
  virtual void* task(void*);
  ~Source2();
};

Source2::Source2(std::string _name): Component(_name)
{
  addOutPort<int>("out");
}

Source2::~Source2()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << " is destructed."
		);
}

void* Source2::task(void* nullarg)
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << "'s implementation of task thread."
		);

  int data[] = {6, 7, 8, 9, 10};
  
  int i;
  for(i=0; i<5; i++)
    {
      this->outPort<int>("out")->write( data[i] );
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " wrote "  << data[i]
		    );
    }
  
  return NULL;
}

#endif
