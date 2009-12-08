#ifndef _PORT_H_
#define _PORT_H_

#include "BlockingQueue.h"

namespace sacre
{

  template <typename T>
    class Port
    {
    public:
      Port(std::string _name);
      std::string getName();
      void setChannel(BlockingQueue<T>*);
      BlockingQueue<T>* getChannel();

    protected:
      std::string name;
      BlockingQueue<T>* channel;      
    };
  
  template <typename T>
    Port<T>::Port(std::string _name): name(_name)
    {
      channel = NULL;
    }
  
  template <typename T>
    std::string Port<T>::getName()
    {
      return name;
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


}

#endif /* _PORT_H_ */
  
