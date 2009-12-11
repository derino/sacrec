#ifndef _INPORT_H_
#define _INPORT_H_

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Port.h"
#include "BlockingQueue.h"

namespace sacre
{

  template <typename T>
    class InPort : public Port<T>
    {
    public:
      InPort(std::string _name);
      T read();
    };
  
  template <typename T>
    InPort<T>::InPort(std::string _name): Port<T>(_name)
    {
    }
    
  template <typename T>
    T InPort<T>::read()
    {
      T* t = new T();
      this->channel->read(t);
      return *t;
    };
}

#endif /* _INPORT_H_ */
  
