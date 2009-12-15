#ifndef _ITERABLEINPORT_H_
#define _ITERABLEINPORT_H_

#include "log4cxx/logger.h"
using namespace log4cxx;

namespace sacre
{
    class IterableInPort
    {
    public:
      //      virtual bool nextReadIsStop() = 0;
      // for adaptation, may have disconnect()
      virtual void disconnect() = 0;
    };  
}
#endif /* _ITERABLEINPORT_H_ */
  
