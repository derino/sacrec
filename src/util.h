#ifndef UTIL_H
#define UTIL_H

#include <typeinfo>
#include "Component.h"
#include "Channel.h"
//#include "BlockingChannel.h"
#include "BlockingQueue.h"
//#include "SharedVariable.h"
#include "InPort.h"
#include "OutPort.h"

namespace sacre
{
  
  // FIXME: why bool!?
  template <typename T>
  bool connect(Channel<T>*&, Channel<T>*&);

  /*  template <typename T>
      bool connect(Channel<T>*&, SharedVariable<T>* sharedVariable);*/

  template <typename T>
    bool connect(OutPort<T>*, InPort<T>*);

  template <typename T>
    bool connect(InPort<T>*, OutPort<T>*);

static int i = 0;

template <typename T>
bool connect(OutPort<T>* ip, InPort<T>* op)
{
  // TODO: check if argument ports are already connected. return false if so. (warn and exit)
  BlockingQueue<T>* ch = new BlockingQueue<T>("BlockingQueue" + (++i));
  ip->setChannel(ch);
  op->setChannel(ch);
  return true;
}

template <typename T>
bool connect(InPort<T>* ip, OutPort<T>* op)
{
  return connect(op, ip);
}

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

/*
template <typename T>
bool connect(Channel<T>*& sv, SharedVariable<T>* sharedVariable)
{
  //  sv = dynamic_cast<Channel*>(sharedVariable);
  sv = sharedVariable;

  return true;
}
*/
  
}
#endif
