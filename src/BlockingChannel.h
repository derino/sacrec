#ifndef BLOCKINGCHANNEL_H
#define BLOCKINGCHANNEL_H

#include <string>
#include <pthread.h>

#include "Channel.h"

namespace sacre
{
  template <typename T>
  class BlockingChannel : public Channel<T>
  {
  public:
    BlockingChannel(std::string);
    void write(T);
    int read(T*);
    
  private:
    T data;
    bool live;
    pthread_mutex_t data_mutex;
    pthread_cond_t  live_cond;
    pthread_mutex_t live_mutex;
  };
  
}
#endif
