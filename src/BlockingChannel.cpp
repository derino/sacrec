#include <iostream>

#include "BlockingChannel.h"

namespace sacre 
{
  template <typename T>
  BlockingChannel<T>::BlockingChannel(std::string _name) : Channel<T>(_name)
  {
    live = false;
    pthread_mutex_init(&data_mutex, 0); //PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_init(&live_cond, 0); //PTHREAD_COND_INITIALIZER;
    pthread_mutex_init(&live_mutex, 0); //PTHREAD_MUTEX_INITIALIZER;
  }
  
  template <typename T>
  void BlockingChannel<T>::write(T value)
  {
    std::cout << "Channel " << this->name << " trying to write value " << value << std::endl;
    
    pthread_mutex_lock(&live_mutex);
    while(live) // don't write if data is still not read
      pthread_cond_wait(&live_cond, &live_mutex);
    pthread_mutex_unlock(&live_mutex);
    
    pthread_mutex_lock(&data_mutex);
    data = value;
    live = true;
    pthread_mutex_unlock(&data_mutex);
    pthread_cond_broadcast(&live_cond);
    
    std::cout << "Channel " << this->name << " wrote value " << value << std::endl;
    //    std::cout << "Channel " << name << " has unread value. Not writing value "  << value << " now!" << std::endl;
  }
  
  template <typename T>
  int BlockingChannel<T>::read(T*)
  {
    std::cout << "Channel " << this->name << " trying to read value " << std::endl;

    pthread_mutex_lock(&live_mutex);
    while(!live)
      pthread_cond_wait(&live_cond, &live_mutex);
    pthread_mutex_unlock(&live_mutex);

    pthread_mutex_lock(&data_mutex);
    int tmp = data;
    live = false;
    pthread_mutex_unlock(&data_mutex);
    pthread_cond_broadcast(&live_cond);

    std::cout << "Channel " << this->name << " read value " << tmp << std::endl;
    return tmp;
  }

}
