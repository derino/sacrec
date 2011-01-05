#ifndef SOURCE1_H
#define SOURCE1_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Component.h"
#include "Token.h"
//#include "IntToken.h"

namespace sacre
{

class Source: public Component
{
 public:
  Source(std::string);
  virtual void* task(void*);
  ~Source();
};

Source::Source(std::string _name): Component(_name)
{
  addOutPort< Token<int> >("out");
}

Source::~Source()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << " is destructed."
		);
}

void* Source::task(void* nullarg)
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << "'s implementation of task thread."
		);

  int data[] = {1, 2, 3, 4, 5};
  
  int i;
  for(i=0; i<5; i++)
    {
      this->outPort< Token<int> >("out")->write( *(new Token<int>(data[i])) );
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " wrote "  << data[i]
		    );
    }

  return NULL;
}

}
#endif
