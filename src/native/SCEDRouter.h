#ifndef SCEDROUTER_H
#define SCEDROUTER_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include "Component.h"
#include "Token.h"

namespace sacre
{
  // N includes also the redundant component instance
  template <typename T, int N>
    class SCEDRouter: public Component
  {
  public:
    SCEDRouter(std::string);
    virtual void* task(void*);
    ~SCEDRouter();
    
  private:
    int iterator;
  };
  
  template <typename T, int N>
    SCEDRouter<T, N>::SCEDRouter(std::string _name): Component(_name)
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
    SCEDRouter<T, N>::~SCEDRouter()
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		    this->name << " is destructed."
		    );
    }
  
  template <typename T, int N>
    void* SCEDRouter<T, N>::task(void* nullarg)
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		    this->name << "'s implementation of task thread."
		    );
      
      while(true)
	{
	  // read data from input, copy and write to output, i.e. forward token to output ports sequentially
	  T tIn = this->inPort<T>("in")->read();
	  LOG4CXX_TRACE(Logger::getLogger("application"), 
			this->name << " read "  << tIn.getData()
			);
	  
	  T tOut(tIn);
	  std::stringstream str;
	  str << iterator++;
	  this->outPort<T>("out" + str.str())->write( tOut );
	  LOG4CXX_TRACE(Logger::getLogger("application"), 
			this->name << " wrote "  << tOut.getData()
			);
	  if(iterator == N) // exclude redundant instance
	    iterator = 1;

	  T tOut2(tIn);
	  std::stringstream str2;
	  str2 << N;
	  this->outPort<T>("out" + str2.str())->write( tOut2 );
	  LOG4CXX_TRACE(Logger::getLogger("application"), 
			this->name << " wrote "  << tOut2.getData()
			);
	  
	}
      
      return NULL;
    }
}

#endif
