#include <iostream>

#include "SharedVariable.h"

namespace sacre
{

  template <typename T>
  SharedVariable<T>::SharedVariable(std::string _name) : Channel<T>(_name)
  {
    pthread_mutex_init(&owner_mutex, 0); //PTHREAD_MUTEX_INITIALIZER;
  }
  
  template <typename T>
  void SharedVariable<T>::acquire(void)
  {
    pthread_mutex_lock(&owner_mutex);
  }

  template <typename T>
  void SharedVariable<T>::release(void)
  {
    pthread_mutex_unlock(&owner_mutex);
  }
  
  template <typename T>
  void SharedVariable<T>::write(T value)
  {
    std::cout << "Channel " << this->getName() << " is writing value " << value << std::endl;
    
    data = value;
    
    std::cout << "Channel " << this->getName() << " wrote value " << value << std::endl;
  }
  
  template <typename T>
  int SharedVariable<T>::read(T* tmp)
  {
    std::cout << "Channel " << this->getName() << " is reading value " << std::endl;
    
    tmp = &data;
    
    std::cout << "Channel " << this->getName() << " read value " << *tmp << std::endl;
    return 1;
  }
  
}
