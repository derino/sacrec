#ifndef COMPONENT_H
#define COMPONENT_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include "boost/any.hpp"
#include "Channel.h"
#include "InPort.h"
#include "OutPort.h"


namespace sacre
{
  
  class Component
  {
  public:
    Component(std::string);
    ~Component();
    std::map<std::string, boost::any> inPorts;
    std::map<std::string, boost::any> outPorts;

    void start(void);
    pthread_t getThread();
    // if task is not pure virtual, I get strange behaviour at run-time.
    // there were times that Component.task() was called 
    // instead of DerivedComponent.task()
    virtual void* task(void*) = 0;
    //Channel<Token*>*& operator[] (std::string);
    template <typename T>
      InPort<T>* inPort(std::string);
    template <typename T>
      OutPort<T>* outPort(std::string);
    std::string getName();

  protected:
    std::string name;
    bool isComposite;
    template <typename T>
      void addInPort(std::string);
    template <typename T>
      void addOutPort(std::string);

    pthread_t thread;
    // return value of pthread_create
    int iret;
  };
  
  extern "C" void* task_cwrapper(void*);
  
  Component::Component(std::string _name): name(_name), isComposite(false), thread(0), iret(0)
    {

    }

  Component::~Component()
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
		    "Component" << name << " is destructed."
		    );
    
      // IMPORTANT NOTE:
      // below join doesn't do what we intend to achieve. It is sometimes the case that
      // DerivedComponent's destructor is called before its thread finishes and before 
      // Component's destructor is called. In this case we get a 
      // "pure virtual method called / terminate called without an active exception"
      // error with an ABORT. 
      // (see: http://tombarta.wordpress.com/2008/07/10/gcc-pure-virtual-method-called/)
      // Solution for now is to move the below join to the end of main thread (e.g. main.cpp).
      // OR move below join to the destructor of each deriving component.
      
      
      /* // if the component gets out of scope, wait until thread finishes before destruction */
      /* if(thread != 0) */
      /* 	{ */
      /* 	  pthread_join(thread, NULL); */
      /* 	  std::cout << "Component " << name << "'s pthread_create returned " << iret << std::endl; */
      /* 	} */
    }

  /*
  Channel<Token*>*& Component::operator[] (std::string chanName)
    {
      if(channels.count(chanName) == 0)
	{
	  std::cout << "FATAL ERROR: " << __FILE__ << ":" << __LINE__ << " Trying to access non-existent channel!" << std::endl;
	  exit(-1);
	}

      return channels[chanName];
    }
*/  
  
  template <typename T>
    InPort<T>* Component::inPort( std::string portName)
    {
      try
	{
	  std::map<std::string,boost::any>::iterator it;
	  it = inPorts.find(portName);
	  if( it == inPorts.end() )
	    {
	      LOG4CXX_FATAL(Logger::getLogger("sacrec"), 
			    "Tried to use non-existent port! " << this->name << " doesn't have an input port named " << portName
			    );
	      exit(EXIT_FAILURE);
	    }
	  else
	    {
	      InPort<T>* ip =  boost::any_cast< InPort<T>* >(inPorts[portName]);
	      return ip;
	    }
	}
      catch(boost::bad_any_cast&)
	{
	  LOG4CXX_FATAL(Logger::getLogger("sacrec"), 
			"FATAL ERROR: Tried to use " << name << "'s " << portName << " port with a different token type than its original type as defined in the component!\n"
			);
	  exit(EXIT_FAILURE);
	}
      return NULL;
    }

  template <typename T>
    OutPort<T>* Component::outPort( std::string portName)
    {
      try
	{
	  std::map<std::string,boost::any>::iterator it;
	  it = outPorts.find(portName);
	  if( it == outPorts.end() )
	    {
	      LOG4CXX_FATAL(Logger::getLogger("sacrec"), 
			    "Tried to use non-existent port! " << this->name << " doesn't have an output port named " << portName
			    );
	      exit(EXIT_FAILURE);
	    }
	  else
	    {
	      OutPort<T>* op =  boost::any_cast< OutPort<T>* >(outPorts[portName]);
	      return op;
	    }
	}
      catch(boost::bad_any_cast&)
	{
	  LOG4CXX_FATAL(Logger::getLogger("sacrec"), 
			"FATAL ERROR: Tried to use " << name << "'s " << portName << " port with a different token type than its original type as defined in the component!\n"
			);
	  exit(EXIT_FAILURE);
	}
      return NULL;
    }

  template <typename T>
    void Component::addInPort(std::string portName)
    {
      if(isComposite)
	{
	  LOG4CXX_FATAL(Logger::getLogger("sacrec"), 
			"addInPort(std::string) can not be used for composite components. Use addInPort(std::string, InPort<T>*) instead."
			);
	  exit(EXIT_FAILURE);
	}
      
      // TODO: check if a port with portName already exists.
      InPort<T>* ip = new InPort<T>(portName);
      inPorts[portName] = ip;
      ip->setComponent(this);
    }
  
  template <typename T>
    void Component::addOutPort(std::string portName)
    {
      if(isComposite)
	{
	  LOG4CXX_FATAL(Logger::getLogger("sacrec"), 
			"addOutPort(std::string) can not be used for composite components. Use addOutPort(std::string, OutPort<T>*) instead."
			);
	  exit(EXIT_FAILURE);
	}
      
      // TODO: check if a port with portName already exists.
      OutPort<T>* op = new OutPort<T>(portName);
      outPorts[portName] = op;
      op->setComponent(this);
    }

  void Component::start(void)
  {
    // TODO: what to do with iret? Do we really need it?
    iret = pthread_create( &thread, NULL, task_cwrapper, (void*)this);
  }

  pthread_t Component::getThread()
  {
    return thread;
  }

  /*void* Component::task(void*)
    {
    std::cout << "default component task function does nothing. Extend Component and override task method." << std::endl;
    }*/

  extern "C" void* task_cwrapper(void* arg)
  {
    Component* c = static_cast<Component*>(arg);
    c->task( (void*) NULL);
    return NULL;
  }

  std::string Component::getName()
    {
      return name;
    }

}
#endif
