#ifndef MAJORITYVOTER_H
#define MAJORITYVOTER_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Component.h"
#include "Token.h"

namespace sacre
{

template <typename T, int N = 3>
  class MajorityVoter: public Component
  {
 public:
  MajorityVoter(std::string);
  virtual void* task(void*);
  ~MajorityVoter();
};

 template <typename T, int N>
   MajorityVoter<T, N>::MajorityVoter(std::string _name): Component(_name)
{
  addInPort< Token<int> >("in1");
  addInPort< Token<int> >("in2");
  addInPort< Token<int> >("in3");
  addOutPort< Token<int> >("out");
}

template <typename T, int N>
    MajorityVoter<T, N>::~MajorityVoter()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << " is destructed."
		);
}

template <typename T, int N>
  void* MajorityVoter<T, N>::task(void* nullarg)
{
  LOG4CXX_DEBUG(Logger::getLogger("application"), 
		this->name << "'s implementation of task thread."
		);

  while(true)
    {
      // read data from input and print
      Token<int> in1 = this->inPort< Token<int> >("in1")->read();
      Token<int> in2 = this->inPort< Token<int> >("in2")->read();
      Token<int> in3 = this->inPort< Token<int> >("in3")->read();

      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " read "  << in1.getData() << " " << in2.getData() << " " << in3.getData()
		    );

      int resInt = 0;
      if( in1.getData() == in2.getData() )
	{
	  resInt = in1.getData();
	  if ( in1.getData() != in3.getData() )
	    { LOG4CXX_TRACE(Logger::getLogger("application"), "in3 faulty" ); }
	  else
	    { LOG4CXX_TRACE(Logger::getLogger("application"), "no fault" ); }
	}
      else if( in1.getData() == in3.getData() )
	{
	  resInt = in1.getData();
	  if ( in1.getData() != in2.getData() )
	    { LOG4CXX_TRACE(Logger::getLogger("application"), "in2 faulty" ); }
	  else
	    { LOG4CXX_TRACE(Logger::getLogger("application"), "no fault" ); }
	}
      else if( in2.getData() == in3.getData() )
	{
	  resInt = in2.getData();
	  if ( in1.getData() != in2.getData() )
	    { LOG4CXX_TRACE(Logger::getLogger("application"), "in1 faulty" ); }
	  else
	    { LOG4CXX_TRACE(Logger::getLogger("application"), "no fault" ); }
	}
      else
	{
	  LOG4CXX_TRACE(Logger::getLogger("application"), "all results are different. against single fault assumption!" );
	  resInt = NULL;
	}

      this->outPort< Token<int> >("out")->write( *(new Token<int>(resInt)) );
      LOG4CXX_TRACE(Logger::getLogger("application"), 
		    this->name << " wrote "  << resInt
		    );
    }//end while

  return NULL;
}

}
#endif
