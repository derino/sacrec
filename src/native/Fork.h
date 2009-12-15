#ifndef FORK_H
#define FORK_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include "Component.h"
#include "Token.h"

using namespace sacre;

template <typename T, int N>
class Fork: public Component
{
 public:
  Fork(std::string);
  virtual void* task(void*);
  ~Fork();
};

template <typename T, int N>
  Fork<T, N>::Fork(std::string _name): Component(_name)
{
  addInPort<T>("in");
  for(int i=1; i<=N; i++)
    {
      std::stringstream str;
      str << i;
      addOutPort<T>("out" + str.str());
    }
  //addOutPort< Token<int> >("out2");
}

template <typename T, int N>
Fork<T, N>::~Fork()
{
  LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		this->name << " is destructed."
		);
}

template <typename T, int N>
void* Fork<T, N>::task(void* nullarg)
{
  LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		this->name << "'s implementation of task thread."
		);

  while(true)
    {
      // read data from input, copy and write to both outputs
      T tIn = this->inPort<T>("in")->read();
      LOG4CXX_TRACE(Logger::getLogger("sacre"), 
		    this->name << " read "  << tIn.getData()
		    );
      
      for(int i=1; i<=N; i++)
	{
	  T* tOut = new T(tIn);
	  std::stringstream str;
	  str << i;
	  this->outPort<T>("out" + str.str())->write( *tOut );
	  LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
			this->name << " wrote "  << tOut->getData()
			);
	}
    }

  return NULL;
}


#endif
