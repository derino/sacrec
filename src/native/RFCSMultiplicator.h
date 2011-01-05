#ifndef RFCSMULTIPLICATOR_H
#define RFCSMULTIPLICATOR_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include "Component.h"
#include "Token.h"

namespace sacre
{

  template <typename T, int N = 3>
    class RFCSMultiplicator: public Component
  {
  public:
    RFCSMultiplicator(std::string);
    virtual void* task(void*);
    ~RFCSMultiplicator();
  };
  
  template <typename T, int N>
    RFCSMultiplicator<T, N>::RFCSMultiplicator(std::string _name): Component(_name)
  {
    addInPort<T>("in");
    addInPort<T>("fault");
    for (int i=1; i<=N; i++)
      {
	std::stringstream str;
	str << i;
	addOutPort<T>("out" + str.str());
      }
  }
  
  template <typename T, int N>
    RFCSMultiplicator<T, N>::~RFCSMultiplicator()
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		    this->name << " is destructed."
		    );
    }
  
  template <typename T, int N>
    void* RFCSMultiplicator<T, N>::task(void* nullarg)
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacre"), 
		    this->name << "'s implementation of task thread."
		    );
      
      T tIn;

      while(true)
	{
	  //TODO: read fault port, if no fault, forward to first two, else forward to last two.
	  T tFault = this->inPort<T>("fault")->read();

	  if( !tFault.isFaultPresentToken() )
	    {
	      LOG4CXX_TRACE(Logger::getLogger("sacre"), 
			    this->name << " read no fault token"
			    );
	      // read data from input, copy and write to both outputs
	      tIn = this->inPort<T>("in")->read();
	      LOG4CXX_TRACE(Logger::getLogger("sacre"), 
			    this->name << " read "  << tIn.getData()
			    );
	      
	      for(int i=1; i<=N-1; i++)
		{
		  T tOut(tIn);
		  std::stringstream str;
		  str << i;
		  this->outPort<T>("out" + str.str())->write( tOut );
		  LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
				this->name << " wrote "  << tOut.getData()
				);
		}
	      
	    }
	  else // fault present token read
	    {
	      LOG4CXX_TRACE(Logger::getLogger("sacre"), 
			    this->name << " read fault present token"
			    );
	      for(int i=2; i<=N; i++)
		{
		  T tOut(tIn);
		  std::stringstream str;
		  str << i;
		  this->outPort<T>("out" + str.str())->write( tOut );
		  LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
				this->name << " wrote "  << tOut.getData()
				);
		}
	      
	    }
	}
      
      return NULL;
    }
}

#endif
