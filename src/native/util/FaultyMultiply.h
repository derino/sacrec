#ifndef FAULTYMULTIPLY_H
#define FAULTYMULTIPLY_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Component.h"
#include "Token.h"
//#include "IntToken.h"

namespace sacre
{
  class FaultyMultiply: public Component
  {
  public:
    FaultyMultiply(std::string);
    virtual void* task(void*);
    ~FaultyMultiply();
  };

  FaultyMultiply::FaultyMultiply(std::string _name): Component(_name)
  {
    addInPort< Token<int> >("in");
    addOutPort< Token<int> >("out");
  }

  FaultyMultiply::~FaultyMultiply()
    {
      LOG4CXX_DEBUG(Logger::getLogger("application"), 
		    this->name << " is destructed."
		    );
    }

  void* FaultyMultiply::task(void* nullarg)
  {
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  this->name << "'s implementation of task thread."
		  );

    while(true)
      {
	// read data from input and print
	Token<int> res = this->inPort< Token<int> >("in")->read();
	LOG4CXX_TRACE(Logger::getLogger("application"), 
		      this->name << " read "  << res.getData()
		      );

	int resInt = res.getData()*4 + 1;

	this->outPort< Token<int> >("out")->write( *(new Token<int>(resInt)) );
	LOG4CXX_TRACE(Logger::getLogger("application"), 
		      this->name << " wrote "  << resInt
		      );
      }

    return NULL;
  }

}
#endif
