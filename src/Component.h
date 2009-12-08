#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include "boost/any.hpp"
#include "Channel.h"
#include "SharedVariable.h"
#include "Token.h"
#include "InPort.h"
#include "OutPort.h"
//class Channel;

namespace sacre
{
  
  class Component
  {
  public:
    Component(std::string);
    ~Component();
    std::map<std::string, Channel<Token*>*> channels;
    std::map<std::string, boost::any> inPorts;
    std::map<std::string, boost::any> outPorts;

    void start(void);
    // if task is not pure virtual, I get strange behaviour at run-time.
    // there were times that Component.task() was called 
    // instead of DerivedComponent.task()
    virtual void* task(void*) = 0;
    //template <typename T>
    Channel<Token*>*& operator[] (std::string);
    template <typename T>
      InPort<T>* inPort(std::string);
    template <typename T>
      OutPort<T>* outPort(std::string);

  protected:
    std::string name;
    template <typename T>
    void addChannel(std::string);
    template <typename T>
      void addInPort(std::string);
    template <typename T>
      void addOutPort(std::string);
    //void addSharedVariable(std::string);
    
  private:
    pthread_t thread;
    // return value of pthread_create
    int iret;
  };
  
  extern "C" void* task_cwrapper(void*);
  
  Component::Component(std::string _name): name(_name), thread(0), iret(0)
    {

    }

  Component::~Component()
    {
      // if the component gets out of scope, wait until thread finishes before destruction
      if(thread != 0)
	{
	  pthread_join(thread, NULL);
	  std::cout << "Component " << name << "'s pthread_create returned " << iret << std::endl;
	}
    }

  //  template <typename T = Token>
  Channel<Token*>*& Component::operator[] (std::string chanName)
    {
      if(channels.count(chanName) == 0)
	{
	  std::cout << "FATAL ERROR: " << __FILE__ << ":" << __LINE__ << " Trying to access non-existent channel!" << std::endl;
	  exit(-1);
	}

      return channels[chanName];
    }
  
  
  template <typename T>
    InPort<T>* Component::inPort( std::string portName)
    {
      try
	{
	  InPort<T>* ip =  boost::any_cast< InPort<T>* >(inPorts[portName]);
	  return ip;
	}
      catch(boost::bad_any_cast&)
	{
	  std::cout << "FATAL ERROR: Tried to use the port with a different token type than its supported type!\n";
	}
      return NULL;
    }

  template <typename T>
    OutPort<T>* Component::outPort( std::string portName)
    {
      try
	{
	  OutPort<T>* op =  boost::any_cast< OutPort<T>* >(outPorts[portName]);
	  return op;
	}
      catch(boost::bad_any_cast&)
	{
	  std::cout << "FATAL ERROR: Tried to use the port with a different token type than its supported type!\n";
	}
      return NULL;
    }

  template <typename T>
    void Component::addChannel(std::string chanName)
    {
      //ChannelName<T> cn(chanName);
      //channels[cn] = NULL;
      // NULL -> not connected
      channels[chanName] = NULL;
    }

  template <typename T>
    void Component::addInPort(std::string portName)
    {
      // TODO: check if a port with portName already exists.
      InPort<T>* ip = new InPort<T>(portName);
      inPorts[portName] = ip;
    }
  
  template <typename T>
    void Component::addOutPort(std::string portName)
    {
      // TODO: check if a port with portName already exists.
      OutPort<T>* op = new OutPort<T>(portName);
      outPorts[portName] = op;
    }

  /*
  void Component::addSharedVariable(std::string sharedVarName)
  {
    addChannel<int>(sharedVarName);
  }
  */

  void Component::start(void)
  {
    iret = pthread_create( &thread, NULL, task_cwrapper, (void*)this);
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

  /*template <typename T>
class ChannelName
  {
  public:
    ChannelName(std::string chanName)
      {
	name = chanName;
      }
  std:string name;
  };*/


}
#endif
