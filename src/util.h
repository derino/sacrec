#ifndef UTIL_H
#define UTIL_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <typeinfo>
#include <sstream>
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
bool connect(OutPort<T>* op, InPort<T>* ip)
{
  // TODO: check if argument ports are already connected. return false if so. (warn and exit)
  std::stringstream i_str;
  i_str << ++i;
  BlockingQueue<T>* ch = new BlockingQueue<T>( "BlockingQueue" + i_str.str() );
  // TODO: if connect is called with wrong token type (e.g. int instead of Token<int>), op and ip may come as NULL. It needs to be checked.
  ip->setChannel(ch);
  op->setChannel(ch);

  LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
		"connected: " << op->getFullName() << " >-----" << ch->getName() <<  "-----> " << ip->getFullName()
		);
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
      LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
		    '[' << it->first << "] = " << ip->getChannel()->getName() << " "
		    );
    }
}

 
}
#endif
