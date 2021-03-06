#ifndef ROUTER_H
#define ROUTER_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include "Component.h"
#include "Token.h"

namespace sacre
{
  
  template <typename T, int N>
    class Router: public Component
  {
  public:
    Router(std::string);
    virtual void* task(void*);
    ~Router();
    
  private:
    int iterator;
  };
  
  template <typename T, int N>
    Router<T, N>::Router(std::string _name): Component(_name)
  {
    addInPort<T>("in");
    for (int i=1; i<=N; i++)
      {
	std::stringstream str;
	str << i;
	addOutPort<T>("out" + str.str());
      }
    
    iterator = 1;
  }
  
  template <typename T, int N>
    Router<T, N>::~Router()
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		    this->name << " is destructed."
		    );
    }
  
  template <typename T, int N>
    void* Router<T, N>::task(void* nullarg)
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		    this->name << "'s implementation of task thread."
		    );
      
      while(true)
	{
	  // read data from input, copy and write to output, i.e. forward token to output ports sequentially
	  T tIn = this->inPort<T>("in")->read();
	  LOG4CXX_TRACE(Logger::getLogger("sacre"), 
			this->name << " read "  << tIn.getData()
			);
	  
	  T tOut(tIn);
	  std::stringstream str;
	  str << iterator++;
	  this->outPort<T>("out" + str.str())->write( tOut );
	  LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
			this->name << " wrote "  << tOut.getData()
			);

	  if(iterator == N+1)
	    iterator = 1;
	  
	}
      
      return NULL;
    }
}

#endif
