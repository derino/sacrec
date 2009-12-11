#ifndef _OUTPORT_H_
#define _OUTPORT_H_

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Port.h"
#include "BlockingQueue.h"

namespace sacre
{

  template <typename T>
    class OutPort : public Port<T>
    {
    public:
      OutPort(std::string _name);
      void write(T);

    };
  
  template <typename T>
    OutPort<T>::OutPort(std::string _name): Port<T>(_name)
    {
    }
  
  template <typename T>
    void OutPort<T>::write(T t)
    {
      this->channel->write(t);
    };
  
}

#endif /* _OUTPORT_H_ */
  
