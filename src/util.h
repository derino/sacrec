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
  
  /* template <typename T>
    void dump(std::map<std::string, boost::any> const& m);

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
  */
 
}
#endif
