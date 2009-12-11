#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <cstdlib>
#include <string>
#include <map>
//#include "boost/lambda/lambda.hpp"
//#include "boost/function.hpp"
#include "Component.h"



namespace sacre
{
  
  class Composite : public Component
  {
  public:
    Composite(std::string);
    ~Composite();
    virtual void* task(void*);

  protected:
    std::map<std::string, Component*> cMap;
    void addComponent(Component*);
    template <typename T>
      void addInPort(std::string, InPort<T>*);
    template <typename T>
      void addOutPort(std::string, OutPort<T>*);
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
    
    }
  
  void Composite::addComponent(Component* c)
  {
    // TODO: check that no two components with same name are added.
    cMap[c->getName()] = c;
  }

  template <typename T>
  void Composite::addInPort(std::string portName, InPort<T>* portToBeExported)
  {
    inPorts[portName] = portToBeExported;
  }


  template <typename T>
  void Composite::addOutPort(std::string portName, OutPort<T>* portToBeExported)
  {
    outPorts[portName] = portToBeExported;
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

}
#endif
