#ifndef SCEDMERGER_H
#define SCEDMERGER_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include "Component.h"
#include "Token.h"

namespace sacre
{
  // N-th component is the redundant instance
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
      LOG4CXX_DEBUG(Logger::getLogger("application"), 
		    this->name << "'s implementation of task thread."
		    );
      
      int iterator = 1;
      bool firstMismatch = false;

      while(true)
	{
	  // read sequentially
	  std::stringstream str;
	  str << iterator;
	  T tIn = this->inPort<T>("in" + str.str())->read();
	  LOG4CXX_TRACE(Logger::getLogger("application"), 
			this->name << " read "  << tIn.getData()
			);
	  
	  // read port from the redundant instance
	  std::stringstream str2;
	  str2 << N;
	  T tIn2 = this->inPort<T>("in" + str2.str())->read();
	  LOG4CXX_TRACE(Logger::getLogger("application"), 
			this->name << " read "  << tIn2.getData()
			);
	  
	  // allow error propagation, we choose the result from the parallel instance by default
	  T* resT = &tIn;

	  if ( tIn.getData() != tIn2.getData() )
	    {
	      if(firstMismatch)
		{
		  // this is the second mismatch => redundant instance faulty
		  resT = &tIn;
		  LOG4CXX_TRACE(Logger::getLogger("application"), this->name << " in" << N << " faulty" );
		}
	      else
		{ 
		  firstMismatch = true;
		  LOG4CXX_TRACE(Logger::getLogger("application"), this->name << " Either in" << iterator << " or in" << N << " is faulty" );
		}
	    }
	  else
	    {
	      if(firstMismatch)
		{
		  // (iterator-1)-th component (previous component) faulty
		  resT = &tIn2;
		  LOG4CXX_TRACE(Logger::getLogger("application"), this->name << " in" << iterator-1 << " faulty" );
		}

	      firstMismatch = false;
	    }


	  iterator++;
	  if (iterator == N) // exclude redundant instance
	    iterator = 1;
	    
	  T tOut(*resT);
	  this->outPort<T>("out")->write( tOut );
	  LOG4CXX_TRACE(Logger::getLogger("application"), 
			this->name << " wrote "  << tOut.getData()
			);
	}
      
      return NULL;
    }
}

#endif
