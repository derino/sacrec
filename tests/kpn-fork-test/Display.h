#ifndef DISPLAY_H
#define DISPLAY_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <pthread.h>
#include "Component.h"

using namespace sacre;

class Display: public Component
{
 public:
  Display(std::string);
  virtual void* task(void*);
  ~Display();
};

Display::Display(std::string _name): Component(_name)
{
  addInPort< Token<int> >("in");
}

Display::~Display()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << " is destructed."
		);
}

void* Display::task(void* nullarg)
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << "'s implementation of task thread."
		);
  //int i;
  //for(i=0; i<5; i++)
  while(1)
    {
      // read data from input and print
      Token<int> res = this->inPort< Token<int> >("in")->read();
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " read "  << res.getData()
		    );
    }

  return NULL;
}


#endif
