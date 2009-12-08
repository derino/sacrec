#ifndef _INPORT_H_
#define _INPORT_H_

#include "BlockingQueue.h"

namespace sacre
{

  template <typename T>
    class InPort
    {
    public:
      InPort(std::string _name);
      std::string getName();
      T read();

    protected:
      std::string name;
      BlockingQueue<T>* channel;
      
    };
  
  template <typename T>
    InPort<T>::InPort(std::string _name): name(_name)
    {
      channel = NULL;
    }
  
  template <typename T>
    std::string InPort<T>::getName()
    {
      return name;
    };
  
  template <typename T>
    T InPort<T>::read()
    {
      T* t = new T();
      channel.read(t);
      return t;
    };
  
}

#endif /* _INPORT_H_ */
  
