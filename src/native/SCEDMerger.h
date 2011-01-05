#ifndef SCEDMERGER_H
#define SCEDMERGER_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include "Component.h"
#include "Token.h"

namespace sacre
{

  template <typename T, int N>
    class SCEDMerger: public Component
  {
  public:
    SCEDMerger(std::string);
    virtual void* task(void*);
    ~SCEDMerger();
  };
  
  template <typename T, int N>
    SCEDMerger<T, N>::SCEDMerger(std::string _name): Component(_name)
  {
    for (int i=1; i<=N; i++)
      {
	std::stringstream str;
	str << i;
	addInPort<T>("in" + str.str());
      }
    addOutPort<T>("out");
  }
  
  template <typename T, int N>
    SCEDMerger<T, N>::~Merger()
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		    this->name << " is destructed."
		    );
    }
  
  template <typename T, int N>
    void* SCEDMerger<T, N>::task(void* nullarg)
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		    this->name << "'s implementation of task thread."
		    );
      
      while(true)
	{
	  // read data from all input ports, copy and write to the output port sequentially	  
	  for(int i=1; i<=N; i++)
	    {
	      std::stringstream str;
	      str << i;
	      T tIn = this->inPort<T>("in" + str.str())->read();
	      LOG4CXX_TRACE(Logger::getLogger("sacre"), 
			    this->name << " read "  << tIn.getData()
			    );

	      T tOut(tIn);
	      this->outPort<T>("out")->write( tOut );
	      LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
			    this->name << " wrote "  << tOut.getData()
			    );
	    }
	}
      
      return NULL;
    }
}

#endif
