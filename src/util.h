#ifndef UTIL_H
#define UTIL_H

#include <typeinfo>
#include "Component.h"
#include "Channel.h"
#include "BlockingQueue.h"
#include "InPort.h"
#include "OutPort.h"

namespace sacre
{
  
  // FIXME: why bool!?
  template <typename T>
    bool connect(OutPort<T>*, InPort<T>*);

  template <typename T>
    bool connect(InPort<T>*, OutPort<T>*);

  template <typename T>
    void dump(std::map<std::string, boost::any> const& m);

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
void dump(std::map<std::string, boost::any> const& m)
{
  for(typename std::map<std::string, boost::any>::const_iterator it(m.begin()), j(m.end()); 
      it != j; 
      ++it)
    {
      InPort<T>* ip = boost::any_cast< InPort<T>* >(it->second);
      std::cout << '[' << it->first << "] = " << ip->getChannel()->getName() << " ";// << (it->second)->getData() << '\n';
    }
}

 
}
#endif
