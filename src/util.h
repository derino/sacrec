#ifndef UTIL_H
#define UTIL_H

#include <typeinfo>
#include "Component.h"
#include "Channel.h"
#include "BlockingChannel.h"
#include "BlockingQueue.h"
#include "SharedVariable.h"

namespace sacre
{
  
  // FIXME: why bool!?
  template <typename T>
  bool connect(Channel<T>*&, Channel<T>*&);

  template <typename T>
  bool connect(Channel<T>*&, SharedVariable<T>* sharedVariable);

static int i = 0;

template <typename T>
bool connect(Channel<T>*& ch1, Channel<T>*& ch2)
{
  //  ch1 = dynamic_cast<Channel*>(new BlockingChannel("BlockingChannel" + (++i) ) );

  //  ch1 = new BlockingChannel("BlockingChannel" + (++i) );
  //  ch2 = ch1;
  std::cout << typeid(T).name() << std::endl;
  ch1 = new BlockingQueue<T>("BlockingQueue" + (++i));
  ch2 = ch1;
  return true;
}

template <typename T>
bool connect(Channel<T>*& sv, SharedVariable<T>* sharedVariable)
{
  //  sv = dynamic_cast<Channel*>(sharedVariable);
  sv = sharedVariable;

  return true;
}

  
}
#endif
