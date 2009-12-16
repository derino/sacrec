#ifndef _INPORT_H_
#define _INPORT_H_

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "Port.h"
#include "IterableInPort.h"
#include "BlockingQueue.h"
#include "StopTokenException.h"

namespace sacre
{

  template <typename T>
    class InPort : public Port<T>, public IterableInPort
    {
    public:
      InPort(std::string _name);
      T read();
      virtual void disconnect();
    };
  
  template <typename T>
    InPort<T>::InPort(std::string _name): Port<T>(_name)
    {
    }
    
  template <typename T>
    T InPort<T>::read()
    {
      //T* t = new T();
      //this->channel->read(t);
      T t;
      this->channel->read(&t);

      // acts as hook to stop STOP_TOKEN
      // TODO: this can be moved to a hook when we add the hook concept.
      //if( t->isStop() )
      if( t.isStop() )
	{
	  LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
			this->getFullName() << " received STOP_TOKEN"
			);
	  throw StopTokenException();
	}

      //return *t;
      return t;
    };

  template <typename T>
    void InPort<T>::disconnect()
    {
      // TODO: not implemented yet. It's here just to make IterableInPort polymorphic.
    }

}

#endif /* _INPORT_H_ */
  
