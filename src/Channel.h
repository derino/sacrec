#ifndef CHANNEL_H
#define CHANNEL_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <string>

#include "IterableChannel.h"

namespace sacre 
{
  template <typename T>
    class Channel : public IterableChannel 
    {
    public:
      Channel(std::string);
      virtual ~Channel();
      virtual void write(T) = 0;
      virtual int read(T*) = 0;
      std::string getName(void);
      
    protected:
      std::string name;
    };
  
  template <typename T>
    Channel<T>::Channel(std::string _name) : IterableChannel()//, name(_name)
    {
      name = _name;
      //  data = 0;
    }
  
  template <typename T>
    std::string Channel<T>::getName(void)
    {
      return name;
    }

  template <typename T>
  Channel<T>::~Channel()
    {
      
    }

}
#endif
