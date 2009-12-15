#ifndef _OUTPORT_H_
#define _OUTPORT_H_

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Port.h"
#include "BlockingQueue.h"
#include "IterableOutPort.h"
#include "Token.h"

namespace sacre
{

  template <typename T>
    class OutPort : public Port<T>, public IterableOutPort
    {
    public:
      OutPort(std::string _name);
      void write(T);
      virtual void writeStopToken();
      virtual void disconnect();
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
  
  template <typename T>
    void OutPort<T>::writeStopToken()
    {
      T* t = new T(STOP_TOKEN);
      this->channel->write(*t);
      LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
		    this->getFullName() << " wrote STOP_TOKEN"
		    );
    }

  template <typename T>
    void OutPort<T>::disconnect()
    {
      // TODO: not implemented yet. It's here just to make IterableOutPort polymorphic.
    }
}

#endif /* _OUTPORT_H_ */
  
