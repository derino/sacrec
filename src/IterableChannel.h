#ifndef ITERABLECHANNEL_H
#define ITERABLECHANNEL_H


#include "log4cxx/logger.h"
using namespace log4cxx;

#include <string>

namespace sacre 
{
    class IterableChannel
    {
    public:
      virtual ~IterableChannel();
      virtual std::string getName()=0;
    };  

    IterableChannel::~IterableChannel()
      {
	
      }
}

#endif
