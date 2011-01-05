#ifndef RFCSCHECKER_H
#define RFCSCHECKER_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Component.h"
#include "Token.h"

namespace sacre
{

  template <typename T, int N = 3>
    class RFCSChecker: public Component
    {
    public:
    RFCSChecker(std::string);
    virtual void* task(void*);
    ~RFCSChecker();
    };
  
  template <typename T, int N>
    RFCSChecker<T, N>::RFCSChecker(std::string _name): Component(_name)
  {
    addInPort< Token<int> >("in1");
    addInPort< Token<int> >("in2");
    addInPort< Token<int> >("in3");
    addOutPort< Token<int> >("out");
    addOutPort< Token<int> >("fault");
  }
  
  template <typename T, int N>
    RFCSChecker<T, N>::~RFCSChecker()
  {
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  this->name << " is destructed."
		  );
  }
  
  template <typename T, int N>
    void* RFCSChecker<T, N>::task(void* nullarg)
  {
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  this->name << "'s implementation of task thread."
		  );
    
    //write one no_fault_present token so that multiplicator can start forwarding.
    this->outPort< Token<int> >("fault")->write( *(new Token<int>(NO_FAULT_TOKEN)) );
    LOG4CXX_TRACE(Logger::getLogger("application"), this->name << " wrote no fault" );
    
    while(true)
      {
	// read data from input and print
	Token<int> in1 = this->inPort< Token<int> >("in1")->read();
	Token<int> in2 = this->inPort< Token<int> >("in2")->read();
	//Token<int> in3 = this->inPort< Token<int> >("in3")->read();
	
	LOG4CXX_TRACE(Logger::getLogger("application"), 
		      this->name << " read "  << in1.getData() << " " << in2.getData()
		      );
	
	int resInt = 0;
	if( in1.getData() == in2.getData() )
	  {
	    resInt = in1.getData();
	    this->outPort< Token<int> >("fault")->write( *(new Token<int>(NO_FAULT_TOKEN)) );
	    LOG4CXX_TRACE(Logger::getLogger("application"), this->name << " wrote no fault" );
	  }
	else // if( in1.getData() != in2.getData() )
	  {
	    // connector bound will be limited to 1 automatically between RFCSMultiplicator and C1, C2, C3 because of the feedback connector (fault connector)!
	    
	    this->outPort< Token<int> >("fault")->write( *(new Token<int>(FAULT_PRESENT_TOKEN)) );
	    Token<int> in2Again = this->inPort< Token<int> >("in2")->read();
	    Token<int> in3 = this->inPort< Token<int> >("in3")->read();
	    
	    // check in1, in2Again and in3 as if they are from TMR
	    if ( in2Again.getData() != in3.getData() && in1.getData() == in3.getData() )
	      {
		// in2 faulty, in1 and in3 correct
		LOG4CXX_TRACE(Logger::getLogger("application"), this->name << " wrote in2 faulty" );
		resInt = in1.getData();
	      }
	    else if ( in2Again.getData() == in3.getData() )
	      {
		// in1 faulty, in2 and in3 correct
		LOG4CXX_TRACE(Logger::getLogger("application"), "in1 faulty" );
		resInt = in2Again.getData(); // TODO: we may reuse in2 and not have in2 recalculated
	      }
	    else 
	      {
		// in1, in2, in3 all different => against single fault assumption
		LOG4CXX_TRACE(Logger::getLogger("application"), "all results are different. against single fault assumption!" );
		resInt = NULL;
	      }
	  }
	
	this->outPort< Token<int> >("out")->write( *(new Token<int>(resInt)) );
	LOG4CXX_TRACE(Logger::getLogger("application"), 
		      this->name << " wrote "  << resInt
		      );

	this->outPort< Token<int> >("fault")->write( *(new Token<int>(NO_FAULT_TOKEN)) );
	LOG4CXX_TRACE(Logger::getLogger("application"), 
		      this->name << " wrote no fault"
		      );
      }//end while
    
    return NULL;
  }
  
}
#endif
