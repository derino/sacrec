#ifndef _ITERABLEOUTPORT_H_
#define _ITERABLEOUTPORT_H_

#include "log4cxx/logger.h"
using namespace log4cxx;

namespace sacre
{
    class IterableOutPort
    {
    public:
      //      virtual bool nextReadIsStop() = 0;
      virtual void writeStopToken() = 0;
      // for adaptation, may have disconnect()
      virtual void disconnect() = 0;
    };  
}
#endif /* _ITERABLEOUTPORT_H_ */
  
