#ifndef _PORT_H_
#define _PORT_H_

#include "log4cxx/logger.h"
using namespace log4cxx;

#include "BlockingQueue.h"
#include "Component.h"

namespace sacre
{

  class Component; // need to forward declare Component because Component and Port includes each other.

  template <typename T>
    class Port
    {
    public:
      Port(std::string _name);
      std::string getName();
      std::string getFullName();
      void setChannel(BlockingQueue<T>*);
      BlockingQueue<T>* getChannel();
      void setComponent(Component*);

    protected:
      std::string name;
      BlockingQueue<T>* channel;      
      Component* comp;
    };
  
  template <typename T>
    Port<T>::Port(std::string _name): name(_name)
    {
      channel = NULL;
      comp = NULL;
    }
  
  template <typename T>
    std::string Port<T>::getName()
    {
      return name;
    };

  template <typename T>
    std::string Port<T>::getFullName()
    {
      return this->comp->getName() + "." + name;
    };

  template <typename T>
    void Port<T>::setChannel(BlockingQueue<T>* channel)
    {
      this->channel = channel;
    }

  template <typename T>
    BlockingQueue<T>* Port<T>::getChannel()
    {
      return this->channel;
    }

  template <typename T>
    void Port<T>::setComponent(Component* c)
    {
      this->comp = c;
    }


}

#endif /* _PORT_H_ */
  
