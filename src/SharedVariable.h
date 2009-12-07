#ifndef SHAREDVARIABLE_H
#define SHAREDVARIABLE_H

#include <string>

#include "Channel.h"

namespace sacre
{
  
  template <typename T>
    class SharedVariable : public Channel<T>
  {
  public:
    SharedVariable(std::string);
    void acquire(void);
    void release(void);
    void write(T);
    int read(T*);
    
  protected:
    pthread_mutex_t owner_mutex;
    T data;
  };
}
#endif
