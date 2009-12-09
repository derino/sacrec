#ifndef CHANNEL_H
#define CHANNEL_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <string>

namespace sacre 
{
  template <typename T>
    class Channel
    {
    public:
      Channel(std::string);
      virtual void write(T) = 0;
      virtual int read(T*) = 0;
      std::string getName(void);
      
    protected:
      std::string name;
    };
  
  template <typename T>
    Channel<T>::Channel(std::string _name)//: name(_name)
    {
      name = _name;
      //  data = 0;
    }
  
  template <typename T>
    std::string Channel<T>::getName(void)
    {
      return name;
    }

 
}
#endif
