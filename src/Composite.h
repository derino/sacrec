#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <cstdlib>
#include <string>
#include <map>
#include <vector>
//#include "boost/lambda/lambda.hpp"
//#include "boost/function.hpp"
#include "Component.h"
//#include "IterableChannel.h"

namespace sacre
{
  
  class Composite : public Component
  {
  public:
    Composite(std::string);
    virtual ~Composite();
    virtual void* task(void*);
    
  protected:
    std::vector<IterableChannel*> chVec;
    std::map<std::string, Component*> cMap;
    void addComponent(Component*);
    template <typename T>
      void addInPort(std::string, InPort<T>*);
    template <typename T>
      void addOutPort(std::string, OutPort<T>*);

    static int i;
    // FIXME: why bool!?
    template <typename T>
      bool connect(OutPort<T>*, InPort<T>*);
    
    template <typename T>
      bool connect(InPort<T>*, OutPort<T>*);

  };
  
  
  Composite::Composite(std::string _name): Component(_name)
    {
      isComposite = true;
    }

  Composite::~Composite()
    {
       LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
		    "Composite" << name << " is destructed."
		    );
       for(std::map<std::string,Component*>::iterator it=cMap.begin();it!=cMap.end();it++)
	 {
	   delete it->second;
	 }

       for(std::vector<IterableChannel*>::iterator itr=chVec.begin();itr!=chVec.end();itr++)
	 {
	   delete *itr;
	 }

       // Since composites share their inports and outports with the internal components, ~Component() destructor of the composite class tries to delete the ports a second time. Therefore we should remove the ports from the inports and outports lists in this desctructor so that nothing remains to free for composite's ~Component() destructor.
       inPorts.clear();
       outPorts.clear();
    }
  
  void Composite::addComponent(Component* c)
  {
    // TODO: check that no two components with same name are added.
    cMap[c->getName()] = c;
  }

  template <typename T>
  void Composite::addInPort(std::string portName, InPort<T>* portToBeExported)
  {
    IterableInPort* iip = dynamic_cast<IterableInPort*>(portToBeExported);
    inPorts[portName] = iip;
    //    inPorts[portName] = portToBeExported;
  }


  template <typename T>
  void Composite::addOutPort(std::string portName, OutPort<T>* portToBeExported)
  {
    IterableOutPort* iop = dynamic_cast<IterableOutPort*>(portToBeExported);
    outPorts[portName] = iop;
    //outPorts[portName] = portToBeExported;
  }


  void* Composite::task(void* nullarg)
  {
    //boost::function<void(Component*)> f = ((Component*)(boost::lambda::_1))->start();
    //std::for_each(cMap.begin(); cMap.end(); f );

    for(std::map<std::string, Component*>::iterator it = cMap.begin(); it != cMap.end(); ++it)
      {
	it->second->start();
      }

    for(std::map<std::string, Component*>::iterator itr = cMap.begin(); itr != cMap.end(); ++itr)
      {
	if( pthread_join( itr->second->getThread(), NULL) == 0 )
	  LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
			"Thread of Component " << itr->first << " in Composite " << name << " has finished succesfully."
			);
      }

    
    return NULL;
  }


  int Composite::i = 0;

  template <typename T>
    bool Composite::connect(OutPort<T>* op, InPort<T>* ip)
    {
      // TODO: check if argument ports are already connected. return false if so. (warn and exit)
      std::stringstream i_str;
      i_str << ++i;
      BlockingQueue<T>* ch = new BlockingQueue<T>( "BlockingQueue" + i_str.str() );
      // TODO: if connect is called with wrong token type (e.g. int instead of Token<int>), op and ip may come as NULL. It needs to be checked.
      ip->setChannel(ch);
      op->setChannel(ch);
      chVec.push_back(ch);

      LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
		    "connected: " << op->getFullName() << " >-----" << ch->getName() <<  "-----> " << ip->getFullName()
		    );
      return true;
    }

  template <typename T>
    bool Composite::connect(InPort<T>* ip, OutPort<T>* op)
    {
      return connect(op, ip);
    }
 

}
#endif
